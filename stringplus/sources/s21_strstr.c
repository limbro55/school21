#include "../../src/s21_string.h"

// need upgrade
char *s21_strstr(const char *haystack, const char *needle) {
  if (haystack == S21_NULL || needle == S21_NULL) {
    return S21_NULL;
  }
  if (*needle == '\0') {
    return (char *)haystack;
  }

  for (; *haystack != '\0'; haystack++) {
    if (*haystack == *needle) {
      const char *h = haystack;
      const char *n = needle;
      while (*h && *n && (*h == *n)) {
        h++;
        n++;
      }
      if (*n == '\0') {
        return (char *)haystack;
      }
    }
  }
  return S21_NULL;
}