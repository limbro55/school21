#include "../../src/s21_sprintf.h"

#include <math.h>
#include <stdarg.h>
#include <stdint.h>

#include "../../src/s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  int written = 0;
  const char *p;
  va_start(args, format);
  for (p = format; *p != '\0'; p++) {
    if (*p == '%') {
      p++;
      if (*p == '\0') break;

      int width = 0, precision = 6, left_align = 0,
          zero_pad = 0;  // инициализация
      scanflags(&p, &width, &precision, &left_align, &zero_pad);

      if (*p == '\0') break;  // добавлена защита от выхода за пределы строки

      parse_token(&args, &p, str, &written, width, precision, left_align,
                  zero_pad);
    } else {
      str[written++] = *p;
    }
    if (written >= 512) {
      break;
    }
  }
  str[written] = '\0';
  va_end(args);
  return written;
}

char *s21_strcpy(char *dest, const char *src) {
  char *start = dest;
  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return start;
}

void int_to_str(int num, char *str, int *index) {
  if (num == 0) {
    str[(*index)++] = '0';
    return;
  }
  if (num < 0) {
    str[(*index)++] = '-';
    num = -num;
  }
  int start_index = *index;
  while (num > 0) {
    str[(*index)++] = '0' + (num % 10);
    num /= 10;
  }
  for (int i = start_index, j = *index - 1; i < j; i++, j--) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}

void trim_trailing_zeros(char *str) {
  char *dot = s21_strchr(str, '.');
  if (!dot) return;
  char *end = str + s21_strlen(str) - 1;
  while (end > dot && *end == '0') *end-- = '\0';
  if (*end == '.') *end = '\0';
}

void sci_notation(double num, char *str, int *pos, char expchr, int precision) {
  if (num == 0.0) {
    str[(*pos)++] = '0';
    str[(*pos)++] = '.';
    for (int i = 0; i < precision; i++) {
      str[(*pos)++] = '0';
    }
    str[(*pos)++] = expchr;
    str[(*pos)++] = '+';
    str[(*pos)++] = '0';
    str[(*pos)++] = '0';
    str[*pos] = '\0';
    return;
  }

  if (num < 0) {
    str[(*pos)++] = '-';
    num = -num;
  }

  int exponent = 0;
  double normalized = num;
  while (normalized >= 10.0) {
    normalized /= 10.0;
    exponent++;
  }
  while (normalized < 1.0) {
    normalized *= 10.0;
    exponent--;
  }

  char mantissa[64] = {0};
  int mantissa_pos = 0;

  int int_part = (int)normalized;
  int_to_str(int_part, mantissa, &mantissa_pos);
  mantissa[mantissa_pos++] = '.';

  double fraction = normalized - int_part;
  for (int i = 0; i < precision; i++) {
    fraction *= 10;
    int digit = (int)fraction;
    mantissa[mantissa_pos++] = '0' + digit;
    fraction -= digit;
  }
  mantissa[mantissa_pos] = '\0';

  s21_strcpy(str + *pos, mantissa);
  *pos += s21_strlen(mantissa);

  str[(*pos)++] = expchr;
  str[(*pos)++] = (exponent >= 0) ? '+' : '-';

  int exp_val = exponent >= 0 ? exponent : -exponent;
  if (exp_val < 10) str[(*pos)++] = '0';
  int exp_digits = 0;
  char expbuf[8] = {0};
  int_to_str(exp_val, expbuf, &exp_digits);
  s21_strcpy(str + *pos, expbuf);
  *pos += exp_digits;
  str[*pos] = '\0';
}

void double_to_str(double num, char *str, int *index, int precision) {
  if (num < 0) {
    str[(*index)++] = '-';
    num = -num;
  }
  int whole_part = (int)num;
  double fractional_part = num - whole_part;
  int_to_str(whole_part, str, index);
  str[(*index)++] = '.';
  for (int i = 0; i < precision; i++) {
    fractional_part *= 10;
    int digit = (int)fractional_part;
    str[(*index)++] = '0' + digit;
    fractional_part -= digit;
  }
  str[*index] = '\0';
}

void optimize_float_format(double num, char *str, int *index, int precision,
                           int uppercase) {
  int exp = 0;
  double mag = fabs(num);

  if (mag == 0.0) {
    if (uppercase) {
      sci_notation(num, str, index, 'E', precision);
    } else {
      sci_notation(num, str, index, 'e', precision);
    }
    return;
  }

  while (mag >= 10.0) {
    mag /= 10.0;
    exp++;
  }
  while (mag < 1.0 && mag > 0.0) {
    mag *= 10.0;
    exp--;
  }

  int start = *index;
  if (exp >= -4 && exp < precision) {
    double_to_str(num, str, index, precision);
    trim_trailing_zeros(str + start);  // только для %g/%G
  } else {
    sci_notation(num, str, index, uppercase ? 'E' : 'e', precision);
  }
}

