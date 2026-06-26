#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_memchr) {
  char str[20];
  int c;
  size_t n;

  strcpy(str, "abcde");
  c = 'a';
  n = 3;
  ck_assert_ptr_eq(memchr(str, c, n), s21_memchr(str, c, n));

  strcpy(str, "hello world");
  c = 'w';
  n = 11;
  ck_assert_ptr_eq(memchr(str, c, n), s21_memchr(str, c, n));

  strcpy(str, "abcde");
  c = 'z';
  n = 5;
  ck_assert_ptr_eq(memchr(str, c, n), s21_memchr(str, c, n));
  ck_assert_ptr_null(s21_memchr(str, c, n));

  char* null_str = NULL;
  c = 'a';
  n = 3;
  ck_assert_ptr_null(s21_memchr(null_str, c, n));
}
END_TEST

START_TEST(test_s21_memcmp) {
  char str1[20];
  char str2[20];
  size_t n;

  strcpy(str1, "abcde");
  strcpy(str2, "abcde");
  n = 5;
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));

  strcpy(str1, "abcde");
  strcpy(str2, "abzde");
  n = 5;
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));

  strcpy(str1, "abcde");
  strcpy(str2, "abcde");
  n = 0;
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));

  char* null_str = NULL;
  ck_assert_int_eq(0, s21_memcmp(null_str, str2, 3));
}
END_TEST

START_TEST(test_s21_memcpy) {
  char src[20] = "hello world";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = 11;

  memcpy(dest1, src, n);
  s21_memcpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
  ck_assert_ptr_eq(s21_memcpy(dest2, src, n), dest2);

  char* null_dest = NULL;
  ck_assert_ptr_null(s21_memcpy(null_dest, src, 3));
}
END_TEST

START_TEST(test_s21_memset) {
  char str1[20];
  char str2[20];
  int c;
  size_t n;

  strcpy(str1, "hello world");
  strcpy(str2, "hello world");
  c = 'a';
  n = 5;

  memset(str1, c, n);
  s21_memset(str2, c, n);

  ck_assert_str_eq(str1, str2);
  ck_assert_ptr_eq(s21_memset(str2, c, n), str2);

  strcpy(str1, "test");
  strcpy(str2, "test");
  c = 'b';
  n = 0;

  memset(str1, c, n);
  s21_memset(str2, c, n);

  ck_assert_str_eq(str1, str2);

  char* null_str = NULL;
  ck_assert_ptr_null(s21_memset(null_str, c, 3));
}
END_TEST

START_TEST(test_s21_strncat) {
  char dest1[40];
  char dest2[40];
  char src[20];
  size_t n;

  strcpy(dest1, "hello ");
  strcpy(dest2, "hello ");
  strcpy(src, "world");
  n = 5;

  strncat(dest1, src, n);
  s21_strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
  ck_assert_ptr_eq(s21_strncat(dest2, src, n), dest2);

  strcpy(dest1, "test");
  strcpy(dest2, "test");
  strcpy(src, "ing");
  n = 10;

  strncat(dest1, src, n);
  s21_strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);

  strcpy(dest1, "abc");
  strcpy(dest2, "abc");
  strcpy(src, "def");
  n = 0;

  strncat(dest1, src, n);
  s21_strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);

  char* null_dest = NULL;
  ck_assert_ptr_null(s21_strncat(null_dest, src, 3));
}
END_TEST

