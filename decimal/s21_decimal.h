#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define AMOUNT_BITS 4
#define BITS_FOR_NUM 3
#define BITS_FOR_RATIO 1
#define NUMBER_OF_DIGITS_IN_BIT 32

#define MAX_DECIMAL 79228162514264337593543950335.0f
#define MAX_DECIMAL_INT 79228162514264337593543950335ULL
#define DECIMAL_ONE ((s21_decimal){{1, 0, 0, 0}})
#define SIGN_MASK 0x80000000
#define EXPONENT_MASK 0x00FF0000
#define INCORRECT_EXPONENT -1
#define INCORRECT_INPUT_VALUE -1

typedef struct {
  uint32_t bits[AMOUNT_BITS];
} s21_decimal;

typedef struct {
  unsigned int bits[3];
  unsigned zero1 : 16;
  unsigned expo : 8;
  unsigned zero2 : 7;
  unsigned sign : 1;
} s21_exposign;

typedef struct {
  unsigned int mantisse : 23;
  unsigned int expo : 8;
  unsigned int sign : 1;
} binaryfloat;

// Return codes
enum { OK = 0, TOO_BIG, TOO_SMALL, DIV_BY_ZERO };
enum { FALSE = 0, TRUE };
enum { CONVERSION_OK = 0, CONVERSION_ERROR };
enum { CALCULATION_OK = 0, CALCULATION_ERROR };

// Bit operations
#define get(x, y) ((s21_exposign*)x)->y
#define set_bit_1(x, y) ((x)->bits[(y) / 32] |= (1u << ((y) % 32)))

// Arithmetic
int s21_add(s21_decimal, s21_decimal, s21_decimal*);
int s21_sub(s21_decimal, s21_decimal, s21_decimal*);
int s21_mul(s21_decimal, s21_decimal, s21_decimal*);
int s21_div(s21_decimal, s21_decimal, s21_decimal*);

// Comparison
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// Conversion
int s21_from_int_to_decimal(int, s21_decimal*);
int s21_from_float_to_decimal(float, s21_decimal*);
int s21_from_decimal_to_int(s21_decimal, int*);
int s21_from_decimal_to_float(s21_decimal, float*);

// Rounding
int s21_floor(s21_decimal, s21_decimal*);
int s21_round(s21_decimal, s21_decimal*);
int s21_truncate(s21_decimal, s21_decimal*);
int s21_negate(s21_decimal, s21_decimal*);

// Helpers
int get_sign(s21_decimal);
void set_sign(s21_decimal*, int);
void clear_sign(s21_decimal*);
void set_scale(s21_decimal*, int);
int get_exp(s21_decimal);
int set_exp(s21_decimal*, int);
int get_bit(uint32_t, int);
int get_bit_from_decimal(const s21_decimal*, int);
int set_bit(uint32_t*, int, int);
int get_decimal_bit(s21_decimal, int);
int set_decimal_bit(s21_decimal*, int, int);
void init_result(s21_decimal*);
int normalize(s21_decimal*, s21_decimal*, s21_decimal*);
int add_dev(s21_decimal, s21_decimal, s21_decimal*, int*);
void sub_dev(s21_decimal, s21_decimal, s21_decimal*);
int double_d_mul(s21_decimal, s21_decimal, s21_decimal*, s21_decimal*);
int is_dec_correct(s21_decimal);
int isnull(s21_decimal);
int decrease_exponent(s21_decimal*);
int decrease_exponent_remainder(s21_decimal*, unsigned);
void prepare_div(s21_decimal*, s21_decimal*);
int mequal(s21_decimal, s21_decimal);
unsigned int mul_by_ten(s21_decimal*);
int madd(s21_decimal, s21_decimal, s21_decimal*);
int msub(s21_decimal, s21_decimal, s21_decimal*);
int increase_exponent(s21_decimal*);
int bank_round(s21_decimal*, int);
int merge_dev(s21_decimal*, s21_decimal, int*);
void invert(s21_decimal*);
int unidec(s21_decimal*, s21_decimal*);

#endif
