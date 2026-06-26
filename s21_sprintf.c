#include <stdarg.h>

#include "s21_string.h"

typedef struct {
  int plus;
  int minus;
  int space;
  int width;
  int precision;
  int is_precision;
  char length;
} s21_flags;

const char* s21_parse_flags(const char* format, s21_flags* flags) {
  int loop = 1;
  while (*format && loop) {
    if (*format == '+') {
      flags->plus = 1;
    } else if (*format == '-') {
      flags->minus = 1;
    } else if (*format == ' ') {
      flags->space = 1;
    } else {
      loop = 0;
    }
    if (loop) {
      format++;
    }
  }
  return format;
}

const char* s21_parse_width_precision(const char* format, int* val) {
  *val = 0;
  while (*format >= '0' && *format <= '9') {
    *val = *val * 10 + (*format - '0');
    format++;
  }
  return format;
}

void s21_apply_padding(char* str, s21_flags flags, int* len) {
  int pad_len = flags.width - *len;
  if (pad_len > 0) {
    int i = 0;
    if (flags.minus) {
      while (i < pad_len) {
        str[*len + i] = ' ';
        i++;
      }
      str[*len + pad_len] = '\0';
      *len += pad_len;
    } else {
      int j = *len;
      while (j >= 0) {
        str[j + pad_len] = str[j];
        j--;
      }
      while (i < pad_len) {
        str[i] = ' ';
        i++;
      }
      *len += pad_len;
    }
  }
}

void s21_format_char(char* str, s21_flags flags, int* len, char c) {
  str[*len] = c;
  str[*len + 1] = '\0';
  int char_len = 1;
  s21_apply_padding(str + *len, flags, &char_len);
  *len += char_len;
}

void s21_format_string(char* str, s21_flags flags, int* len, const char* s) {
  int s_len = 0;
  const char* ptr = s ? s : "(null)";
  while (ptr[s_len] != '\0') {
    s_len++;
  }
  if (flags.is_precision && flags.precision < s_len) {
    s_len = flags.precision;
  }
  int i = 0;
  while (i < s_len) {
    str[*len + i] = ptr[i];
    i++;
  }
  str[*len + s_len] = '\0';
  s21_apply_padding(str + *len, flags, &s_len);
  *len += s_len;
}

void s21_num_to_str(unsigned long long num, char* buf, int* len) {
  int i = 0;
  if (num == 0) {
    buf[i++] = '0';
  }
  while (num > 0) {
    buf[i++] = (num % 10) + '0';
    num /= 10;
  }
  buf[i] = '\0';
  *len = i;
  int j = 0;
  while (j < i / 2) {
    char tmp = buf[j];
    buf[j] = buf[i - 1 - j];
    buf[i - 1 - j] = tmp;
    j++;
  }
}

void s21_apply_int_precision(char* buf, int* buf_len, s21_flags flags) {
  if (flags.is_precision && flags.precision > *buf_len) {
    int prec_pad = flags.precision - *buf_len;
    int i = *buf_len;
    while (i >= 0) {
      buf[i + prec_pad] = buf[i];
      i--;
    }
    i = 0;
    while (i < prec_pad) {
      buf[i] = '0';
      i++;
    }
    *buf_len += prec_pad;
  }
}

void s21_apply_int_sign(char* buf, int* buf_len, s21_flags flags, long long num,
                        int is_unsigned) {
  char sign = '\0';
  if (!is_unsigned) {
    if (num < 0)
      sign = '-';
    else if (flags.plus)
      sign = '+';
    else if (flags.space)
      sign = ' ';
  }
  if (sign != '\0') {
    int i = *buf_len;
    while (i >= 0) {
      buf[i + 1] = buf[i];
      i--;
    }
    buf[0] = sign;
    *buf_len += 1;
  }
}

void s21_format_integer(char* str, s21_flags flags, int* len, long long num,
                        int is_unsigned) {
  char buf[128] = {0};
  int buf_len = 0;
  unsigned long long u_num = 0;
  if (num < 0 && !is_unsigned) {
    u_num = (unsigned long long)(-(num + 1)) + 1;
  } else {
    u_num = (unsigned long long)num;
  }
  s21_num_to_str(u_num, buf, &buf_len);
  if (num == 0 && flags.is_precision && flags.precision == 0) {
    buf_len = 0;
    buf[0] = '\0';
  }
  s21_apply_int_precision(buf, &buf_len, flags);
  s21_apply_int_sign(buf, &buf_len, flags, num, is_unsigned);
  int i = 0;
  while (i < buf_len) {
    str[*len + i] = buf[i];
    i++;
  }
  str[*len + buf_len] = '\0';
  s21_apply_padding(str + *len, flags, &buf_len);
  *len += buf_len;
}

void s21_format_float(char* str, s21_flags flags, int* len, double num) {
  char buf[256] = {0};
  int buf_len = 0;
  int prec = flags.is_precision ? flags.precision : 6;
  double n = num < 0 ? -num : num;
  double round_val = 0.5;
  int i = 0;
  while (i < prec) {
    round_val /= 10.0;
    i++;
  }
  n += round_val;
  unsigned long long ipart = (unsigned long long)n;
  s21_num_to_str(ipart, buf, &buf_len);
  if (prec > 0) {
    buf[buf_len++] = '.';
    double fpart = n - (double)ipart;
    i = 0;
    while (i < prec) {
      fpart *= 10.0;
      int digit = (int)fpart;
      buf[buf_len++] = digit + '0';
      fpart -= digit;
      i++;
    }
  }
  buf[buf_len] = '\0';
  s21_apply_int_sign(buf, &buf_len, flags, num < 0 ? -1 : 1, 0);
  i = 0;
  while (i < buf_len) {
    str[*len + i] = buf[i];
    i++;
  }
  str[*len + buf_len] = '\0';
  s21_apply_padding(str + *len, flags, &buf_len);
  *len += buf_len;
}

void s21_process_argument(char* str, const char spec, s21_flags flags, int* len,
                          va_list args) {
  if (spec == 'c') {
    s21_format_char(str, flags, len, (char)va_arg(args, int));
  } else if (spec == 's') {
    s21_format_string(str, flags, len, va_arg(args, char*));
  } else if (spec == '%') {
    s21_format_char(str, flags, len, '%');
  } else if (spec == 'd') {
    long long num = 0;
    if (flags.length == 'l') {
      num = va_arg(args, long);
    } else if (flags.length == 'h') {
      num = (short)va_arg(args, int);
    } else {
      num = va_arg(args, int);
    }
    s21_format_integer(str, flags, len, num, 0);
  } else if (spec == 'u') {
    long long num = 0;
    if (flags.length == 'l') {
      num = va_arg(args, unsigned long);
    } else if (flags.length == 'h') {
      num = (unsigned short)va_arg(args, unsigned int);
    } else {
      num = va_arg(args, unsigned int);
    }
    s21_format_integer(str, flags, len, num, 1);
  } else if (spec == 'f') {
    s21_format_float(str, flags, len, va_arg(args, double));
  }
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);
  int len = 0;
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      s21_flags flags = {0};
      format = s21_parse_flags(format, &flags);
      format = s21_parse_width_precision(format, &flags.width);
      if (*format == '.') {
        format++;
        flags.is_precision = 1;
        format = s21_parse_width_precision(format, &flags.precision);
      }
      if (*format == 'h' || *format == 'l') {
        flags.length = *format;
        format++;
      }
      s21_process_argument(str, *format, flags, &len, args);
    } else {
      str[len] = *format;
      len++;
    }
    format++;
  }
  str[len] = '\0';
  va_end(args);
  return len;
}