#include <float.h>
#include <math.h>
#include <stdbool.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) return CONVERSION_ERROR;

  init_result(dst);
  dst->bits[0] = (unsigned)abs(src);
  set_sign(dst, src < 0);
  return OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst || !isfinite(src)) return CONVERSION_ERROR;
  init_result(dst);
  if (src == 0.0f) return OK;

  int sign = src < 0 ? 1 : 0;
  if (sign) src = -src;

  if (src > 79228162514264337593543950335.0f) return CONVERSION_ERROR;

  double val = src;
  int scale = 0;

  while (val != floor(val) && scale < 28) {
    val *= 10.0;
    scale++;
  }

  dst->bits[0] = (uint32_t)fmod(val, 4294967296.0);
  dst->bits[1] = (uint32_t)(fmod(val / 4294967296.0, 4294967296.0));
  dst->bits[2] = (uint32_t)(fmod(val / 18446744073709551616.0, 4294967296.0));

  set_exp(dst, scale);
  set_sign(dst, sign);

  return OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) return CONVERSION_ERROR;

  s21_truncate(src, &src);

  if (src.bits[1] == 0 && src.bits[2] == 0 &&
      src.bits[0] <= (unsigned)INT_MAX + get(&src, sign)) {
    *dst = (int)(src.bits[0]) * (get(&src, sign) ? -1 : 1);
    return OK;
  }
  return CONVERSION_ERROR;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) return CONVERSION_ERROR;

  int sign = (src.bits[3] & 0x80000000) ? -1 : 1;
  int scale = (src.bits[3] >> 16) & 0xFF;

  long double value = (long double)src.bits[0] +
                      (long double)src.bits[1] * 4294967296.0L +
                      (long double)src.bits[2] * 18446744073709551616.0L;

  *dst = (float)(value * powl(10.0L, -scale) * sign);
  return OK;
}
