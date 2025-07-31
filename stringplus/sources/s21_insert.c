#include "../../src/s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = S21_NULL;
  if (src && str) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);

    if (start_index <= src_len) {
      res = (char *)calloc(src_len + str_len + 1, sizeof(char));
      if (res) {
        // копируем начало src до start_index
        for (s21_size_t i = 0; i < start_index; i++) {
          res[i] = src[i];
        }
        // вставляем str
        for (s21_size_t i = 0; i < str_len; i++) {
          res[start_index + i] = str[i];
        }
        // копируем оставшуюся часть src
        for (s21_size_t i = start_index; i < src_len; i++) {
          res[str_len + i] = src[i];
        }
      }
    }
  }
  return res;
}
