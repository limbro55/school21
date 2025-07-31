#include "../../src/s21_string.h"

// need upgrade
char *s21_strtok(char *str, const char *delim) {
  static char *next = S21_NULL;
  if (delim == S21_NULL) return S21_NULL;
  if (str != S21_NULL)
    next = str;
  else if (next == S21_NULL)
    return S21_NULL;
  while (*next && s21_strrchr(delim, *next) != S21_NULL) next++;
  if (*next == '\0') {
    next = S21_NULL;
    return S21_NULL;
  }
  char *token_start = next;
  while (*next && s21_strrchr(delim, *next) == S21_NULL) next++;
  if (*next) {
    *next = '\0';
    next++;
  } else
    next = S21_NULL;
  return token_start;
}