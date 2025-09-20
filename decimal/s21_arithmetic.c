#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!is_dec_correct(value_1) || !is_dec_correct(value_2) || !result) return 1;

  init_result(result);

  if (isnull(value_2)) {
    *result = value_1;
    return 0;
  }
  if (isnull(value_1)) {
    *result = value_2;
    return 0;
  }

  int left = abs(unidec(&value_1, &value_2));
  get(result, sign) = (mequal(value_1, value_2) == 1) ? get(&value_1, sign)
                                                      : get(&value_2, sign);

  int ret = 0;
  if (get(&value_1, sign) == get(&value_2, sign)) {
    ret += add_dev(value_1, value_2, result, &left);
  } else {
    if (mequal(value_1, value_2) == 1)
      invert(&value_1);
    else
      invert(&value_2);

    result->bits[3] ^= (1 << 31);
    get(&value_1, sign) = get(&value_2, sign) = get(result, sign);
    ret += add_dev(value_1, value_2, result, &left);
    invert(result);
    left = -left;
  }

  ret += bank_round(result, left);
  ret = ret ? get(result, sign) + 1 : ret;
  get(result, sign) &= !isnull(*result);

  return ret;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return INCORRECT_INPUT_VALUE;

  init_result(result);
  int res_code = normalize(&value_1, &value_2, result);

  if (res_code != OK) return res_code;

  int sign1 = get_sign(value_1), sign2 = get_sign(value_2);

  if (sign1 == 0 && sign2 == 1) {
    clear_sign(&value_2);
    res_code = s21_add(value_1, value_2, result);
    if (res_code == OK) set_sign(result, 0);
  } else if (sign1 == 1 && sign2 == 0) {
    clear_sign(&value_1);
    res_code = s21_add(value_1, value_2, result);
    if (res_code == TOO_BIG) res_code = TOO_SMALL;
    if (res_code == OK || res_code == TOO_SMALL) set_sign(result, 1);
  } else {
    clear_sign(&value_1);
    clear_sign(&value_2);

    if (s21_is_greater(value_1, value_2)) {
      sub_dev(value_1, value_2, result);
      set_sign(result, sign1);
    } else if (s21_is_equal(value_1, value_2)) {
      init_result(result);
    } else {
      sub_dev(value_2, value_1, result);
      set_sign(result, sign1 ^ 1);
    }
  }

  return res_code;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!is_dec_correct(value_1) || !is_dec_correct(value_2) || !result) return 1;

  init_result(result);
  if (isnull(value_1) || isnull(value_2)) return 0;

  s21_decimal leftovers = {{0}};
  get(result, expo) = get(&value_1, expo) + get(&value_2, expo);
  get(result, sign) = get(&value_1, sign) ^ get(&value_2, sign);

  int ret = double_d_mul(value_1, value_2, result, &leftovers);
  int carry = 0;
  ret += merge_dev(result, leftovers, &carry);
  ret += bank_round(result, carry);

  return ret ? get(result, sign) + 1 : 0;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!is_dec_correct(value_1) || !is_dec_correct(value_2) || !result) return 1;

  init_result(result);
  if (isnull(value_2)) return 3;
  if (isnull(value_1)) return 0;

  prepare_div(&value_1, &value_2);

  int result_expo = get(&value_1, expo) - get(&value_2, expo);
  short result_sign = get(&value_1, sign) ^ get(&value_2, sign);

  int res_code = 0, carry = 0;
  s21_decimal leftovers = {{0}};

  while (!isnull(value_1) && !res_code) {
    if (mequal(value_1, value_2) < 0) {
      s21_decimal tmp_dec = leftovers;
      if (mul_by_ten(&tmp_dec))
        init_result(&value_1);
      else {
        leftovers = tmp_dec;
        s21_add(leftovers, (s21_decimal){{mul_by_ten(result), 0, 0, 0}},
                &leftovers);
        result_expo++;
      }
      carry = mul_by_ten(&value_1);
    }

    while (mequal(value_1, value_2) >= 0 || carry > 0) {
      carry -= msub(value_1, value_2, &value_1);
      if (s21_add(*result, DECIMAL_ONE, result)) {
        res_code += s21_add(leftovers, DECIMAL_ONE, &leftovers);
        init_result(result);
      }
    }
  }

  while (isnull(leftovers) && !res_code && result_expo < 0) {
    res_code += increase_exponent(result);
    result_expo++;
  }

  get(result, sign) = result_sign;

  if (!res_code) {
    get(result, expo) = result_expo;
    res_code = merge_dev(result, leftovers, &carry);
    res_code += bank_round(result, carry);
  }

  if (res_code) {
    result->bits[0] = result->bits[1] = result->bits[2] = UINT_MAX;
    get(result, expo) = 0;
    res_code = get(result, sign) + 1;
  }

  return res_code;
}
