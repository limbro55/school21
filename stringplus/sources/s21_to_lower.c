#include "../../src/s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;

  s21_size_t len = s21_strlen(str);
  char *output_str = (char *)malloc(len + 1);
  if (output_str == S21_NULL) return S21_NULL;

  for (s21_size_t i = 0; i < len; i++) {
    output_str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : str[i];
  }

  output_str[len] = '\0';
  return output_str;
}