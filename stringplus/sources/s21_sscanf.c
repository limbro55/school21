#include "../../src/s21_sscanf.h"

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>

int handle_decimal(struct list fmt, const char **input, int *out) {
  int value = 0, sign = 1, count = 0;
  while (isspace(**input)) (*input)++;
  if (**input == '-') {
    sign = -1;
    (*input)++;
  } else if (**input == '+') {
    (*input)++;
  }
  while (isdigit(**input) && (fmt.weight == 0 || count < fmt.weight)) {
    value = value * 10 + (**input - '0');
    (*input)++;
    count++;
  }
  *out = sign * value;
  return count > 0;
}

int handle_float(struct list fmt, const char **input, float *out) {
  float value = 0.0f, divisor = 1.0f;
  int sign = 1, seen_dot = 0;
  while (isspace(**input)) (*input)++;
  if (**input == '-') {
    sign = -1;
    (*input)++;
  } else if (**input == '+') {
    (*input)++;
  }
  while ((isdigit(**input)) || (!seen_dot && **input == '.')) {
    if (**input == '.') {
      seen_dot = 1;
      (*input)++;
      continue;
    }
    value = value * 10 + (**input - '0');
    if (seen_dot) divisor *= 10.0f;
    (*input)++;
  }
  *out = sign * value / divisor;

  if (fmt.weight > 0) {
    int scale = 1;
    for (int i = 0; i < fmt.weight; i++) scale *= 10;
    *out = ((int)(*out * scale)) / (float)scale;
  }

  return 1;
}

int handle_string(struct list fmt, const char **input, char *out) {
  while (isspace(**input)) (*input)++;
  int i = 0;
  while (**input && !isspace(**input) && (fmt.weight == 0 || i < fmt.weight)) {
    out[i++] = *(*input)++;
  }
  out[i] = '\0';
  return i > 0;
}

int handle_char(const char **input, char *out) {
  while (isspace(**input)) (*input)++;
  if (**input) {
    *out = *(*input)++;
    return 1;
  }
  return 0;
}

int handle_unsigned(struct list fmt, const char **input, unsigned int *out) {
  unsigned int value = 0;
  int count = 0;
  while (isspace(**input)) (*input)++;
  while (isdigit(**input) && (fmt.weight == 0 || count < fmt.weight)) {
    value = value * 10 + (**input - '0');
    (*input)++;
    count++;
  }
  *out = value;
  return count > 0;
}

int handle_exponential_extra(const char **input, double *out) {
  double value = 0.0, frac = 1.0;
  int sign = 1, exp_sign = 1, exponent = 0, count = 0;
  while (isspace(**input)) (*input)++;
  if (**input == '-') {
    sign = -1;
    (*input)++;
  } else if (**input == '+') {
    (*input)++;
  }
  while ((**input >= '0' && **input <= '9') || **input == '.') {
    if (**input == '.') {
      (*input)++;
      while (isdigit(**input)) {
        value += (**input - '0') / (frac *= 10);
        (*input)++;
        count++;
      }
      break;
    } else {
      value = value * 10 + (**input - '0');
      (*input)++;
      count++;
    }
  }

  if (**input == 'e' || **input == 'E') {
    (*input)++;
    if (**input == '-') {
      exp_sign = -1;
      (*input)++;
    } else if (**input == '+') {
      (*input)++;
    }
    while (isdigit(**input)) {
      exponent = exponent * 10 + (**input - '0');
      (*input)++;
    }
  }

  *out = sign * value * pow(10, exp_sign * exponent);
  return count > 0;
}

int handle_general_extra(const char **input, double *out) {
  return handle_exponential_extra(input, out);
}

int handle_octal_extra(struct list fmt, const char **input, int *out) {
  int value = 0, count = 0;
  while (isspace(**input)) (*input)++;
  while (**input >= '0' && **input <= '7' &&
         (fmt.weight == 0 || count < fmt.weight)) {
    value = value * 8 + (**input - '0');
    (*input)++;
    count++;
  }
  *out = value;
  return count > 0;
}

int handle_hex_extra(struct list fmt, const char **input, unsigned int *out,
                     int uppercase) {
  (void)uppercase;
  unsigned int value = 0;
  int count = 0;
  while (isspace(**input)) (*input)++;
  while ((**input >= '0' && **input <= '9') ||
         (**input >= 'a' && **input <= 'f') ||
         (**input >= 'A' && **input <= 'F')) {
    if (fmt.weight != 0 && count >= fmt.weight) break;
    if (**input >= '0' && **input <= '9')
      value = value * 16 + (**input - '0');
    else if (**input >= 'a' && **input <= 'f')
      value = value * 16 + (**input - 'a' + 10);
    else if (**input >= 'A' && **input <= 'F')
      value = value * 16 + (**input - 'A' + 10);
    (*input)++;
    count++;
  }
  *out = value;
  return count > 0;
}

int handle_pointer(const char **input, void **out) {
  while (isspace(**input)) (*input)++;
  if (**input == '0' && ((*input)[1] == 'x' || (*input)[1] == 'X')) {
    *input += 2;
  }
  unsigned long value = 0;
  int count = 0;
  while (isxdigit(**input)) {
    char c = **input;
    value <<= 4;
    if (isdigit(c))
      value += c - '0';
    else if (c >= 'a' && c <= 'f')
      value += c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
      value += c - 'A' + 10;
    (*input)++;
    count++;
  }
  *out = (void *)(uintptr_t)value;
  return count > 0;
}

// основной sscanf
int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int assigned = 0;
  const char *f = format;
  const char *s = str;

  while (*f) {
    if (isspace(*f)) {
      while (isspace(*s)) s++;
      f++;
      continue;
    }
    if (*f != '%') {
      if (*f != *s) break;
      f++, s++;
      continue;
    }

    f++;
    struct list fmt = {0};
    if (isdigit(*f)) {
      fmt.weight = 0;
      while (isdigit(*f)) {
        fmt.weight = fmt.weight * 10 + (*f - '0');
        f++;
      }
    }

    char spec = *f++;
    void *ptr = va_arg(args, void *);
    int res = 0;

    switch (spec) {
      case 'd':
        res = handle_decimal(fmt, &s, (int *)ptr);
        break;
      case 'u':
        res = handle_unsigned(fmt, &s, (unsigned int *)ptr);
        break;
      case 'f':
        res = handle_float(fmt, &s, (float *)ptr);
        break;
      case 'e':
        res = handle_exponential_extra(&s, (double *)ptr);
        break;
      case 'g':
        res = handle_general_extra(&s, (double *)ptr);
        break;
      case 's':
        res = handle_string(fmt, &s, (char *)ptr);
        break;
      case 'c':
        res = handle_char(&s, (char *)ptr);
        break;
      case 'o':
        res = handle_octal_extra(fmt, &s, (int *)ptr);
        break;
      case 'x':
      case 'X':
        res = handle_hex_extra(fmt, &s, (unsigned int *)ptr, spec == 'X');
        break;
      case 'p':
        res = handle_pointer(&s, (void **)ptr);
        break;
      default:
        res = 0;
        break;
    }

    if (res > 0)
      assigned += 1;
    else
      break;

    fmt.weight = 0;
  }

  va_end(args);
  return assigned;
}
