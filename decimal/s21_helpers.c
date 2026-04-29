#include <math.h>
#include <stdio.h>

#include "s21_decimal.h"

int get_sign(s21_decimal value) { return (value.bits[3] & SIGN_MASK) != 0; }
void set_sign(s21_decimal *value, int sign) {
  sign ? (value->bits[3] |= SIGN_MASK) : (value->bits[3] &= ~SIGN_MASK);
}
void clear_sign(s21_decimal *value) { value->bits[3] &= ~SIGN_MASK; }
void set_scale(s21_decimal *dst, int scale) {
  if (!dst) return;
  dst->bits[3] &= ~EXPONENT_MASK;
  dst->bits[3] |= ((uint32_t)scale << 16) & EXPONENT_MASK;
}

int get_exp(s21_decimal value) { return (value.bits[3] >> 16) & 0xFF; }
int set_exp(s21_decimal *value, int exp) {
  if (!value) return INCORRECT_EXPONENT;
  if (exp < 0 || exp > 28) return INCORRECT_EXPONENT;
  value->bits[3] &= ~EXPONENT_MASK;
  value->bits[3] |= ((uint32_t)exp << 16) & EXPONENT_MASK;
  return 0;
}

int get_bit(uint32_t mask, int pos) { return (mask >> pos) & 1u; }

int get_bit_from_decimal(const s21_decimal *dec, int bit_pos) {
  if (bit_pos < 0 || bit_pos >= 128) return 0;
  int index = bit_pos / 32;
  int offset = bit_pos % 32;
  return (dec->bits[index] >> offset) & 1u;
}

int set_bit(uint32_t *mask, int pos, int value) {
  if (value)
    *mask |= (1u << pos);
  else
    *mask &= ~(1u << pos);
  return 0;
}

int normalize(s21_decimal *v1, s21_decimal *v2, s21_decimal *res) {
  int exp1 = get_exp(*v1), exp2 = get_exp(*v2);
  int delta_exp = exp1 - exp2;
  int res_code = OK;

  s21_decimal exp = {{10, 0, 0, 0}};
  s21_decimal *max_exp_decimal = v1;
  s21_decimal *min_exp_decimal = v2;

  if (delta_exp < 0) {
    max_exp_decimal = v2;
    min_exp_decimal = v1;
    delta_exp = -delta_exp;
  }

  while (delta_exp-- && !res_code) {
    s21_decimal tmp = {{0}};
    res_code = s21_mul(*min_exp_decimal, exp, &tmp);
    *min_exp_decimal = tmp;
  }

  if (get_exp(*min_exp_decimal) > 28) res_code = TOO_BIG;

  set_exp(min_exp_decimal, get_exp(*max_exp_decimal));
  set_exp(res, get_exp(*max_exp_decimal));
  return res_code;
}

int madd(s21_decimal v1, s21_decimal v2, s21_decimal *res) {
  int ret = 0;

  res->bits[0] = v1.bits[0] + v2.bits[0];
  if (res->bits[0] < v2.bits[0]) {
    if (++v1.bits[1] == 0 && ++v1.bits[2] == 0) ret = 1;
  }

  res->bits[1] = v1.bits[1] + v2.bits[1];
  if (res->bits[1] < v2.bits[1]) {
    if (++v1.bits[2] == 0) ret = 1;
  }

  res->bits[2] = v1.bits[2] + v2.bits[2];
  if (res->bits[2] < v2.bits[2]) ret = 1;

  return ret;
}

int msub(s21_decimal v1, s21_decimal v2, s21_decimal *res) {
  int ret = 0;

  res->bits[0] = v1.bits[0] - v2.bits[0];
  if (v2.bits[0] > v1.bits[0]) {
    if (--v1.bits[1] == UINT_MAX && --v1.bits[2] == UINT_MAX) ret = 1;
  }

  res->bits[1] = v1.bits[1] - v2.bits[1];
  if (v2.bits[1] > v1.bits[1]) {
    if (--v1.bits[2] == UINT_MAX) ret = 1;
  }

  res->bits[2] = v1.bits[2] - v2.bits[2];
  if (v2.bits[2] > v1.bits[2]) ret = 1;

  return ret;
}

