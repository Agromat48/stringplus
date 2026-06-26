#include "s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  void* result = S21_NULL;

  if (str != S21_NULL) {
    const unsigned char* ptr = (const unsigned char*)str;
    for (s21_size_t i = 0; i < n && result == S21_NULL; ++i) {
      if (ptr[i] == (unsigned char)c) {
        result = (void*)(ptr + i);
      }
    }
  }

  return result;
}

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  int result = 0;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    const unsigned char* ptr1 = (const unsigned char*)str1;
    const unsigned char* ptr2 = (const unsigned char*)str2;

    for (s21_size_t i = 0; i < n && result == 0; ++i) {
      result = ptr1[i] - ptr2[i];
    }
  }

  return result;
}

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  void* result = S21_NULL;

  if (dest != S21_NULL && src != S21_NULL) {
    unsigned char* dest_ptr = (unsigned char*)dest;
    const unsigned char* ptr = (const unsigned char*)src;

    for (s21_size_t i = 0; i < n; ++i) {
      dest_ptr[i] = ptr[i];
    }
    result = dest;
  }

  return result;
}

void* s21_memset(void* str, int c, s21_size_t n) {
  void* result = S21_NULL;

  if (str != S21_NULL) {
    unsigned char* ptr = (unsigned char*)str;
    for (s21_size_t i = 0; i < n; ++i) {
      ptr[i] = (unsigned char)c;
    }
    result = str;
  }

  return result;
}

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  char* result = S21_NULL;

  if (dest != S21_NULL && src != S21_NULL) {
    result = dest;

    while (*dest != '\0') dest++;

    s21_size_t i;
    for (i = 0; i < n && src[i] != '\0'; ++i) {
      dest[i] = src[i];
    }

    dest[i] = '\0';
  }

  return result;
}

char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;

  if (str != S21_NULL) {
    unsigned char uc = (unsigned char)c;
    s21_size_t i = 0;

    while (str[i] != '\0' && result == S21_NULL) {
      if ((unsigned char)str[i] == uc) {
        result = (char*)(str + i);
      }
      i++;
    }

    if (result == S21_NULL && uc == '\0') {
      result = (char*)(str + i);
    }
  }

  return result;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int result = 0;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    s21_size_t i = 0;

    while (i < n && str1[i] != '\0' && str2[i] != '\0' && result == 0) {
      if (str1[i] != str2[i]) result = str1[i] - str2[i];

      i++;
    }

    if (result == 0 && i < n) result = str1[i] - str2[i];
  }

  return result;
}

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  char* result = S21_NULL;

  if (dest != S21_NULL && src != S21_NULL) {
    s21_size_t i = 0;

    for (; i < n && src[i] != '\0'; ++i) {
      dest[i] = src[i];
    }

    while (i < n) {
      dest[i] = '\0';
      ++i;
    }

    result = dest;
  }

  return result;
}

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t result = 0;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    int found = 0;
    s21_size_t i = 0;

    while (str1[i] != '\0' && !found) {
      for (s21_size_t j = 0; str2[j] != '\0' && !found; ++j) {
        if (str1[i] == str2[j]) found = 1;
      }

      if (!found) ++i;
    }

    result = i;
  }

  return result;
}

#if defined __APPLE__
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define UNKNOWN "Unknown error: "

static const char* errorList[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};

#elif defined __linux__
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define UNKNOWN "Unknown error: "

static const char* errorList[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};

#endif

char* s21_strerror(int errorNumber) {
  static char result[512] = {0};

  if (errorNumber <= MIN_ERRLIST || errorNumber >= MAX_ERRLIST) {
    s21_sprintf(result, "%s%d", UNKNOWN, errorNumber);
  } else {
    s21_strncpy(result, errorList[errorNumber], 511);
  }

  return result;
}

s21_size_t s21_strlen(const char* str) {
  s21_size_t result = 0;

  if (str != S21_NULL) {
    while (str[result] != '\0') ++result;
  }

  return result;
}

char* s21_strpbrk(const char* str1, const char* str2) {
  char* result = S21_NULL;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    s21_size_t pos = s21_strcspn(str1, str2);

    if (str1[pos] != '\0') {
      result = (char*)(str1 + pos);
    }
  }

  return result;
}