START_TEST(test_s21_strchr) {
  char str[20];
  int c;

  strcpy(str, "hello world");
  c = 'o';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));

  strcpy(str, "hello world");
  c = 'z';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
  ck_assert_ptr_null(s21_strchr(str, c));

  strcpy(str, "hello");
  c = '\0';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));

  char* null_str = NULL;
  ck_assert_ptr_null(s21_strchr(null_str, c));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char str1[20];
  char str2[20];
  size_t n;
  int res_orig, res_s21;

  strcpy(str1, "abcde");
  strcpy(str2, "abcde");
  n = 5;
  res_orig = strncmp(str1, str2, n);
  res_s21 = s21_strncmp(str1, str2, n);
  ck_assert_int_eq((res_orig > 0) - (res_orig < 0),
                   (res_s21 > 0) - (res_s21 < 0));

  strcpy(str1, "abcde");
  strcpy(str2, "abzde");
  n = 5;
  res_orig = strncmp(str1, str2, n);
  res_s21 = s21_strncmp(str1, str2, n);
  ck_assert_int_eq((res_orig > 0) - (res_orig < 0),
                   (res_s21 > 0) - (res_s21 < 0));

  strcpy(str1, "abc");
  strcpy(str2, "abcd");
  n = 4;
  res_orig = strncmp(str1, str2, n);
  res_s21 = s21_strncmp(str1, str2, n);
  ck_assert_int_eq((res_orig > 0) - (res_orig < 0),
                   (res_s21 > 0) - (res_s21 < 0));

  strcpy(str1, "abcde");
  strcpy(str2, "abcde");
  n = 0;
  res_orig = strncmp(str1, str2, n);
  res_s21 = s21_strncmp(str1, str2, n);
  ck_assert_int_eq((res_orig > 0) - (res_orig < 0),
                   (res_s21 > 0) - (res_s21 < 0));

  char* null_str = NULL;
  ck_assert_int_eq(0, s21_strncmp(null_str, str2, 3));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char dest1[20] = {0};
  char dest2[20] = {0};
  char src[20] = "hello";
  size_t n = 10;

  strncpy(dest1, src, n);
  s21_strncpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
  ck_assert_ptr_eq(s21_strncpy(dest2, src, n), dest2);

  memset(dest1, 0, 20);
  memset(dest2, 0, 20);
  strcpy(src, "test");
  n = 4;

  strncpy(dest1, src, n);
  s21_strncpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);

  char* null_dest = NULL;
  ck_assert_ptr_null(s21_strncpy(null_dest, src, 3));
}
END_TEST

START_TEST(test_s21_strcspn) {
  char str1[20];
  char str2[20];

  strcpy(str1, "hello world");
  strcpy(str2, "ow");
  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));

  strcpy(str1, "hello");
  strcpy(str2, "xyz");
  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));

  strcpy(str1, "");
  strcpy(str2, "a");
  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));

  strcpy(str1, "abc");
  strcpy(str2, "");
  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));

  char* null_str = NULL;
  ck_assert_int_eq(0, s21_strcspn(null_str, str2));
  ck_assert_int_eq(0, s21_strcspn(str1, null_str));
}
END_TEST

START_TEST(test_s21_strlen) {
  char str[20];

  strcpy(str, "hello world");
  ck_assert_int_eq(strlen(str), s21_strlen(str));

  strcpy(str, "");
  ck_assert_int_eq(strlen(str), s21_strlen(str));

  strcpy(str, "a b c");
  ck_assert_int_eq(strlen(str), s21_strlen(str));

  char* null_str = NULL;
  ck_assert_int_eq(0, s21_strlen(null_str));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char str1[20];
  char str2[20];

  strcpy(str1, "hello world");
  strcpy(str2, "ow");
  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));

  strcpy(str1, "hello");
  strcpy(str2, "xyz");
  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));
  ck_assert_ptr_null(s21_strpbrk(str1, str2));

  strcpy(str1, "");
  strcpy(str2, "a");
  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));

  strcpy(str1, "abc");
  strcpy(str2, "");
  ck_assert_ptr_eq(strpbrk(str1, str2), s21_strpbrk(str1, str2));

  char* null_str = NULL;
  ck_assert_ptr_null(s21_strpbrk(null_str, str2));
  ck_assert_ptr_null(s21_strpbrk(str1, null_str));
}
END_TEST

START_TEST(test_s21_strrchr) {
  char str[20];
  int c;

  strcpy(str, "hello world");
  c = 'o';
  ck_assert_ptr_eq(strrchr(str, c), s21_strrchr(str, c));

  strcpy(str, "abcabc");
  c = 'a';
  ck_assert_ptr_eq(strrchr(str, c), s21_strrchr(str, c));

  strcpy(str, "hello");
  c = 'z';
  ck_assert_ptr_eq(strrchr(str, c), s21_strrchr(str, c));
  ck_assert_ptr_null(s21_strrchr(str, c));

  strcpy(str, "hello");
  c = '\0';
  ck_assert_ptr_eq(strrchr(str, c), s21_strrchr(str, c));

  char* null_str = NULL;
  ck_assert_ptr_null(s21_strrchr(null_str, c));
}
END_TEST

START_TEST(test_s21_strstr) {
  char str1[20];
  char str2[20];

  strcpy(str1, "hello world");
  strcpy(str2, "world");
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));

  strcpy(str1, "hello world");
  strcpy(str2, "xyz");
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
  ck_assert_ptr_null(s21_strstr(str1, str2));

  strcpy(str1, "hello");
  strcpy(str2, "");
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));

  strcpy(str1, "");
  strcpy(str2, "a");
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));

  char* null_str = NULL;
  ck_assert_ptr_null(s21_strstr(null_str, str2));
  ck_assert_ptr_null(s21_strstr(str1, null_str));
}
END_TEST

