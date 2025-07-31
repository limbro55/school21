#include "../../src/s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL) return S21_NULL;

  s21_size_t src_len = s21_strlen(src);
  s21_size_t start = 0, end = src_len;

  while (start < end && s21_strchr(trim_chars, src[start]) != S21_NULL) start++;
  while (end > start && s21_strchr(trim_chars, src[end - 1]) != S21_NULL) end--;

  s21_size_t new_len = end - start;
  char *trimmed_str = (char *)malloc(new_len + 1);
  if (trimmed_str == S21_NULL) return S21_NULL;

  s21_memcpy(trimmed_str, src + start, new_len);
  trimmed_str[new_len] = '\0';

  return trimmed_str;
}
