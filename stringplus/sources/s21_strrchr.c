#include "../../src/s21_string.h"

// need upgrade
char *s21_strrchr(const char *str, int c) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  const char *last = S21_NULL;
  char ch = (char)c;
  while (*str) {
    if (*str == ch) {
      last = str;
    }
    str++;
  }
  if (ch == '\0') {
    return (char *)str;
  }
  return (char *)last;
}