START_TEST(test_s21_strtok) {
  char* null_str = NULL;
  char* delim = "a";
  ck_assert_ptr_null(s21_strtok(null_str, delim));

  char str1[] = "Hello world";
  char* delim1 = " ";
  char* token1 = s21_strtok(str1, delim1);
  ck_assert_str_eq(token1, "Hello");
  char* token2 = s21_strtok(NULL, delim1);
  ck_assert_str_eq(token2, "world");
  char* token3 = s21_strtok(NULL, delim1);
  ck_assert_ptr_null(token3);

  char str2[] = "a,,b,c";
  char* delim2 = ",";
  ck_assert_str_eq(s21_strtok(str2, delim2), "a");
  ck_assert_str_eq(s21_strtok(NULL, delim2), "b");
  ck_assert_str_eq(s21_strtok(NULL, delim2), "c");
  ck_assert_ptr_null(s21_strtok(NULL, delim2));

  char str3[] = "one";
  char* delim3 = ",";
  ck_assert_str_eq(s21_strtok(str3, delim3), "one");
  ck_assert_ptr_null(s21_strtok(NULL, delim3));

  char str4[] = ",,,a,,,";
  char* delim4 = ",";
  ck_assert_str_eq(s21_strtok(str4, delim4), "a");
  ck_assert_ptr_null(s21_strtok(NULL, delim4));
}
END_TEST

START_TEST(test_s21_to_upper) {
  char* str = NULL;
  ck_assert_ptr_null(s21_to_upper(str));

  char str1[] = "hello world";
  char* upper1 = s21_to_upper(str1);
  ck_assert_str_eq(upper1, "HELLO WORLD");
  free(upper1);

  char str2[] = "Test123";
  char* upper2 = s21_to_upper(str2);
  ck_assert_str_eq(upper2, "TEST123");
  free(upper2);

  char str3[] = "UPPER CASE";
  char* upper3 = s21_to_upper(str3);
  ck_assert_str_eq(upper3, "UPPER CASE");
  free(upper3);

  char str4[] = "";
  char* upper4 = s21_to_upper(str4);
  ck_assert_str_eq(upper4, "");
  free(upper4);

  char str5[] = "!@# 123";
  char* upper5 = s21_to_upper(str5);
  ck_assert_str_eq(upper5, "!@# 123");
  free(upper5);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char* r1 = s21_to_lower("HELLO");
  ck_assert_str_eq(r1, "hello");
  free(r1);

  char* r2 = s21_to_lower("hello");
  ck_assert_str_eq(r2, "hello");
  free(r2);

  char* r3 = s21_to_lower("");
  ck_assert_str_eq(r3, "");
  free(r3);

  char* r4 = s21_to_lower("123ABC!@#");
  ck_assert_str_eq(r4, "123abc!@#");
  free(r4);

  char* r5 = s21_to_lower(NULL);
  ck_assert_ptr_null(r5);
}
END_TEST

START_TEST(test_s21_insert) {
  char* r1 = s21_insert("hello", " world", 5);
  ck_assert_str_eq(r1, "hello world");
  free(r1);

  char* r2 = s21_insert("hello", " world", 0);
  ck_assert_str_eq(r2, " worldhello");
  free(r2);

  char* r3 = s21_insert("hello", " world", 3);
  ck_assert_str_eq(r3, "hel worldlo");
  free(r3);

  char* r4 = s21_insert("", "test", 0);
  ck_assert_str_eq(r4, "test");
  free(r4);

  char* r5 = s21_insert("test", "", 2);
  ck_assert_str_eq(r5, "test");
  free(r5);

  char* r6 = s21_insert("test", "abc", 100);
  ck_assert_ptr_null(r6);

  char* r7 = s21_insert(NULL, "abc", 0);
  ck_assert_ptr_null(r7);

  char* r8 = s21_insert("abc", NULL, 0);
  ck_assert_ptr_null(r8);
}
END_TEST

START_TEST(test_s21_trim) {
  char* r1 = s21_trim("  hello  ", " ");
  ck_assert_str_eq(r1, "hello");
  free(r1);

  char* r2 = s21_trim("***hello***", "*");
  ck_assert_str_eq(r2, "hello");
  free(r2);

  char* r3 = s21_trim("abc hello abc", "abc");
  ck_assert_str_eq(r3, " hello ");
  free(r3);

  char* r4 = s21_trim("hello", "xyz");
  ck_assert_str_eq(r4, "hello");
  free(r4);

  char* r5 = s21_trim("", " ");
  ck_assert_str_eq(r5, "");
  free(r5);

  char* r6 = s21_trim("   ", " ");
  ck_assert_str_eq(r6, "");
  free(r6);

  char* r7 = s21_trim("abba", "ab");
  ck_assert_str_eq(r7, "");
  free(r7);

  char* r8 = s21_trim(NULL, "abc");
  ck_assert_ptr_null(r8);
}
END_TEST

