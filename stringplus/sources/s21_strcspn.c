#include "../../src/s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  if (str1 == S21_NULL || str2 == S21_NULL) return 0;
  const char *p1, *p2;

  for (p1 = str1; *p1 != '\0'; p1++) {
    for (p2 = str2; *p2 != '\0'; p2++) {
      if (*p1 == *p2) return (s21_size_t)(p1 - str1);
    }
  }
  return (s21_size_t)(p1 - str1);
}