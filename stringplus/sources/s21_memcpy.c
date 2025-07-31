#include "../../src/s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (dest != S21_NULL && src != S21_NULL) {
    s21_size_t i = 0;
    while (i++ < n) *(((char *)dest) + (i - 1)) = *(((char *)src) + (i - 1));
  }
  return dest;
}