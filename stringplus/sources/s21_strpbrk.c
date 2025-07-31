#include "../../src/s21_string.h"

// need upgrade
char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1) {
    const char *p = str2;
    while (*p) {
      if (*str1 == *p) {
        return (char *)str1;
      }
      p++;
    }
    str1++;
  }
  return S21_NULL;
}