#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <stdarg.h>

struct list {
  int weight;
};

int s21_sscanf(const char *input, const char *format, ...);

int handle_decimal(struct list fmt, const char **input, int *out);
int handle_float(struct list fmt, const char **input, float *out);
int handle_string(struct list fmt, const char **input, char *dest);
int handle_char(const char **input, char *out);
int handle_unsigned(struct list fmt, const char **input, unsigned int *out);
int handle_pointer(const char **input, void **out);
int handle_exponential_extra(const char **input, double *out);
int handle_general_extra(const char **input, double *out);
int handle_octal_extra(struct list fmt, const char **input, int *out);
int handle_hex_extra(struct list fmt_extra, const char **input_extra,
                     unsigned int *out_extra, int uppercase);

#endif  // S21_SSCANF_H