char* s21_strrchr(const char* str, int c) {
  char* result = S21_NULL;

  if (str != S21_NULL) {
    unsigned char uc = (unsigned char)c;
    s21_size_t i = 0;

    while (str[i] != '\0') {
      if ((unsigned char)str[i] == uc) result = (char*)(str + i);

      i++;
    }
    if (result == S21_NULL && uc == '\0') result = (char*)(str + i);
  }

  return result;
}

char* s21_strstr(const char* haystack, const char* needle) {
  char* result = S21_NULL;

  if (haystack != S21_NULL && needle != S21_NULL) {
    s21_size_t needleLen = s21_strlen(needle);

    if (needleLen == 0) {
      result = (char*)haystack;
    } else {
      for (s21_size_t i = 0; result == S21_NULL && haystack[i] != '\0'; ++i) {
        if (haystack[i] == needle[0] &&
            s21_strncmp(haystack + i, needle, needleLen) == 0)
          result = (char*)(haystack + i);
      }
    }
  }

  return result;
}

char* s21_strtok(char* str, const char* delim) {
  static char* token = S21_NULL;

  if (str == S21_NULL) str = token;

  while ((str != S21_NULL) && (*str != '\0') &&
         (s21_strchr(delim, *str) != S21_NULL)) {
    str++;
  }

  if (str && *str == '\0') {
    str = S21_NULL;
    token = S21_NULL;
  }

  if (str && *str != '\0') {
    token = str;

    while (*token && !(s21_strchr(delim, *token))) {
      token++;
    }
  }

  if (token && *token) {
    *token = '\0';
    token++;
  }

  return str;
}

void* s21_to_upper(const char* str) {
  char* result = S21_NULL;

  if (str != S21_NULL) {
    s21_size_t length = s21_strlen(str);
    result = (char*)malloc(length + 1);

    if (result != S21_NULL) {
      for (s21_size_t i = 0; i < length; ++i) {
        result[i] =
            (str[i] >= 'a' && str[i] <= 'z') ? str[i] + ('A' - 'a') : str[i];
      }

      result[length] = '\0';
    }
  }

  return (void*)result;
}

void* s21_to_lower(const char* str) {
  char* result = S21_NULL;

  if (str != S21_NULL) {
    s21_size_t length = s21_strlen(str);
    result = (char*)malloc(length + 1);

    if (result != S21_NULL) {
      for (s21_size_t i = 0; i < length; ++i) {
        result[i] =
            (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + ('a' - 'A') : str[i];
      }

      result[length] = '\0';
    }
  }

  return (void*)result;
}

void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
  char* result = S21_NULL;

  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t srcLength = s21_strlen(src);
    s21_size_t strLength = s21_strlen(str);

    if (start_index <= srcLength) {
      result = (char*)malloc(srcLength + strLength + 1);

      if (result != S21_NULL) {
        s21_size_t i = 0;

        for (; i < start_index; ++i) result[i] = src[i];

        for (s21_size_t j = 0; j < strLength; ++j, ++i) result[i] = str[j];

        for (s21_size_t j = start_index; j < srcLength; ++j, ++i)
          result[i] = src[j];

        result[srcLength + strLength] = '\0';
      }
    }
  }

  return (void*)result;
}

void* s21_trim(const char* src, const char* trim_chars) {
  char* result = S21_NULL;

  if (src != S21_NULL) {
    s21_size_t length = s21_strlen(src);
    s21_size_t start = 0;
    s21_size_t end = length;

    while (start < length && s21_strchr(trim_chars, src[start]) != S21_NULL) {
      ++start;
    }

    while (end > start && s21_strchr(trim_chars, src[end - 1]) != S21_NULL) {
      --end;
    }

    s21_size_t new_length = (start < end) ? (end - start) : 0;

    result = (char*)malloc(new_length + 1);
    if (result != S21_NULL) {
      for (s21_size_t i = 0; i < new_length; ++i) {
        result[i] = src[start + i];
      }
      result[new_length] = '\0';
    }
  }

  return (void*)result;
}