#include "s21_decimal.h"

// Округляет значение value вниз
int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result || !is_dec_correct(value)) return CALCULATION_ERROR;

  init_result(result);
  s21_decimal fract = {{0}};

  s21_truncate(value, result);
  s21_sub(value, *result, &fract);

  if (get(&fract, sign)) {
    return s21_sub(*result, DECIMAL_ONE, result);
  }

  return OK;
}

// Округляет значение value до ближайшего целого
int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result || !is_dec_correct(value)) return CALCULATION_ERROR;

  *result = value;
  int left = 0;

  while (get(result, expo) > 0) {
    left = decrease_exponent(result);
  }

  if (left >= 5) madd(*result, DECIMAL_ONE, result);

  return OK;
}

// Отбрасывает дробную часть числа value (усекает до целого)
int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result || !is_dec_correct(value)) return CALCULATION_ERROR;

  *result = value;

  while (get(result, expo) > 0) {
    decrease_exponent(result);
  }

  return OK;
}

// Меняет знак числа
int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) return CALCULATION_ERROR;

  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }

  result->bits[3] ^= SIGN_MASK;

  return OK;
}