void uint_tobase(unsigned int num, char *str, int *index, int base) {
  if (num == 0) {
    str[(*index)++] = '0';
    str[*index] = '\0';
    return;
  }

  int start = *index;
  while (num > 0) {
    int digit = num % base;
    str[(*index)++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
    num /= base;
  }
  str[*index] = '\0';

  for (int i = start, j = *index - 1; i < j; i++, j--) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
  }
}

void ptrhex(uint64_t num, char *str, int *index) {
  if (num == 0) {
    s21_strcpy(str + *index, "(nil)");
    *index += 5;
    return;
  }

  str[(*index)++] = '0';
  str[(*index)++] = 'x';
  int start = *index;

  while (num > 0) {
    int digit = num % 16;
    str[(*index)++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
    num /= 16;
  }

  str[*index] = '\0';
  for (int i = start, j = *index - 1; i < j; i++, j--) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
  }
}

void parse_token(va_list *args, const char **p, char *str, int *written,
                 int width, int precision, int left_align, int zero_pad) {
  char buffer[512] = {0};
  int buffer_index = 0;

  if (**p == '\0') return;  // добавленная защита

  switch (**p) {
    case '%':
      buffer[buffer_index++] = '%';
      break;
    case 'c':
      buffer[buffer_index++] = (char)va_arg(*args, int);
      break;
    case 'd':
    case 'i': {
      int i = va_arg(*args, int);
      int_to_str(i, buffer, &buffer_index);
      break;
    }
    case 'f': {
      double f = va_arg(*args, double);
      double_to_str(f, buffer, &buffer_index, precision);
      break;
    }
    case 'e':
    case 'E': {
      double d = va_arg(*args, double);
      sci_notation(d, buffer, &buffer_index, (**p == 'E') ? 'E' : 'e',
                   precision);
      break;
    }
    case 'g':
    case 'G': {
      double f = va_arg(*args, double);
      optimize_float_format(f, buffer, &buffer_index, precision, (**p == 'G'));
      break;
    }
    case 'u': {
      unsigned int u = va_arg(*args, unsigned int);
      uint_tobase(u, buffer, &buffer_index, 10);
      break;
    }
    case 'x': {
      unsigned int x = va_arg(*args, unsigned int);
      uint_tobase(x, buffer, &buffer_index, 16);
      break;
    }
    case 'X': {
      unsigned int X = va_arg(*args, unsigned int);
      uint_tobase(X, buffer, &buffer_index, 16);
      // преобразуем буквы в верхний регистр
      for (int i = 0; i < buffer_index; i++) {
        if (buffer[i] >= 'a' && buffer[i] <= 'f') {
          buffer[i] = buffer[i] - 'a' + 'A';
        }
      }
      break;
    }
    case 'p': {
      void *ptr = va_arg(*args, void *);
      ptrhex((uint64_t)(uintptr_t)ptr, buffer, &buffer_index);
      break;
    }
    case 's': {
      char *s = va_arg(*args, char *);
      if (s == NULL) s = "(null)";
      while (*s && buffer_index < 511) {
        buffer[buffer_index++] = *s++;
      }
      break;
    }
    case 'o': {
      unsigned int o = va_arg(*args, unsigned int);
      uint_tobase(o, buffer, &buffer_index, 8);
      break;
    }

    default:
      return;
  }
  buffer[buffer_index] = '\0';

  int pad_len = width - buffer_index;
  if (pad_len < 0) pad_len = 0;

  if (!left_align) {
    char pad_char = zero_pad ? '0' : ' ';
    for (int i = 0; i < pad_len; i++) {
      str[(*written)++] = pad_char;
    }
  }
  for (int i = 0; i < buffer_index; i++) {
    str[(*written)++] = buffer[i];
  }
  if (left_align) {
    for (int i = 0; i < pad_len; i++) {
      str[(*written)++] = ' ';
    }
  }
}

void scanflags(const char **p, int *width, int *precision, int *left_align,
               int *zero_pad) {
  *width = 0;
  *precision = 6;  // дефолтная точность
  *left_align = 0;
  *zero_pad = 0;

  while (**p == '-' || **p == '0') {
    if (**p == '-') *left_align = 1;
    if (**p == '0') *zero_pad = 1;
    (*p)++;
  }
  while (**p >= '0' && **p <= '9') {
    *width = (*width) * 10 + (**p - '0');
    (*p)++;
  }
  if (**p == '.') {
    (*p)++;
    *precision = 0;
    while (**p >= '0' && **p <= '9') {
      *precision = (*precision) * 10 + (**p - '0');
      (*p)++;
    }
  }
}