int add_dev(s21_decimal v1, s21_decimal v2, s21_decimal *result, int *left) {
  int ret = 0;

  while (ret == 0 && (ret = madd(v1, v2, result))) {
    if (get(&v1, expo) && get(&v2, expo)) {
      *left = decrease_exponent(&v1) + decrease_exponent(&v2);
      if (*left > 9) madd(v1, (s21_decimal){{1, 0, 0, 0}}, &v1);
      *left %= 10;
      ret = 0;
    }
  }

  get(result, expo) = get(&v1, expo);
  while (get(result, expo) > 28) *left = decrease_exponent(result);

  return ret;
}

void sub_dev(s21_decimal v1, s21_decimal v2, s21_decimal *res) {
  int borrow = 0;

  for (int i = 0; i < NUMBER_OF_DIGITS_IN_BIT * BITS_FOR_NUM; ++i) {
    int diff = get_decimal_bit(v1, i) - get_decimal_bit(v2, i) - borrow;
    if (diff == 1) {
      set_decimal_bit(res, i, 1);
      borrow = 0;
    } else if (diff < 0) {
      set_decimal_bit(res, i, 1);
      borrow = 1;
    } else
      borrow = 0;
  }
}

static int validate_decimal_position(int pos) {
  const int first_pos_in_exp = NUMBER_OF_DIGITS_IN_BIT * AMOUNT_BITS;
  if (pos < 0 || pos >= NUMBER_OF_DIGITS_IN_BIT * 4) return 1;
  if ((pos >= first_pos_in_exp && pos <= first_pos_in_exp + 15) ||
      (pos >= first_pos_in_exp + 24 && pos <= first_pos_in_exp + 30))
    return 1;
  return 0;
}

int get_decimal_bit(s21_decimal num, int pos) {
  if (validate_decimal_position(pos)) return -1;
  return get_bit(num.bits[pos / NUMBER_OF_DIGITS_IN_BIT],
                 pos % NUMBER_OF_DIGITS_IN_BIT);
}

int set_decimal_bit(s21_decimal *num, int pos, int value) {
  if (validate_decimal_position(pos)) return -1;
  return set_bit(&num->bits[pos / NUMBER_OF_DIGITS_IN_BIT],
                 pos % NUMBER_OF_DIGITS_IN_BIT, value);
}

void init_result(s21_decimal *res) {
  for (int i = 0; i < AMOUNT_BITS; ++i) res->bits[i] = 0;
}

int is_dec_correct(s21_decimal d) {
  return !get(&d, zero1) && !get(&d, zero2) && get(&d, expo) <= 28;
}
int isnull(s21_decimal d) { return !d.bits[0] && !d.bits[1] && !d.bits[2]; }

int decrease_exponent(s21_decimal *d) {
  if (get(d, expo) == 0) return -1;
  return decrease_exponent_remainder(d, 0);
}

int decrease_exponent_remainder(s21_decimal *d, unsigned left) {
  unsigned long tmp = left;
  if (!isnull(*d) || left)
    for (int n = 2; n >= 0; n--) {
      tmp = tmp * (UINT_MAX + 1UL) + d->bits[n];
      d->bits[n] = (unsigned)(tmp / 10);
      tmp %= 10;
    }
  get(d, expo)--;
  return (int)tmp;
}

int increase_exponent(s21_decimal *d) {
  if (get(d, expo) >= 28U) return 1;
  s21_decimal tmp = *d;
  int err = mul_by_ten(&tmp);
  if (!err) {
    *d = tmp;
    get(d, expo)++;
  }
  return err;
}

unsigned int mul_by_ten(s21_decimal *d) {
  unsigned ret = 0;
  unsigned long carry = 0;
  for (int n = 0; n < 3; n++) {
    unsigned long t = 10UL * d->bits[n] + carry;
    d->bits[n] = (unsigned)(t % (UINT_MAX + 1UL));
    carry = t >> 32;
    ret = (unsigned)carry;
  }
  return ret;
}

void invert(s21_decimal *d) {
  for (int i = 0; i < 3; i++) d->bits[i] = ~d->bits[i];
  d->bits[3] ^= 1u << 31;
}

int mequal(s21_decimal d1, s21_decimal d2) {
  for (int i = 2; i >= 0; i--)
    if (d1.bits[i] != d2.bits[i]) return d1.bits[i] > d2.bits[i] ? 1 : -1;
  return 0;
}