START_TEST(test_sprintf_char_string) {
  char buf_s21[256] = {0};
  char buf_orig[256] = {0};
  char* fmt = "Char: %c, String: %s, Percent: %%";

  int res_s21 = s21_sprintf(buf_s21, fmt, 'M', "minsk 125");
  int res_orig = sprintf(buf_orig, fmt, 'M', "minsk 125");

  ck_assert_int_eq(res_s21, res_orig);
  ck_assert_str_eq(buf_s21, buf_orig);
}
END_TEST

START_TEST(test_sprintf_integers) {
  char buf_s21[256] = {0};
  char buf_orig[256] = {0};
  char* fmt = "Int: %d, Negative: %d, Zero: %d, Unsigned: %u";

  int res_s21 = s21_sprintf(buf_s21, fmt, 2147483647, -12345, 0, 4294967295U);
  int res_orig = sprintf(buf_orig, fmt, 2147483647, -12345, 0, 4294967295U);

  ck_assert_int_eq(res_s21, res_orig);
  ck_assert_str_eq(buf_s21, buf_orig);
}
END_TEST

START_TEST(test_sprintf_flags) {
  char buf_s21[256] = {0};
  char buf_orig[256] = {0};

  int res_s21 =
      s21_sprintf(buf_s21, "Plus: %+d, Space: % d, Left: %-10d!", 5, 5, 42);
  int res_orig =
      sprintf(buf_orig, "Plus: %+d, Space: % d, Left: %-10d!", 5, 5, 42);

  ck_assert_int_eq(res_s21, res_orig);
  ck_assert_str_eq(buf_s21, buf_orig);
}
END_TEST

START_TEST(test_sprintf_width_precision) {
  char buf_s21[256] = {0};
  char buf_orig[256] = {0};

  int res_s21 =
      s21_sprintf(buf_s21, "Num: %10.5d, Str: %.5s", 125, "minsk 125");
  int res_orig = sprintf(buf_orig, "Num: %10.5d, Str: %.5s", 125, "minsk 125");

  ck_assert_int_eq(res_s21, res_orig);
  ck_assert_str_eq(buf_s21, buf_orig);
}
END_TEST

START_TEST(test_sprintf_lengths) {
  char buf_s21[256] = {0};
  char buf_orig[256] = {0};
  short sh = 32767;
  long lg = 9223372036854775807L;
  unsigned long ulg = 18446744073709551615UL;

  int res_s21 =
      s21_sprintf(buf_s21, "Short: %hd, Long: %ld, ULong: %lu", sh, lg, ulg);
  int res_orig =
      sprintf(buf_orig, "Short: %hd, Long: %ld, ULong: %lu", sh, lg, ulg);

  ck_assert_int_eq(res_s21, res_orig);
  ck_assert_str_eq(buf_s21, buf_orig);
}
END_TEST

START_TEST(test_sprintf_floats) {
  char buf_s21[256] = {0};
  char buf_orig[256] = {0};
  double f1 = 3.1415926535;
  double f2 = -0.12345;

  int res_s21 =
      s21_sprintf(buf_s21, "Def: %f, Prec: %.8f, Zero: %.0f", f1, f2, f1);
  int res_orig =
      sprintf(buf_orig, "Def: %f, Prec: %.8f, Zero: %.0f", f1, f2, f1);

  ck_assert_int_eq(res_s21, res_orig);
  ck_assert_str_eq(buf_s21, buf_orig);
}
END_TEST

Suite* s21_string_suite(void) {
  Suite* s = suite_create("s21_string");
  TCase* tc_core = tcase_create("StringTests");

  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strncat);

  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strlen);

  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_strtok);
  tcase_add_test(tc_core, test_s21_to_upper);

  tcase_add_test(tc_core, test_s21_to_lower);
  tcase_add_test(tc_core, test_s21_insert);
  tcase_add_test(tc_core, test_s21_trim);

  tcase_add_test(tc_core, test_sprintf_char_string);
  tcase_add_test(tc_core, test_sprintf_integers);
  tcase_add_test(tc_core, test_sprintf_flags);
  tcase_add_test(tc_core, test_sprintf_width_precision);
  tcase_add_test(tc_core, test_sprintf_lengths);
  tcase_add_test(tc_core, test_sprintf_floats);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite* s = s21_string_suite();
  SRunner* sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}