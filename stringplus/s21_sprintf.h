#include "s21_string.h"

#define BUFFER_SIZE 1024

int s21_sprintf(char *str, const char *format, ...);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *dest_ptr, const char *src_ptr);
void int_to_str(int num, char *str, int *index);
void sci_notation(double num, char *str, int *index, char exp_char,
                  int precision);
void format_uint_to_str(unsigned int num, char *str, int *index, int base);
void double_to_str(double num, char *str, int *index, int precision);
// format_g
void optimize_float_format(double num, char *str, int *index, int precision,
                           int uppercase);
void uint_tobase(unsigned int num, char *str, int *index, int base);
// uint for str for p
void ptrhex(uint64_t num, char *str, int *index);
void parse_token(va_list *args, const char **p, char *str, int *written,
                 int width, int precision, int left_align, int zero_pad);
void scanflags(const char **p, int *width, int *precision, int *left_align,
               int *zero_pad);
void flush_buffer(char *str, int *written, char *buffer, int buffer_index,
                  int width, int left_align, int zero_pad);