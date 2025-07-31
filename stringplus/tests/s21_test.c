
#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../src/s21_sprintf.h"
#include "../../src/s21_sscanf.h"
#include "../../src/s21_string.h"

void run_testcase(Suite *testcase);
void run_tests(void);

Suite *suite_memcmp(void);
Suite *suite_memchr(void);
Suite *suite_memcpy(void);
Suite *suite_memset(void);
Suite *suite_strchr(void);
Suite *suite_strncat(void);
Suite *suite_strncmp(void);
Suite *suite_strncpy(void);
Suite *suite_strcspn(void);
Suite *suite_strlen(void);
Suite *suite_strpbrk(void);
Suite *suite_strrchr(void);
Suite *suite_strstr(void);
Suite *suite_strtok(void);
Suite *suite_sprintf(void);
Suite *suite_sscanf(void);
Suite *suite_strerror(void);
Suite *suite_bonus(void);

START_TEST(zero) {
  char str1[] = "";
  char str2[] = "";
  int n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(one_byte) {
  char str1[] = "abc";
  char str2[] = "abd";
  int n = 3;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(zero_bytes) {
  char str1[] = "Hellp";
  char str2[] = "Hellp";
  int n = 3;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(length_diff) {
  char str1[] = "Hellp";
  char str2[] = "Hellpppp";
  int n = 5;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(zero_byte) {
  char str1[] = "\x00\x01";
  char str2[] = "\x00\x02";
  int n = 2;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(long_eq_string) {
  char str1[] = "Long string for testing memcmp function.";
  char str2[] = "Long string for testing memcmp function.";
  int n = 39;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(long_string) {
  char str1[] = "Long string for testing memcmp function.";
  char str2[] = "Long string for testing memcmp function";
  int n = 39;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(two_byte_long_two_num) {
  char str1[] = "13";
  char str2[] = "1234";
  int n = 2;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(s21_memchr_test_zero) {
  char *str = "This is a test";
  ck_assert_ptr_eq(s21_memchr(str, 's', 0), memchr(str, 's', 0));
}
END_TEST

START_TEST(s21_memchr_test_two) {
  char *str = "This is a test";
  ck_assert_ptr_eq(s21_memchr(str, 's', 2), memchr(str, 's', 2));
}
END_TEST

START_TEST(s21_memchr_test_full) {
  char *str = "This is a test";
  ck_assert_ptr_eq(s21_memchr(str, 's', 15), memchr(str, 's', 15));
}
END_TEST

START_TEST(s21_memchr_test_not_found) {
  char *str = "This is a test";
  ck_assert_ptr_eq(s21_memchr(str, 'u', 15), memchr(str, 'u', 15));
}
END_TEST

START_TEST(s21_memchr_test_space) {
  char *str = "This is a test";
  ck_assert_ptr_eq(s21_memchr(str, ' ', 8), memchr(str, ' ', 8));
}
END_TEST

START_TEST(s21_memcpy_test_zero) {
  char src[] = "This is a test";
  char dest1[50] = {0};
  char dest2[50] = {0};

  s21_memcpy(dest1, src, 0);
  memcpy(dest2, src, 0);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(s21_memcpy_test_full_copy) {
  char src[] = "This is a test";
  char dest1[50] = {0};
  char dest2[50] = {0};

  s21_memcpy(dest1, src, 15);
  memcpy(dest2, src, 15);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(s21_memcpy_test_partial_copy) {
  char src[] = "This is a test";
  char dest1[50] = {0};
  char dest2[50] = {0};

  s21_memcpy(dest1, src, 4);
  memcpy(dest2, src, 4);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_s21_memset_zero) {
  char str[10] = "abcdefghi";
  char str2[10] = "abcdefghi";
  s21_memset(str, '\0', 5);
  memset(str2, '\0', 5);
  ck_assert_str_eq(str, str2);
}
END_TEST
START_TEST(test_s21_memset_fill) {
  char str[10] = "abcdefghi";
  char str2[10] = "abcdefghi";
  s21_memset(str, 'x', 5);
  memset(str2, 'x', 5);
  ck_assert_str_eq(str, str2);
}
END_TEST
START_TEST(test_s21_memset_full) {
  char str[10] = "abcdefghi";
  char str2[10] = "abcdefghi";
  s21_memset(str, 'z', 9);
  memset(str2, 'z', 9);
  ck_assert_str_eq(str, str2);
}
END_TEST
START_TEST(test_s21_memset_partial) {
  char str[10] = "abcdefghi";
  char str2[10] = "abcdefghi";
  s21_memset(str, 'y', 3);
  memset(str2, 'y', 3);
  ck_assert_str_eq(str, str2);
}
END_TEST

START_TEST(test_s21_memset_tabs) {
  char str[10] = "abcdefghi";
  char str2[10] = "abcdefghi";
  s21_memset(str, '\t', 9);
  memset(str2, '\t', 9);
  ck_assert_str_eq(str, str2);
}
END_TEST

START_TEST(s21_strchr_test_first_occurrence) {
  char *str = "This is a test";
  ck_assert_ptr_eq(s21_strchr(str, 's'), strchr(str, 's'));
}
END_TEST

START_TEST(s21_strchr_test_not_found) {
  char *str = "This is a test";
  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
}
END_TEST

START_TEST(s21_strchr_test_last_occurrence) {
  char *str = "This is a test";
  ck_assert_ptr_eq(s21_strchr(str, 't'), strchr(str, 't'));
}
END_TEST

START_TEST(s21_strchr_test_null_character) {
  char *str = "This is a test";
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

START_TEST(s21_strchr_test_empty_string) {
  char *str = "";
  ck_assert_ptr_eq(s21_strchr(str, 'a'), strchr(str, 'a'));
}
END_TEST

START_TEST(s21_strncat_test_basic_concatenation) {
  char dest[50] = "Hello, ";
  char src[] = "world!";

  s21_strncat(dest, src, 6);
  char expected[] = "Hello, world!";
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(s21_strncat_test_partial_concatenation) {
  char dest[50] = "Hello, ";
  char src[] = "world!";

  s21_strncat(dest, src, 3);
  char expected[] = "Hello, wor";
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(s21_strncat_test_empty_source) {
  char dest[50] = "Hello, ";
  char src[] = "";

  s21_strncat(dest, src, 0);
  char expected[] = "Hello, ";
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(s21_strncat_test_empty_destination) {
  char dest[50] = "";
  char src[] = "world!";

  s21_strncat(dest, src, 6);
  char expected[] = "world!";
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(s21_strncat_test_no_space_in_dest) {
  char dest[50] = "Hello, ";
  char src[] = "world!";

  s21_strncat(dest, src, 10);
  char expected[] = "Hello, world!";
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(s21_strncat_test_zero_length) {
  char dest[50] = "Hello, ";
  char src[] = "world!";

  s21_strncat(dest, src, 0);
  char expected[] = "Hello, ";
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(s21_strncmp_test_equal_strings) {
  char str1[] = "Hello, World!";
  char str2[] = "Hello, World!";

  ck_assert_int_eq(s21_strncmp(str1, str2, 13), strncmp(str1, str2, 13));
}
END_TEST

START_TEST(s21_strncmp_test_partial_equal_strings) {
  char str1[] = "Hello, World!";
  char str2[] = "Hello, Worlz!";
  int buff1 = s21_strncmp(str1, str2, 5);
  int buff2 = strncmp(str1, str2, 5);
  ck_assert_int_eq(buff1, buff2);
}
END_TEST

START_TEST(s21_strncmp_test_different_length) {
  char str1[] = "Hello";
  char str2[] = "Hello, World!";
  int buff1 = s21_strncmp(str1, str2, 5);
  int buff2 = strncmp(str1, str2, 5);

  ck_assert_int_eq(buff1, buff2);
}
END_TEST

START_TEST(s21_strncmp_test_case_sensitive) {
  char str1[] = "Hello, World!";
  char str2[] = "hello, world!";

  ck_assert_int_eq(s21_strncmp(str1, str2, 13), strncmp(str1, str2, 13));
}
END_TEST

START_TEST(s21_strncmp_test_empty_strings) {
  char str1[] = "";
  char str2[] = "";

  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
}
END_TEST

START_TEST(s21_strncmp_test_empty_dest_string) {
  char str1[10] = " ";
  char str2[10] = "Hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(s21_strncmp_test_empty_source_string) {
  char str1[10] = "Hello";
  char str2[10] = " ";

  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(s21_strncmp_test_again) {
  char str1[] = "Hi";
  char str2[] = "Hi there!";

  ck_assert_int_eq(s21_strncmp(str1, str2, 2), strncmp(str1, str2, 2));
}
END_TEST

START_TEST(s21_strncpy_test_basic_copy) {
  char dest[50];
  char src[] = "Hello, World!";

  s21_strncpy(dest, src, 13);
  dest[13] = '\0';
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(s21_strncpy_test_partial_copy) {
  char dest[50];
  char src[] = "Hello, World!";

  s21_strncpy(dest, src, 5);
  dest[5] = '\0';
  char expected[] = "Hello";
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(s21_strncpy_test_empty_source) {
  char dest[50];
  char src[] = "";

  s21_strncpy(dest, src, 10);
  dest[0] = '\0';
  ck_assert_str_eq(dest, "");
}
END_TEST

START_TEST(s21_strncpy_test_empty_destination) {
  char dest[50] = "Initial Text";
  char src[] = "New Text";

  s21_strncpy(dest, src, 8);
  dest[8] = '\0';
  char expected[] = "New Text";
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(s21_strncpy_test_more_length_than_source) {
  char dest[50];
  char src[] = "Hi";

  s21_strncpy(dest, src, 10);
  dest[10] = '\0';

  char expected[] = "Hi";
  ck_assert_str_eq(dest, expected);
  ck_assert_int_eq(dest[2], '\0');
}
END_TEST

START_TEST(s21_strncpy_test_no_null_termination) {
  char dest[50];
  char src[] = "Hello";

  s21_strncpy(dest, src, 3);
  dest[3] = '\0';
  char expected[] = "Hel";
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(s21_strncpy_test_zero_length) {
  char dest[50] = "Initial";
  char src[] = "New Data";

  s21_strncpy(dest, src, 0);
  ck_assert_str_eq(dest, "Initial");
}
END_TEST

START_TEST(s21_strcspn_test_basic) {
  char str1[] = "hello world";
  char str2[] = "aeiou";

  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t res = strcspn(str1, str2);
  ck_assert_int_eq(result, res);
}
END_TEST

START_TEST(s21_strcspn_test_no_match) {
  char str1[] = "abcdef";
  char str2[] = "xyz";

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, 6);  // No matches
}
END_TEST

START_TEST(s21_strcspn_test_with_match_at_start) {
  char str1[] = "abcdef";
  char str2[] = "adef";  // 'a' is in str2, first letter

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, 0);  // Immediate match
}
END_TEST

START_TEST(s21_strcspn_test_match_after_some_chars) {
  char str1[] = "1234567890";
  char str2[] = "7890";  // First match is '7'

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, 6);  // First match at index 6
}
END_TEST

START_TEST(s21_strcspn_test_empty_first_string) {
  char str1[] = "";
  char str2[] = "abc";

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, 0);  // Empty str1
}
END_TEST

START_TEST(s21_strcspn_test_empty_second_string) {
  char str1[] = "abc";
  char str2[] = "";

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(s21_strcspn_test_identical_strings) {
  char str1[] = "abcde";
  char str2[] = "abcde";

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_strcspn_test_no_chars_in_first_string) {
  char str1[] = "qwerty";
  char str2[] = "abc";

  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, 6);
}
END_TEST

START_TEST(test_empty_string) {
  char test[] = "";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST

START_TEST(test_single_character) {
  char test[] = "A";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST

START_TEST(test_multiple_characters) {
  char test[] = "Hello, world!";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST

START_TEST(test_spaces_only) {
  char test[] = "   ";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST

START_TEST(test_various_characters) {
  char test[] = "123!@#";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST

START_TEST(test_newline_character) {
  char test[] = "Hello\nWorld";
  ck_assert_int_eq(s21_strlen(test), strlen(test));
}
END_TEST

START_TEST(test_null_character_in_middle) {
  char test[] = "Hello\0World";  // Правильная длина равна 5
  ck_assert_int_eq(s21_strlen(test), 5);
}
END_TEST

START_TEST(s21_strpbrk_test_first_string_contains_matching_chars) {
  const char *str1 = "hello world";
  const char *str2 = "ow";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_no_chars_in_first_string) {
  const char *str1 = "example string";
  const char *str2 = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_no_matching_chars) {
  const char *str1 = "abcdef";
  const char *str2 = "ghijk";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_last_chars_match) {
  const char *str1 = "abcde";
  const char *str2 = "de";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_multiple_matches) {
  const char *str1 = "hello";
  const char *str2 = "elo";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_empty_first_string) {
  const char *str1 = "";
  const char *str2 = "abc";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_empty_second_string) {
  const char *str1 = "abc";
  const char *str2 = "";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_last_character_match) {
  const char *str1 = "abcdef";
  const char *str2 = "f";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_first_characters_match) {
  const char *str1 = "abcdef";
  const char *str2 = "abc";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_multiple_match_in_second_string) {
  const char *str1 = "abcde";
  const char *str2 = "deabcd";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strrchr_test_char_exists_in_string) {
  const char *str = "hello, world";
  char ch = 'o';
  ck_assert_str_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

START_TEST(s21_strrchr_test_char_does_not_exist) {
  const char *str = "hello, world";
  char ch = 'x';
  ck_assert_ptr_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

START_TEST(s21_strrchr_test_last_character_match) {
  const char *str = "hello";
  char ch = 'o';
  ck_assert_str_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

START_TEST(s21_strrchr_test_first_character_match) {
  const char *str = "abcde";
  char ch = 'a';
  ck_assert_str_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

START_TEST(s21_strrchr_test_empty_string) {
  const char *str = "";
  char ch = 'a';
  ck_assert_ptr_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

START_TEST(s21_strrchr_test_null_character) {
  const char *str = "string with null char\0here";
  ck_assert_str_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(s21_strstr_test_needle_exists_in_haystack) {
  const char *haystack = "Hello, world!";
  const char *needle = "world";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(s21_strstr_test_needle_does_not_exist) {
  const char *haystack = "Hello, world!";
  const char *needle = "foo";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(s21_strstr_test_empty_needle) {
  const char *haystack = "Hello, world!";
  const char *needle = "";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(s21_strstr_test_empty_haystack) {
  const char *haystack = "";
  const char *needle = "a";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(s21_strstr_test_haystack_equals_needle) {
  const char *haystack = "same";
  const char *needle = "same";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(s21_strstr_test_partial_match) {
  const char *haystack = "ababcabc";
  const char *needle = "bca";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(s21_strtok_test_basic) {
  char str1[] = "Hello,World,This,Is,A,Test";
  char str2[] = "Hello,World,This,Is,A,Test";
  const char delim[] = ",";
  char *token1 = strtok(str1, delim);
  char *token2 = s21_strtok(str2, delim);

  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = strtok(NULL, delim);
    token2 = s21_strtok(NULL, delim);
  }

  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(s21_strtok_test_no_delimiters) {
  char str1[] = "HelloWorldThisIsATest";
  char str2[] = "HelloWorldThisIsATest";
  const char delim[] = ",";
  char *token1 = strtok(str1, delim);
  char *token2 = s21_strtok(str2, delim);

  ck_assert_str_eq(token1, token2);
  ck_assert_ptr_eq(strtok(NULL, delim), NULL);
  ck_assert_ptr_eq(s21_strtok(NULL, delim), NULL);
}
END_TEST

START_TEST(s21_strtok_test_multiple_delimiters) {
  char str1[] = "Hello,,World,,,This,Is,A,Test";
  char str2[] = "Hello,,World,,,This,Is,A,Test";
  const char delim[] = ",";
  char *token1 = strtok(str1, delim);
  char *token2 = s21_strtok(str2, delim);

  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = strtok(NULL, delim);
    token2 = s21_strtok(NULL, delim);
  }

  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(s21_strtok_test_end_of_string) {
  char str[] = "Hello World";
  char *token;

  token = s21_strtok(str, " ");  // Разделитель - пробел
  ck_assert_str_eq(token, "Hello");
  token = s21_strtok(NULL, " ");
  ck_assert_str_eq(token, "World");
  token = s21_strtok(NULL, " ");
  ck_assert_ptr_eq(token, NULL);  // Должно вернуть NULL
}
END_TEST

START_TEST(s21_strtok_test_empty_string) {
  char str[] = "";
  char *token;

  token = s21_strtok(str, " ");   // Разделитель - пробел
  ck_assert_ptr_eq(token, NULL);  // Должно вернуть NULL
}

END_TEST
START_TEST(test_s21_strerror_no_such_file) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
}
END_TEST
START_TEST(test_s21_strerror_io_error) {
  ck_assert_str_eq(s21_strerror(10), strerror(10));
}
END_TEST

START_TEST(test_s21_strerror_unknown_error) {
  const char *expected = "Unknown error -1";

  const char *actual = s21_strerror(-1);

  ck_assert_str_eq(actual, expected);
}
END_TEST
START_TEST(test_format_g_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%g", 12345.6789);
  s21_sprintf(buffer, "%g", 12345.6789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_g_small) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%g", 0.00012345);
  s21_sprintf(buffer, "%g", 0.00012345);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_g_negative) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%g", -9876.54321);
  s21_sprintf(buffer, "%g", -9876.54321);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_g_large) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%g", 12354.0);
  s21_sprintf(buffer, "%g", 12354.0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_g_scientific) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%g", 3e8);
  s21_sprintf(buffer, "%g", 3e8);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_G_zero) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%G", 0.0);
  s21_sprintf(buffer, "%G", 0.0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_G_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%G", 12345.6789);
  s21_sprintf(buffer, "%G", 12345.6789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_G_small) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%G", 0.00012345);
  s21_sprintf(buffer, "%G", 0.00012345);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_G_negative) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%G", -9876.54321);
  s21_sprintf(buffer, "%G", -9876.54321);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_c_single_character) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%c", 'A');
  s21_sprintf(buffer, "%c", 'A');
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_c_lowercase_character) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%c", 'b');
  s21_sprintf(buffer, "%c", 'b');
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_c_special_character) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%c", '@');
  s21_sprintf(buffer, "%c", '@');
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_c_numeric_character) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%c", '5');
  s21_sprintf(buffer, "%c", '5');
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_c_space_character) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%c", ' ');
  s21_sprintf(buffer, "%c", ' ');
  ck_assert_str_eq(buffer, expected);
}
END_TEST
START_TEST(test_format_f_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%f", 12345.6789);
  s21_sprintf(buffer, "%f", 12345.6789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_f_negative) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%f", -9876.54321);
  s21_sprintf(buffer, "%f", -9876.54321);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_f_zero) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%f", 0.0);
  s21_sprintf(buffer, "%f", 0.0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_f_small) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%f", 0.00012345);
  s21_sprintf(buffer, "%f", 0.00012345);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_f_large) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%f", 123456789.0);
  s21_sprintf(buffer, "%f", 123456789.0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_f_precision) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%.2f", 3.14159);
  s21_sprintf(buffer, "%.2f", 3.14159);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_f_negative_precision) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%.3f", -2.71828);
  s21_sprintf(buffer, "%.3f", -2.71828);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_o_zero) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%o", 0);
  s21_sprintf(buffer, "%o", 0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_o_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%o", 8);
  s21_sprintf(buffer, "%o", 8);
  ck_assert_str_eq(buffer, expected);  // 8 в восьмеричной системе
}
END_TEST

START_TEST(test_format_o_large_number) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%o", 255);
  s21_sprintf(buffer, "%o", 255);
  ck_assert_str_eq(buffer, expected);  // 255 в восьмеричной системе
}
END_TEST

START_TEST(test_format_o_negative_number) {
  char buffer[128];
  char expected[128];
  unsigned int num = -1;  // Преобразуем отрицательное значение в беззнаковое
  sprintf(expected, "%o", num);
  s21_sprintf(buffer, "%o", num);
  ck_assert_str_eq(
      buffer, expected);  // -1 в восьмеричной системе (для 32-битного unsigned)
}
END_TEST

START_TEST(test_format_o_large_value) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%o", 1024);
  s21_sprintf(buffer, "%o", 1024);
  ck_assert_str_eq(buffer, expected);  // 1024 в восьмеричной системе
}
END_TEST

START_TEST(test_format_e_zero) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%E", 0.0);
  s21_sprintf(buffer, "%E", 0.0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_e_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%e", 12345.6789);
  s21_sprintf(buffer, "%e", 12345.6789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_e_negative) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%e", -9876.54321);
  s21_sprintf(buffer, "%e", -9876.54321);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_e_precision) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%.2e", 3.14159);
  s21_sprintf(buffer, "%.2e", 3.14159);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_e_negative_precision) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%.3e", -2.71828);
  s21_sprintf(buffer, "%.3e", -2.71828);
  ck_assert_str_eq(buffer, expected);
}
END_TEST
START_TEST(test_format_E_zero) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%E", 0.0);
  s21_sprintf(buffer, "%E", 0.0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_E_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%E", 12345.6789);
  s21_sprintf(buffer, "%E", 12345.6789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_E_negative) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%E", -9876.54321);
  s21_sprintf(buffer, "%E", -9876.54321);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_E_precision) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%.2E", 3.14159);
  s21_sprintf(buffer, "%.2E", 3.14159);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_E_negative_precision) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%.3E", -2.71828);
  s21_sprintf(buffer, "%.3E", -2.71828);
  ck_assert_str_eq(buffer, expected);
}
END_TEST
START_TEST(test_format_d_zero) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%d", 0);
  s21_sprintf(buffer, "%d", 0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_d_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%d", 12345);
  s21_sprintf(buffer, "%d", 12345);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_d_negative) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%d", -6789);
  s21_sprintf(buffer, "%d", -6789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_d_large) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%d", 2147483647);  // Максимальное значение для int
  s21_sprintf(buffer, "%d", 2147483647);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_d_small) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%d", -2147483647);  // Минимальное значение для int
  s21_sprintf(buffer, "%d", -2147483647);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_d_with_leading_zeros) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%05d", 42);  // Ожидается: "00042"
  s21_sprintf(buffer, "%05d", 42);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_i_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%i", 12345);
  s21_sprintf(buffer, "%i", 12345);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_i_negative) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%i", -6789);
  s21_sprintf(buffer, "%i", -6789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_i_large) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%i", 2147483647);  // Максимальное значение для int
  s21_sprintf(buffer, "%i", 2147483647);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_i_small) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%i", -2147483647);  // Минимальное значение для int
  s21_sprintf(buffer, "%i", -2147483647);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_i_with_leading_zeros) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%05i", 42);
  s21_sprintf(buffer, "%05i", 42);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_s_simple) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%s", "Hello, world!");
  s21_sprintf(buffer, "%s", "Hello, world!");
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_s_empty) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%s", "");
  s21_sprintf(buffer, "%s", "");
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_s_with_spaces) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%s", "   ");
  s21_sprintf(buffer, "%s", "   ");
  ck_assert_str_eq(buffer, expected);  // Проверяем пробелы
}
END_TEST

START_TEST(test_format_s_special_characters) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%s", "123!@#");
  s21_sprintf(buffer, "%s", "123!@#");
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_s_newline_character) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%s", "Hello\nWorld");
  s21_sprintf(buffer, "%s", "Hello\nWorld");
  ck_assert_str_eq(buffer, expected);  // Проверяем перенос строки
}
END_TEST

START_TEST(test_format_s_long_string) {
  char buffer[128];
  const char *long_string =
      "This is a very long string that exceeds the usual length.";
  char expected[128];
  sprintf(expected, "%s", long_string);
  s21_sprintf(buffer, "%s", long_string);
  ck_assert_str_eq(buffer, expected);  // Проверяем длинную строку
}
END_TEST

START_TEST(test_format_u_zero) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%u", (unsigned int)0);
  s21_sprintf(buffer, "%u", (unsigned int)0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_u_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%u", (unsigned int)12345);
  s21_sprintf(buffer, "%u", (unsigned int)12345);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_u_large) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%u",
          4294967295U);  // Максимальное значение для unsigned int
  s21_sprintf(buffer, "%u",
              4294967295U);  // Максимальное значение для unsigned int
  s21_sprintf(buffer, "%u", (unsigned int)4294967295U);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_u_small) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%u", (unsigned int)1);
  s21_sprintf(buffer, "%u", (unsigned int)1);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_u_with_leading_zeros) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%05u", 42);  // Ожидается: "00042"
  s21_sprintf(buffer, "%05u", 42);
  sprintf(expected, "%05u", (unsigned int)42);  // Ожидается: "00042"
  s21_sprintf(buffer, "%05u", (unsigned int)42);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_u_negative_value) {
  char buffer[128];
  unsigned int num = -1;  // Преобразуем отрицательное значение в беззнаковое
  char expected[128];
  sprintf(expected, "%u", num);  // Для 32-битного unsigned
  s21_sprintf(buffer, "%u", num);
  sprintf(expected, "%u", (unsigned int)num);  // Для 32-битного unsigned
  s21_sprintf(buffer, "%u", (unsigned int)num);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_x_zero) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%x", 0);
  s21_sprintf(buffer, "%x", 0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_x_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%x", 255);  // Ожидается: "ff"
  s21_sprintf(buffer, "%x", 255);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_x_bi_number) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%x", 4095);  // Ожидается: "fff"
  s21_sprintf(buffer, "%x", 4095);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_x_with_leading_zeros) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%05x", 42);  // Ожидается: "0002a"
  s21_sprintf(buffer, "%05x", 42);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_x_negative_value) {
  char buffer[128];
  unsigned int num = -1;  // Преобразуем отрицательное значение в беззнаковое
  char expected[128];
  sprintf(expected, "%x", num);  // Для 32-битного unsigned
  s21_sprintf(buffer, "%x", num);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_x_large_number) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%x", 123456789);  // Ожидается: "75bcd15"
  s21_sprintf(buffer, "%x", 123456789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_X_zero) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%X", 0);  // Ожидается: "0"
  s21_sprintf(buffer, "%X", 0);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_X_positive) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%X", 255);  // Ожидается: "FF"
  s21_sprintf(buffer, "%X", 255);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_X_big_number) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%X", 4095);  // Ожидается: "FFF"
  s21_sprintf(buffer, "%X", 4095);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_X_with_leading_zeros) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%05X", 42);  // Ожидается: "0002A"
  s21_sprintf(buffer, "%05X", 42);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_X_negative_value) {
  char buffer[128];
  unsigned int num = -1;  // Преобразуем отрицательное значение в беззнаковое
  char expected[128];
  sprintf(expected, "%X", num);  // Для 32-битного unsigned
  s21_sprintf(buffer, "%X", num);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

END_TEST
START_TEST(test_format_X_large_number) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%X", 123456789);
  s21_sprintf(buffer, "%X", 123456789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_format_p_large_pointer) {
  long long large_num = 1234567890123456789LL;
  char buffer[128];
  char expected[128];
  sprintf(expected, "%p", (void *)large_num);
  s21_sprintf(buffer, "%p", (void *)large_num);
  ck_assert_str_eq(buffer, expected);
}
START_TEST(test_format_p_null) {
  char buffer[128];
  char expected[128];
  sprintf(expected, "%p", NULL);
  s21_sprintf(buffer, "%p", S21_NULL);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

//================ОБЩИЕ================//

START_TEST(TEST1_1) {
  const char *str = "123 45.67 Hello";
  int a;
  float b;
  char c[50];
  ck_assert_int_eq(sscanf(str, "%d %f %49s", &a, &b, c),
                   s21_sscanf(str, "%d %f %49s", &a, &b, c));
}
END_TEST

START_TEST(TEST1_2) {
  const char *str = "123456789";
  int a1 = 0, a2 = 0;
  ck_assert_int_eq(sscanf(str, "%15d", &a1), s21_sscanf(str, "%15d", &a2));
}
END_TEST

START_TEST(TEST1_3) {
  const char *str = " 123456789";
  int a1 = 0, a2 = 0;
  ck_assert_int_eq(sscanf(str, "%15d", &a1), s21_sscanf(str, "%15d", &a2));
}
END_TEST

//================ЦЕЛОЧИСЛЕННЫЕ================//

START_TEST(TEST2_1) {
  const char *str = "123 45.67 Hello";
  int a1, a2;
  float b1, b2;
  char c1[50], c2[50];
  sscanf(str, "%d %f %c", &a1, &b1, c1);
  s21_sscanf(str, "%d %f %s", &a2, &b2, c2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST2_2) {
  const char *str = "123.45";
  int a1 = 0, a2 = 0;
  sscanf(str, "%d", &a1);
  s21_sscanf(str, "%d", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST2_3) {
  const char *str = "a";
  int a1 = 0, a2 = 0;
  sscanf(str, "%d", &a1);
  s21_sscanf(str, "%d", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST2_4) {
  const char *str = "32a";
  int a1 = 0, a2 = 0;
  sscanf(str, "%d", &a1);
  s21_sscanf(str, "%d", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST2_5) {
  const char *str = "-32";
  int a1 = 0, a2 = 0;
  sscanf(str, "%d", &a1);
  s21_sscanf(str, "%d", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST2_6) {
  const char *str = " 123.45";
  int a1 = 0, a2 = 0;
  sscanf(str, "%d", &a1);
  s21_sscanf(str, "%d", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST2_7) {
  const char *str = "A";
  int a1 = 0, a2 = 0;
  sscanf(str, "%d", &a1);
  s21_sscanf(str, "%d", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

//================FLOAT================//

START_TEST(TEST3_1) {
  const char *str = "32.32";
  float a1 = 0, a2 = 0;
  sscanf(str, "%f", &a1);
  s21_sscanf(str, "%f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST3_2) {
  const char *str = "32,32";
  float a1 = 0, a2 = 0;
  sscanf(str, "%f", &a1);
  s21_sscanf(str, "%f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST3_3) {
  const char *str = "32.a";
  float a1 = 0, a2 = 0;
  sscanf(str, "%f", &a1);
  s21_sscanf(str, "%f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST3_4) {
  const char *str = "32a";
  float a1 = 0, a2 = 0;
  sscanf(str, "%f", &a1);
  s21_sscanf(str, "%f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST3_5) {
  const char *str = "a";
  float a1 = 0, a2 = 0;
  sscanf(str, "%f", &a1);
  s21_sscanf(str, "%f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST3_6) {
  const char *str = "a32.32a";
  float a1 = 0, a2 = 0;
  sscanf(str, "%f", &a1);
  s21_sscanf(str, "%f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST3_7) {
  const char *str = " a";
  float a1 = 0, a2 = 0;
  sscanf(str, "%f", &a1);
  s21_sscanf(str, "%f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST3_8) {
  const char *str = "AAA";
  float a1 = 0, a2 = 0;
  sscanf(str, "%f", &a1);
  s21_sscanf(str, "%f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

//================СИМВОЛ================//

START_TEST(TEST4_1) {
  const char *str = "a";
  char a1, a2;
  sscanf(str, "%c", &a1);
  s21_sscanf(str, "%c", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST4_2) {
  const char *str = "A";
  char a1, a2;
  sscanf(str, "%c", &a1);
  s21_sscanf(str, "%c", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST4_3) {
  const char *str = "aAa";
  char a1, a2;
  sscanf(str, "%c", &a1);
  s21_sscanf(str, "%c", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST4_4) {
  const char *str = "12";
  char a1, a2;
  sscanf(str, "%c", &a1);
  s21_sscanf(str, "%c", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST4_5) {
  const char *str = "/n";
  char a1 = ' ', a2 = ' ';
  sscanf(str, "%c", &a1);
  s21_sscanf(str, "%c", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST4_6) {
  const char *str = "";
  char a1 = 0, a2 = 0;
  sscanf(str, "%c", &a1);
  s21_sscanf(str, "%c", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST4_7) {
  const char *str = "-";
  char a1, a2;
  sscanf(str, "%c", &a1);
  s21_sscanf(str, "%c", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

//================СТРОКА================//

START_TEST(TEST5_1) {
  const char *str = "abc def";
  char a1[50];
  char a2[50];
  sscanf(str, "%49s", a1);
  s21_sscanf(str, "%49s", a2);
  ck_assert_str_eq(a1, a2);
}
END_TEST

START_TEST(TEST5_2) {
  const char *str = "aBcD AbCd";
  char a1[50];
  char a2[50];
  sscanf(str, "%49s", a1);
  s21_sscanf(str, "%49s", a2);
  ck_assert_str_eq(a1, a2);
}
END_TEST

START_TEST(TEST5_3) {
  const char *str = "abc-def";
  char a1[50];
  char a2[50];
  sscanf(str, "%49s", a1);
  s21_sscanf(str, "%49s", a2);
  ck_assert_str_eq(a1, a2);
}
END_TEST

START_TEST(TEST5_4) {
  const char *str = "abc\n";
  char a1[50];
  char a2[50];
  sscanf(str, "%49s", a1);
  s21_sscanf(str, "%49s", a2);
  ck_assert_str_eq(a1, a2);
}
END_TEST

START_TEST(TEST5_5) {
  const char *str = " abc ";
  char a1[50];
  char a2[50];
  sscanf(str, "%49s", a1);
  s21_sscanf(str, "%49s", a2);
  ck_assert_str_eq(a1, a2);
}
END_TEST

START_TEST(TEST5_6) {
  const char *str = "^!&?!&#";
  char a1[50];
  char a2[50];
  sscanf(str, "%49s", a1);
  s21_sscanf(str, "%49s", a2);
  ck_assert_str_eq(a1, a2);
}
END_TEST

//================БЕЗЗНАКОВОЕ ЧИСЛО================//

START_TEST(TEST6_1) {
  const char *str = "123";
  unsigned int a1;
  unsigned int a2;
  sscanf(str, "%u", &a1);
  s21_sscanf(str, "%u", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST6_2) {
  const char *str = "u123";
  unsigned int a1 = 0;
  unsigned int a2 = 0;
  sscanf(str, "%u", &a1);
  s21_sscanf(str, "%u", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST6_3) {
  const char *str = "12.3";
  unsigned int a1;
  unsigned int a2;
  sscanf(str, "%u", &a1);
  s21_sscanf(str, "%u", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST6_4) {
  const char *str = "12u3";
  unsigned int a1;
  unsigned int a2;
  sscanf(str, "%u", &a1);
  s21_sscanf(str, "%u", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST6_5) {
  const char *str = "X";
  unsigned int a1 = 0;
  unsigned int a2 = 0;
  sscanf(str, "%u", &a1);
  s21_sscanf(str, "%u", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST6_6) {
  const char *str = "";
  unsigned int a1 = 0;
  unsigned int a2 = 0;
  sscanf(str, "%u", &a1);
  s21_sscanf(str, "%u", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST6_7) {
  const char *str = " 123 ";
  unsigned int a1;
  unsigned int a2;
  sscanf(str, "%u", &a1);
  s21_sscanf(str, "%u", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

//================ % ================//

START_TEST(TEST7_1) {
  const char *str = "42%";
  ck_assert_int_eq(sscanf(str, "%%"), s21_sscanf(str, "%%"));
}
END_TEST

START_TEST(TEST7_2) {
  const char *str = "%";
  ck_assert_int_eq(sscanf(str, "%%"), s21_sscanf(str, "%%"));
}
END_TEST

START_TEST(TEST7_3) {
  const char *str = " % ";
  ck_assert_int_eq(sscanf(str, "%%"), s21_sscanf(str, "%%"));
}
END_TEST

START_TEST(TEST7_4) {
  const char *str = "37";  // код % по аски
  ck_assert_int_eq(sscanf(str, "%%"), s21_sscanf(str, "%%"));
}
END_TEST

START_TEST(TEST7_5) {
  const char *str = "%%%%%%";
  ck_assert_int_eq(sscanf(str, "%%"), s21_sscanf(str, "%%"));
}
END_TEST

//================ШИРИНА================//

START_TEST(TEST8_1) {
  const char *str = "123456789";
  int a1 = 0, a2 = 0;

  sscanf(str, "%5d", &a1);
  s21_sscanf(str, "%5d", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_2) {
  const char *str = "123456789";
  int a1 = 0, a2 = 0;

  sscanf(str, "%15d", &a1);
  s21_sscanf(str, "%15d", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_3) {
  const char *str = "123456789";
  int a1 = 0, a2 = 0;

  sscanf(str, "%1d", &a1);
  s21_sscanf(str, "%1d", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_4) {
  const char *str = "1234.56789";
  float a1 = 0, a2 = 0;

  sscanf(str, "%5f", &a1);
  s21_sscanf(str, "%5f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_5) {
  const char *str = "1234.56789";
  float a1 = 0, a2 = 0;

  sscanf(str, "%4f", &a1);
  s21_sscanf(str, "%4f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_6) {
  const char *str = "123456789";
  char a1[10], a2[10];

  sscanf(str, "%3s", a1);
  s21_sscanf(str, "%3s", a2);
  ck_assert_str_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_7) {
  const char *str = "1234 6789";
  char a1[10], a2[10];

  sscanf(str, "%8s", a1);
  s21_sscanf(str, "%8s", a2);
  ck_assert_str_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_8) {
  const char *str = "123456789";
  char a1[10], a2[10];

  sscanf(str, "%1s", a1);
  s21_sscanf(str, "%1s", a2);
  ck_assert_str_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_9) {
  const char *str = "123456789";
  unsigned int a1 = 0, a2 = 0;

  sscanf(str, "%5u", &a1);
  s21_sscanf(str, "%5u", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_10) {
  const char *str = " 123456789";
  unsigned int a1 = 0, a2 = 0;

  sscanf(str, "%5u", &a1);
  s21_sscanf(str, "%5u", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST8_11) {
  const char *str = "1234,56789";
  float a1 = 0, a2 = 0;

  sscanf(str, "%4f", &a1);
  s21_sscanf(str, "%4f", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

//================ДЕСЯТИЧНОЕ================//

START_TEST(TEST9_1) {
  const char *str = "12345";
  int a1 = 0, a2 = 0;
  sscanf(str, "%i", &a1);
  s21_sscanf(str, "%i", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST9_2) {
  const char *str = "-12345";
  int a1 = 0, a2 = 0;
  sscanf(str, "%i", &a1);
  s21_sscanf(str, "%i", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST9_3) {
  const char *str = "123.45";
  int a1 = 0, a2 = 0;
  sscanf(str, "%i", &a1);
  s21_sscanf(str, "%i", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST9_4) {
  const char *str = "a";
  int a1 = 0, a2 = 0;
  sscanf(str, "%i", &a1);
  s21_sscanf(str, "%i", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST9_5) {
  const char *str = " ";
  int a1 = 0, a2 = 0;
  sscanf(str, "%i", &a1);
  s21_sscanf(str, "%i", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST9_6) {
  const char *str = "12A";
  int a1 = 0, a2 = 0;
  sscanf(str, "%i", &a1);
  s21_sscanf(str, "%i", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST9_7) {
  const char *str = " 1 2 345";
  int a1 = 0, a2 = 0;
  sscanf(str, "%i", &a1);
  s21_sscanf(str, "%i", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

//================ g ================//

START_TEST(TEST10_1) {
  const char *str = "12345.678";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%g", &a1);
  s21_sscanf(str, "%g", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST10_2) {
  const char *str = "0.00001234";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%g", &a1);
  s21_sscanf(str, "%g", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST10_3) {
  const char *str = "1234567890.0";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%g", &a1);
  s21_sscanf(str, "%g", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST10_4) {
  const char *str = "12345.678";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%G", &a1);
  s21_sscanf(str, "%G", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST10_5) {
  const char *str = "0.00001234";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%G", &a1);
  s21_sscanf(str, "%G", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST10_6) {
  const char *str = "1234567890.0";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%G", &a1);
  s21_sscanf(str, "%G", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST10_7) {
  const char *str = " 1234567890.0";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%G", &a1);
  s21_sscanf(str, "%G", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST10_8) {
  const char *str = "AaA";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%g", &a1);
  s21_sscanf(str, "%g", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

//================ e ================//

START_TEST(TEST11_1) {
  const char *str = "12345.678";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%e", &a1);
  s21_sscanf(str, "%e", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST11_2) {
  const char *str = "0.00001234";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%e", &a1);
  s21_sscanf(str, "%e", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST11_3) {
  const char *str = "1234567890.0";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%e", &a1);
  s21_sscanf(str, "%e", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST11_4) {
  const char *str = "12345.678";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%E", &a1);
  s21_sscanf(str, "%E", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST11_5) {
  const char *str = "0.00001234";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%E", &a1);
  s21_sscanf(str, "%E", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST11_6) {
  const char *str = "1234567890.0";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%E", &a1);
  s21_sscanf(str, "%E", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST11_7) {
  const char *str = " 1234567890.0";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%E", &a1);
  s21_sscanf(str, "%E", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST11_8) {
  const char *str = "A";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%e", &a1);
  s21_sscanf(str, "%e", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

START_TEST(TEST11_9) {
  const char *str = "a";
  float a1 = 0;
  double a2 = 0;
  sscanf(str, "%e", &a1);
  s21_sscanf(str, "%e", &a2);
  ck_assert_float_eq(a1, a2);
}
END_TEST

//================ octal ================//

START_TEST(TEST12_1) {
  const char *str = "123";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%o", &a1);
  s21_sscanf(str, "%o", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST12_2) {
  const char *str = "0";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%o", &a1);
  s21_sscanf(str, "%o", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST12_3) {
  const char *str = "888";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%o", &a1);
  s21_sscanf(str, "%o", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST12_4) {
  const char *str = " 888";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%o", &a1);
  s21_sscanf(str, "%o", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST12_5) {
  const char *str = "A";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%o", &a1);
  s21_sscanf(str, "%o", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

//================ hex ================//

START_TEST(TEST13_1) {
  const char *str = "1A";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%X", &a1);
  s21_sscanf(str, "%X", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST13_2) {
  const char *str = "1A2B";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%X", &a1);
  s21_sscanf(str, "%X", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST13_3) {
  const char *str = "AAA";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%X", &a1);
  s21_sscanf(str, "%X", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST13_4) {
  const char *str = "1a";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%x", &a1);
  s21_sscanf(str, "%x", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST13_5) {
  const char *str = "1a2b";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%x", &a1);
  s21_sscanf(str, "%x", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST13_6) {
  const char *str = "aaa";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%x", &a1);
  s21_sscanf(str, "%x", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(TEST13_7) {
  const char *str = " aaa";
  unsigned int a1 = 0, a2 = 0;
  sscanf(str, "%x", &a1);
  s21_sscanf(str, "%x", &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

//================ pointer ================//

START_TEST(TEST14_1) {
  const char *str = "0x7ffeefbff618";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  ck_assert_int_eq(sscanf(str, "%p", &ptr1), s21_sscanf(str, "%p", &ptr2));
}
END_TEST

START_TEST(TEST14_2) {
  const char *str = "0x7FFEEFBFF618";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  ck_assert_int_eq(sscanf(str, "%p", &ptr1), s21_sscanf(str, "%p", &ptr2));
}
END_TEST

START_TEST(TEST14_3) {
  const char *str = "0X7FFEEFBFF618";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  ck_assert_int_eq(sscanf(str, "%p", &ptr1), s21_sscanf(str, "%p", &ptr2));
}
END_TEST

START_TEST(TEST14_4) {
  const char *str = "  0X7FFEEFBFF618";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  ck_assert_int_eq(sscanf(str, "%p", &ptr1), s21_sscanf(str, "%p", &ptr2));
}
END_TEST

//================ n ================//

START_TEST(TEST15_1) {
  const char *str = "123 abc";
  int num = 0, chars_read = 0, num2 = 0, chars_read2 = 0;
  char mas[10], mas2[10];
  int point = 0;
  s21_sscanf(str, "%d %9s%n", &num, mas, &chars_read);
  sscanf(str, "%d %9s%n", &num2, mas2, &chars_read2);
  if (num == num2) {
    point++;
  }
  if (chars_read == chars_read2) {
    point++;
  }
  ck_assert_int_eq(point, 2);
}
END_TEST

START_TEST(TEST15_2) {
  const char *str = "123 ABC";
  int num = 0, chars_read = 0, num2 = 0, chars_read2 = 0;
  char mas[10], mas2[10];
  int point = 0;
  s21_sscanf(str, "%d %9s%n", &num, mas, &chars_read);
  sscanf(str, "%d %9s%n", &num2, mas2, &chars_read2);
  if (num == num2) {
    point++;
  }
  if (chars_read == chars_read2) {
    point++;
  }
  ck_assert_int_eq(point, 2);
}
END_TEST

//================ ДОПЫ ================//

START_TEST(TEST16_1) {
  const char *str = "123";
  int result = 0;
  struct list fmt = {0};
  int ret = handle_decimal(fmt, &str, &result);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(result, 123);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char *result = s21_to_lower("HeLLo");
  ck_assert_str_eq(result, "hello");
  free(result);

  result = s21_to_lower("123!@#");
  ck_assert_str_eq(result, "123!@#");
  free(result);

  result = s21_to_lower("");
  ck_assert_str_eq(result, "");
  free(result);

  ck_assert_ptr_eq(s21_to_lower(S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_s21_to_upper) {
  char *result = s21_to_upper("hello");
  ck_assert_str_eq(result, "HELLO");
  free(result);

  result = s21_to_upper("123!@#");
  ck_assert_str_eq(result, "123!@#");
  free(result);

  result = s21_to_upper("");
  ck_assert_str_eq(result, "");
  free(result);

  ck_assert_ptr_eq(s21_to_upper(S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_s21_trim) {
  char *result = s21_trim("  hello  ", " ");
  ck_assert_str_eq(result, "hello");
  free(result);

  result = s21_trim("---hello---", "-");
  ck_assert_str_eq(result, "hello");
  free(result);

  result = s21_trim("hello", " ");
  ck_assert_str_eq(result, "hello");
  free(result);

  result = s21_trim("     ", " ");
  ck_assert_str_eq(result, "");
  free(result);

  ck_assert_ptr_eq(s21_trim(S21_NULL, " "), S21_NULL);
  ck_assert_ptr_eq(s21_trim("test", S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_s21_insert) {
  char *result = s21_insert("hello", " ", 5);
  ck_assert_str_eq(result, "hello ");
  free(result);

  result = s21_insert("hello", "BIG ", 0);
  ck_assert_str_eq(result, "BIG hello");
  free(result);

  result = s21_insert("hello", "WORLD", 3);
  ck_assert_str_eq(result, "helWORLDlo");
  free(result);

  result = s21_insert(S21_NULL, "test", 2);
  ck_assert_ptr_eq(result, S21_NULL);
  if (result) free(result);

  result = s21_insert("test", S21_NULL, 2);
  ck_assert_ptr_eq(result, S21_NULL);
  if (result) free(result);
}
END_TEST

Suite *suite_memcmp(void) {
  Suite *s = suite_create("suite_memcmp");
  TCase *tc = tcase_create("memcmp_tc");

  tcase_add_test(tc, zero);
  tcase_add_test(tc, one_byte);
  tcase_add_test(tc, zero_bytes);
  tcase_add_test(tc, length_diff);
  tcase_add_test(tc, zero_byte);
  tcase_add_test(tc, long_eq_string);
  tcase_add_test(tc, long_string);
  tcase_add_test(tc, two_byte_long_two_num);

  suite_add_tcase(s, tc);
  return s;
}
Suite *suite_memchr(void) {
  Suite *s = suite_create("suite_memchr");
  TCase *tc = tcase_create("memchr_tc");
  tcase_add_test(tc, s21_memchr_test_zero);
  tcase_add_test(tc, s21_memchr_test_two);
  tcase_add_test(tc, s21_memchr_test_full);
  tcase_add_test(tc, s21_memchr_test_not_found);
  tcase_add_test(tc, s21_memchr_test_space);

  suite_add_tcase(s, tc);
  return s;
}
Suite *suite_memcpy(void) {
  Suite *s = suite_create("suite_memcpy");
  TCase *tc = tcase_create("memcpy_tc");
  tcase_add_test(tc, s21_memcpy_test_zero);
  tcase_add_test(tc, s21_memcpy_test_full_copy);
  tcase_add_test(tc, s21_memcpy_test_partial_copy);
  suite_add_tcase(s, tc);
  return s;
}
Suite *suite_memset(void) {
  Suite *s = suite_create("suite_memset");
  TCase *tc = tcase_create("memset_tc");

  tcase_add_test(tc, test_s21_memset_zero);
  tcase_add_test(tc, test_s21_memset_fill);
  tcase_add_test(tc, test_s21_memset_full);
  tcase_add_test(tc, test_s21_memset_partial);
  tcase_add_test(tc, test_s21_memset_tabs);

  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_strchr(void) {
  Suite *s = suite_create("suite_strchr");
  TCase *tc = tcase_create("strchr_tc");
  tcase_add_test(tc, s21_strchr_test_first_occurrence);
  tcase_add_test(tc, s21_strchr_test_not_found);
  tcase_add_test(tc, s21_strchr_test_last_occurrence);
  tcase_add_test(tc, s21_strchr_test_null_character);
  tcase_add_test(tc, s21_strchr_test_empty_string);
  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_strncat(void) {
  Suite *s = suite_create("suite_strncat");
  TCase *tc = tcase_create("strncat_tc");
  tcase_add_test(tc, s21_strncat_test_basic_concatenation);
  tcase_add_test(tc, s21_strncat_test_partial_concatenation);
  tcase_add_test(tc, s21_strncat_test_empty_source);
  tcase_add_test(tc, s21_strncat_test_empty_destination);
  tcase_add_test(tc, s21_strncat_test_no_space_in_dest);
  tcase_add_test(tc, s21_strncat_test_zero_length);
  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_strncmp(void) {
  Suite *s = suite_create("suite_strncmp");
  TCase *tc = tcase_create("strncmp_tc");
  tcase_add_test(tc, s21_strncmp_test_equal_strings);
  tcase_add_test(tc, s21_strncmp_test_partial_equal_strings);
  tcase_add_test(tc, s21_strncmp_test_different_length);
  tcase_add_test(tc, s21_strncmp_test_case_sensitive);
  tcase_add_test(tc, s21_strncmp_test_empty_strings);
  tcase_add_test(tc, s21_strncmp_test_empty_dest_string);
  tcase_add_test(tc, s21_strncmp_test_empty_source_string);
  tcase_add_test(tc, s21_strncmp_test_again);
  suite_add_tcase(s, tc);
  return s;
}
Suite *suite_strncpy(void) {
  Suite *s = suite_create("suite_strncpy");
  TCase *tc = tcase_create("strncpy_tc");
  tcase_add_test(tc, s21_strncpy_test_basic_copy);
  tcase_add_test(tc, s21_strncpy_test_partial_copy);
  tcase_add_test(tc, s21_strncpy_test_empty_source);
  tcase_add_test(tc, s21_strncpy_test_empty_destination);
  tcase_add_test(tc, s21_strncpy_test_more_length_than_source);
  tcase_add_test(tc, s21_strncpy_test_no_null_termination);
  tcase_add_test(tc, s21_strncpy_test_zero_length);
  suite_add_tcase(s, tc);
  return s;
}
Suite *suite_strcspn(void) {
  Suite *s = suite_create("suite_strcspn");
  TCase *tc = tcase_create("strcspn_tc");
  tcase_add_test(tc, s21_strcspn_test_basic);
  tcase_add_test(tc, s21_strcspn_test_no_match);
  tcase_add_test(tc, s21_strcspn_test_with_match_at_start);
  tcase_add_test(tc, s21_strcspn_test_match_after_some_chars);
  tcase_add_test(tc, s21_strcspn_test_empty_first_string);
  tcase_add_test(tc, s21_strcspn_test_empty_second_string);
  tcase_add_test(tc, s21_strcspn_test_identical_strings);
  tcase_add_test(tc, s21_strcspn_test_no_chars_in_first_string);
  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_strlen(void) {
  Suite *s = suite_create("suite_strlen");
  TCase *tc = tcase_create("strlen_tc");

  tcase_add_test(tc, test_empty_string);
  tcase_add_test(tc, test_single_character);
  tcase_add_test(tc, test_multiple_characters);
  tcase_add_test(tc, test_spaces_only);
  tcase_add_test(tc, test_various_characters);
  tcase_add_test(tc, test_newline_character);
  tcase_add_test(tc, test_null_character_in_middle);

  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_strpbrk(void) {
  Suite *s = suite_create("suite_strpbrk");
  TCase *tc = tcase_create("strpbrk_tc");
  tcase_add_test(tc, s21_strpbrk_test_first_string_contains_matching_chars);
  tcase_add_test(tc, s21_strpbrk_test_no_chars_in_first_string);
  tcase_add_test(tc, s21_strpbrk_test_no_matching_chars);
  tcase_add_test(tc, s21_strpbrk_test_last_chars_match);
  tcase_add_test(tc, s21_strpbrk_test_multiple_matches);
  tcase_add_test(tc, s21_strpbrk_test_empty_first_string);
  tcase_add_test(tc, s21_strpbrk_test_empty_second_string);
  tcase_add_test(tc, s21_strpbrk_test_last_character_match);
  tcase_add_test(tc, s21_strpbrk_test_first_characters_match);
  tcase_add_test(tc, s21_strpbrk_test_multiple_match_in_second_string);
  suite_add_tcase(s, tc);
  return s;
}
Suite *suite_strrchr(void) {
  Suite *s = suite_create("suite_strrchr");
  TCase *tc = tcase_create("strrchr_tc");
  tcase_add_test(tc, s21_strrchr_test_char_exists_in_string);
  tcase_add_test(tc, s21_strrchr_test_char_does_not_exist);
  tcase_add_test(tc, s21_strrchr_test_last_character_match);
  tcase_add_test(tc, s21_strrchr_test_first_character_match);
  tcase_add_test(tc, s21_strrchr_test_empty_string);
  tcase_add_test(tc, s21_strrchr_test_null_character);
  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_strstr(void) {
  Suite *s = suite_create("suite_strstr");
  TCase *tc = tcase_create("strstr_tc");
  tcase_add_test(tc, s21_strstr_test_needle_exists_in_haystack);
  tcase_add_test(tc, s21_strstr_test_needle_does_not_exist);
  tcase_add_test(tc, s21_strstr_test_empty_needle);
  tcase_add_test(tc, s21_strstr_test_empty_haystack);
  tcase_add_test(tc, s21_strstr_test_haystack_equals_needle);
  tcase_add_test(tc, s21_strstr_test_partial_match);
  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_strtok(void) {
  Suite *s = suite_create("suite_strtok");
  TCase *tc = tcase_create("strtok_tc");
  tcase_add_test(tc, s21_strtok_test_basic);
  tcase_add_test(tc, s21_strtok_test_no_delimiters);
  tcase_add_test(tc, s21_strtok_test_multiple_delimiters);
  tcase_add_test(tc, s21_strtok_test_end_of_string);
  tcase_add_test(tc, s21_strtok_test_empty_string);
  suite_add_tcase(s, tc);
  return s;
}
Suite *suite_strerror(void) {
  Suite *s = suite_create("suite_strerror");
  TCase *tc = tcase_create("strtok_tc");
  tcase_add_test(tc, test_s21_strerror_no_such_file);
  tcase_add_test(tc, test_s21_strerror_io_error);
  tcase_add_test(tc, test_s21_strerror_unknown_error);
  suite_add_tcase(s, tc);
  return s;
}
Suite *suite_sscanf(void) {
  Suite *s = suite_create("suite_sscanf");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, TEST1_1);
  tcase_add_test(tc, TEST1_2);
  tcase_add_test(tc, TEST1_3);

  tcase_add_test(tc, TEST2_1);
  tcase_add_test(tc, TEST2_2);
  tcase_add_test(tc, TEST2_3);
  tcase_add_test(tc, TEST2_4);
  tcase_add_test(tc, TEST2_5);
  tcase_add_test(tc, TEST2_6);
  tcase_add_test(tc, TEST2_7);

  tcase_add_test(tc, TEST3_1);
  tcase_add_test(tc, TEST3_2);
  tcase_add_test(tc, TEST3_3);
  tcase_add_test(tc, TEST3_4);
  tcase_add_test(tc, TEST3_5);
  tcase_add_test(tc, TEST3_6);
  tcase_add_test(tc, TEST3_7);
  tcase_add_test(tc, TEST3_8);

  tcase_add_test(tc, TEST4_1);
  tcase_add_test(tc, TEST4_2);
  tcase_add_test(tc, TEST4_3);
  tcase_add_test(tc, TEST4_4);
  tcase_add_test(tc, TEST4_5);
  tcase_add_test(tc, TEST4_6);
  tcase_add_test(tc, TEST4_7);

  tcase_add_test(tc, TEST5_1);
  tcase_add_test(tc, TEST5_2);
  tcase_add_test(tc, TEST5_3);
  tcase_add_test(tc, TEST5_4);
  tcase_add_test(tc, TEST5_5);
  tcase_add_test(tc, TEST5_6);

  tcase_add_test(tc, TEST6_1);
  tcase_add_test(tc, TEST6_2);
  tcase_add_test(tc, TEST6_3);
  tcase_add_test(tc, TEST6_4);
  tcase_add_test(tc, TEST6_5);
  tcase_add_test(tc, TEST6_6);
  tcase_add_test(tc, TEST6_7);

  tcase_add_test(tc, TEST7_1);
  tcase_add_test(tc, TEST7_2);
  tcase_add_test(tc, TEST7_3);
  tcase_add_test(tc, TEST7_4);
  tcase_add_test(tc, TEST7_5);

  tcase_add_test(tc, TEST8_1);
  tcase_add_test(tc, TEST8_2);
  tcase_add_test(tc, TEST8_3);
  tcase_add_test(tc, TEST8_4);
  tcase_add_test(tc, TEST8_5);
  tcase_add_test(tc, TEST8_6);
  tcase_add_test(tc, TEST8_7);
  tcase_add_test(tc, TEST8_8);
  tcase_add_test(tc, TEST8_9);
  tcase_add_test(tc, TEST8_10);
  tcase_add_test(tc, TEST8_11);

  tcase_add_test(tc, TEST9_1);
  tcase_add_test(tc, TEST9_2);
  tcase_add_test(tc, TEST9_3);
  tcase_add_test(tc, TEST9_4);
  tcase_add_test(tc, TEST9_5);
  tcase_add_test(tc, TEST9_6);
  tcase_add_test(tc, TEST9_7);

  tcase_add_test(tc, TEST10_1);
  tcase_add_test(tc, TEST10_2);
  tcase_add_test(tc, TEST10_3);
  tcase_add_test(tc, TEST10_4);
  tcase_add_test(tc, TEST10_5);
  tcase_add_test(tc, TEST10_6);
  tcase_add_test(tc, TEST10_7);
  tcase_add_test(tc, TEST10_8);

  tcase_add_test(tc, TEST11_1);
  tcase_add_test(tc, TEST11_2);
  tcase_add_test(tc, TEST11_3);
  tcase_add_test(tc, TEST11_4);
  tcase_add_test(tc, TEST11_5);
  tcase_add_test(tc, TEST11_6);
  tcase_add_test(tc, TEST11_7);
  tcase_add_test(tc, TEST11_8);
  tcase_add_test(tc, TEST11_9);

  tcase_add_test(tc, TEST12_1);
  tcase_add_test(tc, TEST12_2);
  tcase_add_test(tc, TEST12_3);
  tcase_add_test(tc, TEST12_4);
  tcase_add_test(tc, TEST12_5);

  tcase_add_test(tc, TEST13_1);
  tcase_add_test(tc, TEST13_2);
  tcase_add_test(tc, TEST13_3);
  tcase_add_test(tc, TEST13_4);
  tcase_add_test(tc, TEST13_5);
  tcase_add_test(tc, TEST13_6);
  tcase_add_test(tc, TEST13_7);

  tcase_add_test(tc, TEST14_1);
  tcase_add_test(tc, TEST14_2);
  tcase_add_test(tc, TEST14_3);
  tcase_add_test(tc, TEST14_4);

  tcase_add_test(tc, TEST15_1);
  tcase_add_test(tc, TEST15_2);

  tcase_add_test(tc, TEST16_1);
  suite_add_tcase(s, tc);
  return s;
}
Suite *suite_sprintf(void) {
  // g G c f o e E d i s u x X

  Suite *s = suite_create("suite_sprintf");
  TCase *tc = tcase_create("sprintf_tc");
  tcase_add_test(tc, test_format_g_positive);
  tcase_add_test(tc, test_format_g_small);
  tcase_add_test(tc, test_format_g_negative);
  tcase_add_test(tc, test_format_g_large);
  tcase_add_test(tc, test_format_g_scientific);

  tcase_add_test(tc, test_format_G_zero);
  tcase_add_test(tc, test_format_G_positive);
  tcase_add_test(tc, test_format_G_small);
  tcase_add_test(tc, test_format_G_negative);
  tcase_add_test(tc, test_format_c_single_character);
  tcase_add_test(tc, test_format_c_lowercase_character);
  tcase_add_test(tc, test_format_c_special_character);
  tcase_add_test(tc, test_format_c_numeric_character);
  tcase_add_test(tc, test_format_c_space_character);

  tcase_add_test(tc, test_format_f_positive);
  tcase_add_test(tc, test_format_f_negative);
  tcase_add_test(tc, test_format_f_zero);
  tcase_add_test(tc, test_format_f_small);
  tcase_add_test(tc, test_format_f_large);
  tcase_add_test(tc, test_format_f_precision);
  tcase_add_test(tc, test_format_f_negative_precision);

  tcase_add_test(tc, test_format_o_zero);
  tcase_add_test(tc, test_format_o_positive);
  tcase_add_test(tc, test_format_o_large_number);
  tcase_add_test(tc, test_format_o_negative_number);
  tcase_add_test(tc, test_format_o_large_value);

  tcase_add_test(tc, test_format_e_zero);
  tcase_add_test(tc, test_format_e_positive);
  tcase_add_test(tc, test_format_e_negative);
  tcase_add_test(tc, test_format_e_precision);
  tcase_add_test(tc, test_format_e_negative_precision);

  tcase_add_test(tc, test_format_E_zero);
  tcase_add_test(tc, test_format_E_positive);
  tcase_add_test(tc, test_format_E_negative);
  tcase_add_test(tc, test_format_E_precision);
  tcase_add_test(tc, test_format_E_negative_precision);

  tcase_add_test(tc, test_format_d_zero);
  tcase_add_test(tc, test_format_d_positive);
  tcase_add_test(tc, test_format_d_negative);
  tcase_add_test(tc, test_format_d_large);
  tcase_add_test(tc, test_format_d_small);
  tcase_add_test(tc, test_format_d_with_leading_zeros);

  tcase_add_test(tc, test_format_i_positive);
  tcase_add_test(tc, test_format_i_negative);
  tcase_add_test(tc, test_format_i_large);
  tcase_add_test(tc, test_format_i_small);
  tcase_add_test(tc, test_format_i_with_leading_zeros);

  tcase_add_test(tc, test_format_s_simple);
  tcase_add_test(tc, test_format_s_empty);
  tcase_add_test(tc, test_format_s_with_spaces);
  tcase_add_test(tc, test_format_s_special_characters);
  tcase_add_test(tc, test_format_s_newline_character);
  tcase_add_test(tc, test_format_s_long_string);

  tcase_add_test(tc, test_format_u_zero);
  tcase_add_test(tc, test_format_u_positive);
  tcase_add_test(tc, test_format_u_large);
  tcase_add_test(tc, test_format_u_small);
  tcase_add_test(tc, test_format_u_with_leading_zeros);
  tcase_add_test(tc, test_format_u_negative_value);

  tcase_add_test(tc, test_format_x_zero);
  tcase_add_test(tc, test_format_x_positive);
  tcase_add_test(tc, test_format_x_large_number);
  tcase_add_test(tc, test_format_x_with_leading_zeros);
  tcase_add_test(tc, test_format_x_negative_value);
  tcase_add_test(tc, test_format_x_large_number);
  tcase_add_test(tc, test_format_x_bi_number);

  tcase_add_test(tc, test_format_X_zero);
  tcase_add_test(tc, test_format_X_positive);
  tcase_add_test(tc, test_format_X_with_leading_zeros);
  tcase_add_test(tc, test_format_X_negative_value);
  tcase_add_test(tc, test_format_X_large_number);
  tcase_add_test(tc, test_format_X_big_number);

  tcase_add_test(tc, test_format_p_null);
  tcase_add_test(tc, test_format_p_large_pointer);

  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_bonus(void) {
  Suite *s = suite_create("bonus");
  TCase *tc_core = tcase_create("bonus");

  tcase_add_test(tc_core, test_s21_to_lower);
  tcase_add_test(tc_core, test_s21_to_upper);
  tcase_add_test(tc_core, test_s21_trim);
  tcase_add_test(tc_core, test_s21_insert);

  suite_add_tcase(s, tc_core);
  return s;
}

void run_tests(void) {
  Suite *list_cases[] = {suite_memcmp(),
                         suite_memchr(),
                         suite_memcpy(),
                         suite_memset(),
                         suite_strchr(),
                         suite_strncat(),
                         suite_strncmp(),
                         suite_strncpy(),
                         suite_strcspn(),
                         suite_strlen(),
                         suite_strpbrk(),
                         suite_strrchr(),
                         suite_strstr(),
                         suite_strtok(),
                         suite_strerror(),
                         suite_sprintf(),
                         suite_sscanf(),
                         suite_bonus(),
                         NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}
void run_testcase(Suite *testcase) {
  setlocale(LC_ALL, "");
  static int counter_testcase = 1;

  if (counter_testcase > 1) putchar('\n');
  printf("%s%d%s", "CURRENT TEST: ", counter_testcase, "\n");
  counter_testcase++;

  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}
int main(void) {
  run_tests();
  return 0;
}