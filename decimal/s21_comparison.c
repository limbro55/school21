#include "s21_decimal.h"

// >
int s21_is_greater(s21_decimal val1, s21_decimal val2) {
  if (get(&val1, sign) != get(&val2, sign)) {
    return (!isnull(val1) || !isnull(val2)) && get(&val1, sign) == 0;
  }

  if (get(&val1, expo) != get(&val2, expo)) unidec(&val1, &val2);

  for (int i = 95; i >= 0; i--) {
    int b1 = get_bit_from_decimal(&val1, i);
    int b2 = get_bit_from_decimal(&val2, i);
    if (b1 != b2) return (b1 > b2) ^ get(&val1, sign);
  }
  return 0;
}

// <
int s21_is_less(s21_decimal val1, s21_decimal val2) {
  if (get(&val1, sign) != get(&val2, sign)) {
    return (!isnull(val1) || !isnull(val2)) && get(&val1, sign) == 1;
  }

  if (get(&val1, expo) != get(&val2, expo)) unidec(&val1, &val2);

  for (int i = 95; i >= 0; i--) {
    int b1 = get_bit_from_decimal(&val1, i);
    int b2 = get_bit_from_decimal(&val2, i);
    if (b1 != b2) return (b1 < b2) ^ get(&val1, sign);
  }
  return 0;
}

// ==
int s21_is_equal(s21_decimal val1, s21_decimal val2) {
  if (get(&val1, sign) != get(&val2, sign)) return isnull(val1) && isnull(val2);

  unidec(&val1, &val2);
  for (int i = 95; i >= 0; i--) {
    if (get_bit_from_decimal(&val1, i) != get_bit_from_decimal(&val2, i))
      return 0;
  }
  return 1;
}

// <=
int s21_is_less_or_equal(s21_decimal val1, s21_decimal val2) {
  return s21_is_equal(val1, val2) || s21_is_less(val1, val2);
}

// !=
int s21_is_not_equal(s21_decimal val1, s21_decimal val2) {
  return !s21_is_equal(val1, val2);
}

// >=
int s21_is_greater_or_equal(s21_decimal val1, s21_decimal val2) {
  return s21_is_equal(val1, val2) || s21_is_greater(val1, val2);
}