// ===== Служебные сложные операции =====
int bank_round(s21_decimal *d, int digit) {
  int ret = 0;
  if (abs(digit) > 5 || (abs(digit) == 5 && get_bit(d->bits[0], 0))) {
    if (digit < 0) {
      msub(*d, (s21_decimal){{1, 0, 0, 0}}, d);
    } else if (madd(*d, (s21_decimal){{1, 0, 0, 0}}, d)) {
      *d = (s21_decimal){{0, 0, 0, d->bits[3]}};
      if (get(d, expo) > 0) {
        decrease_exponent_remainder(d, 1);
        madd(*d, (s21_decimal){{1, 0, 0, 0}}, d);
      } else
        ret = get(d, sign) + 1;
    }
  }
  return ret;
}

int merge_dev(s21_decimal *d, s21_decimal leftovers, int *left) {
  int ret = 0;
  while (!isnull(leftovers) && !ret) {
    if (get(d, expo) == 0)
      ret = 1;
    else {
      *left = decrease_exponent_remainder(&leftovers, 0);
      *left = decrease_exponent_remainder(d, *left);
    }
  }
  while (get(d, expo) > 28) *left = decrease_exponent(d);
  return ret;
}

int unidec(s21_decimal *d1, s21_decimal *d2) {
  int carry = 0, tmp;
  if (isnull(*d1)) get(d1, expo) = get(d2, expo);
  if (isnull(*d2)) get(d2, expo) = get(d1, expo);

  while (get(d1, expo) < get(d2, expo) && !increase_exponent(d1));
  while (get(d1, expo) > get(d2, expo) && !increase_exponent(d2));

  while (!isnull(*d1) && !isnull(*d2) && get(d1, expo) < get(d2, expo) &&
         (tmp = decrease_exponent(d2)) != -1)
    carry = tmp;
  while (!isnull(*d1) && !isnull(*d2) && get(d1, expo) > get(d2, expo) &&
         (tmp = decrease_exponent(d1)) != -1)
    carry = -tmp;

  return carry;
}

void prepare_div(s21_decimal *v1, s21_decimal *v2) {
  unsigned tmp_exp = get(v2, expo);
  get(v2, expo) = 0;
  while (!increase_exponent(v2)) tmp_exp += get(v2, expo)--;
  get(v2, expo) += tmp_exp;

  tmp_exp = get(v1, expo);
  get(v1, expo) = 0;
  while (!increase_exponent(v1)) tmp_exp += get(v1, expo)--;
  get(v1, expo) += tmp_exp;

  tmp_exp = get(v2, expo);
  get(v2, expo) = 28U;
  s21_decimal tmp_dec = *v2;
  while ((mequal(*v1, *v2) < 0) && decrease_exponent(&tmp_dec) == 0)
    *v2 = tmp_dec;

  while (28U - get(v2, expo) > tmp_exp) get(v2, expo)++, get(v1, expo)++;

  get(v2, expo) = tmp_exp - (28U - get(v2, expo));
  while (get(v1, expo) > 0 && get(v2, expo) > 0)
    get(v1, expo)--, get(v2, expo)--;
}

int double_d_mul(s21_decimal v1, s21_decimal v2, s21_decimal *res,
                 s21_decimal *leftovers) {
  int ret = 0;
  for (int i = 0; i < 3 && !ret; i++) {
    unsigned long carry = 0;
    short lo_index = 0;
    for (int j = 0; j < 3; j++) {
      unsigned long r =
          (unsigned long)v1.bits[i] * (unsigned long)v2.bits[j] + carry;
      carry = r >> 32;
      r &= UINT_MAX;
      if (i + j <= 2) {
        r += res->bits[i + j];
        res->bits[i + j] = (unsigned)r;
      } else {
        r += leftovers->bits[lo_index];
        leftovers->bits[lo_index++] = (unsigned)r;
      }
      carry += r >> 32;
      if (carry && j == 2) {
        s21_decimal tmp = {{0}};
        tmp.bits[i] = (unsigned)carry;
        ret += madd(*leftovers, tmp, leftovers);
      }
    }
  }
  return ret;
}
