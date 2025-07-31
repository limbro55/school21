#include "../../src/s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  while (n > 0 && *str1 && *str1 == *str2) {
    str1++;
    str2++;
    n--;
  }

  if (n == 0) {
    return 0;
  }

  return (int)(signed char)*str1 - (int)(signed char)*str2;
}