#include "CStrUtil.h"
#include "CThrow.h"

//#define ALLOW_NAN 1

#ifdef ALLOW_NAN
#include <COS/COS.h>
#endif

#include <cstdio>
#include <cstring>
#include <cerrno>
#include <climits>
#include <algorithm>
#include <iostream>


static std::string base_chars_ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static std::string error_msg_;
static bool        hex_upper_;

std::string
CStrUtil::
toString(const char *str)
{
  return str;
}

std::string
CStrUtil::
toString(const std::string &str)
{
  return str;
}

std::string
CStrUtil::
toString(char c)
{
  std::string str;

  str += c;

  return str;
}

std::string
CStrUtil::
toString(bool flag)
{
  if (flag)
    return "true";
  else
    return "false";
}

std::string
CStrUtil::
toString(int integer)
{
  static char buffer[64];

  ::sprintf(buffer, "%d", integer);

  return std::string(buffer);
}

std::string
CStrUtil::
toString(uint integer)
{
  static char buffer[64];

  ::sprintf(buffer, "%u", integer);

  return std::string(buffer);
}

std::string
CStrUtil::
toString(long integer)
{
  static char buffer[64];

  ::sprintf(buffer, "%ld", integer);

  return std::string(buffer);
}

std::string
CStrUtil::
toString(ulong integer)
{
  static char buffer[64];

  ::sprintf(buffer, "%lu", integer);

  return std::string(buffer);
}

std::string
CStrUtil::
toString(double real)
{
  static char buffer[128];

#ifdef ALLOW_NAN
  if (COS::is_nan(real))
    strcpy(buffer, "NaN");
  else
    ::sprintf(buffer, "%g", real);
#else
  ::sprintf(buffer, "%g", real);
#endif

  return std::string(buffer);
}

std::string
CStrUtil::
toString(const std::vector<std::string> &words, const std::string &sep)
{
  return toString(words, 0, -1, sep);
}

std::string
CStrUtil::
toString(const std::vector<std::string> &words, int start, int end, const std::string &sep)
{
  std::string str;

  if (end == -1)
    end = words.size() - 1;

  for (int i = start; i <= end; i++) {
    if (i > start)
      str += sep;

    str += words[i];
  }

  return str;
}

std::string
CStrUtil::
toString(const char **words, uint num_words, const std::string &sep)
{
  return toString(words, num_words, 0, -1, sep);
}

std::string
CStrUtil::
toString(const char **words, uint num_words, int start, int end, const std::string &sep)
{
  std::string str;

  if (end == -1)
    end = num_words - 1;

  for (int i = start; i <= end; i++) {
    if (i > start)
      str += sep;

    str += words[i];
  }

  return str;
}

std::string
CStrUtil::
toString(std::vector<std::string>::const_iterator pstr1,
         std::vector<std::string>::const_iterator pstr2, const std::string &sep)
{
  std::vector<std::string>::const_iterator pstr;

  uint i = 0;

  std::string str;

  for (pstr = pstr1; pstr != pstr2; ++pstr, i++) {
    if (i > 0)
      str += sep;

    str += *pstr;
  }

  return str;
}

std::string
CStrUtil::
toString(const CStrWords &words, const std::string &sep)
{
  std::string str;

  uint num_words = words.size();

  for (uint i = 0; i < num_words; i++) {
    if (i > 0)
      str += sep;

    uint pos = str.size();

    while ((int) pos < words[i].getStartPos()) {
      str += sep;

      ++pos;
    }

    char c1 = words[i].getStartGroup();
    char c2 = words[i].getEndGroup();

    if (c1 != '\0')
      str += c1;

    int num_escapes = words[i].getNumEscapeChars();

    if (num_escapes > 0) {
      std::string word = words[i].getWord();

      for (int j = 0; j < num_escapes; j++) {
        const CStrCharPos &escape_char = words[i].getEscapeChar(j);

        std::string wordl = word.substr(0, escape_char.getPos());
        std::string wordr = word.substr(escape_char.getPos());

        word = wordl + escape_char.getChar() + wordr;
      }

      str += word;
    }
    else
      str += words[i].getWord();

    if (c2 != '\0')
      str += c2;
  }

  return str;
}

bool
CStrUtil::
decodeHexString(const std::string &str, uint *value)
{
  *value = 0;

  uint len = str.size();

  uint value1;

  for (uint i = 0; i < len; ++i) {
    if (! decodeHexChar(str[i], &value1))
      return false;

    *value = 16*(*value) + value1;
  }

  return true;
}

bool
CStrUtil::
decodeHexChar(unsigned char c, uint *value)
{
  switch (c) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      *value = c - '0';
      break;
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
      *value = c - 'a' + 10;
      break;
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
      *value = c - 'A' + 10;
      break;
    default:
      return false;
  }

  return true;
}

std::string
CStrUtil::
toHexString(signed int integer, uint width)
{
  if (integer < 0)
    return "-" + toHexString((uint) -integer, width);
  else
    return       toHexString((uint)  integer, width);
}

void
CStrUtil::
setHexUpper(bool upper)
{
  hex_upper_ = upper;
}

std::string
CStrUtil::
toHexString(uint integer, uint width)
{
  static char format[16];
  static char buffer[64];

  if (hex_upper_)
    ::sprintf(format, "%%0%dX", width);
  else
    ::sprintf(format, "%%0%dx", width);

  ::sprintf(buffer, format, integer);

  return std::string(buffer);
}

std::string
CStrUtil::
toOctString(int integer)
{
  std::string str;

  int i = integer;

  while (i >= 8) {
    int i1 = i / 8;
    int i2 = i % 8;

    str = (char) (i2 + '0') + str;

    i = i1;
  }

  if (i > 0)
    str = (char) (i + '0') + str;

  return str;
}

std::string
CStrUtil::
toOctStringInWidth(int integer, uint width)
{
  std::vector<int> digits ; digits .resize(width);
  std::vector<int> factors; factors.resize(width);

  factors[0] = 1;

  for (uint i = 1; i < width; ++i)
    factors[i] = 8*factors[i - 1];

  for (uint i = 0; i < width; ++i) {
    digits[i] = integer;

    for (uint j = 0; j < i; ++j)
      digits[i] -= digits[j]*factors[width - j - 1];

    digits[i] /= factors[width - i - 1];
  }

  std::string str;

  for (uint i = 0; i < width; ++i)
    str += (char) (digits[i] + '0');

  return str;
}

std::string
CStrUtil::
toBitString(int c)
{
  static char buffer[9];

  uint c1 = c;

  for (uint i = 0; i < 8; i++)
    buffer[i] = ((c1 >> (7 - i)) & 0x01) ? '1' : '0';

  buffer[8] = '\0';

  return std::string(buffer);
}

bool
CStrUtil::
isBool(const std::string &str)
{
  if (CStrUtil::casecmp(str, "true" ) == 0 ||
      CStrUtil::casecmp(str, "false") == 0 ||
      CStrUtil::casecmp(str, "yes"  ) == 0 ||
      CStrUtil::casecmp(str, "no"   ) == 0 ||
      CStrUtil::casecmp(str, "on"   ) == 0 ||
      CStrUtil::casecmp(str, "off"  ) == 0 ||
      CStrUtil::casecmp(str, "1"    ) == 0 ||
      CStrUtil::casecmp(str, "0"    ) == 0)
    return true;

  return false;
}

bool
CStrUtil::
toBool(const std::string &str)
{
  bool value;

  if (! toBool(str, &value)) {
    CTHROW(error_msg_);
    return false;
  }

  return value;
}

bool
CStrUtil::
toBool(const std::string &str, bool *value)
{
  if      (CStrUtil::casecmp(str, "true" ) == 0 ||
           CStrUtil::casecmp(str, "yes"  ) == 0 ||
           CStrUtil::casecmp(str, "on"   ) == 0 ||
           CStrUtil::casecmp(str, "1"    ) == 0)
    *value = true;
  else if (CStrUtil::casecmp(str, "false") == 0 ||
           CStrUtil::casecmp(str, "no"   ) == 0 ||
           CStrUtil::casecmp(str, "off"  ) == 0 ||
           CStrUtil::casecmp(str, "0"    ) == 0)
    *value = false;
  else {
    error_msg_ = "Invalid Boolean String";
    return false;
  }

  return true;
}

bool
CStrUtil::
isInteger(const std::string &str)
{
  const char *c_str = str.c_str();

  int i = 0;

  while (c_str[i] != 0 && ::isspace(c_str[i]))
    ++i;

  if (c_str[i] == '\0')
    return false;

  const char *p;

  errno = 0;

  strtol(&c_str[i], (char **) &p, 10);

  if (errno == ERANGE)
    return false;

  while (*p != 0 && ::isspace(*p))
    ++p;

  if (*p != '\0')
    return false;

  return true;
}

long
CStrUtil::
toInteger(const std::string &str)
{
  long integer;

  if (! toInteger(str, &integer)) {
    CTHROW(error_msg_);
    return 0;
  }

  return integer;
}

bool
CStrUtil::
toInteger(const std::string &str, short *integer)
{
  long integer1;

  if (! toInteger(str, &integer1))
    return false;

  *integer = (short) integer1;

  return true;
}

bool
CStrUtil::
toInteger(const std::string &str, int *integer)
{
  long integer1;

  if (! toInteger(str, &integer1))
    return false;

  *integer = (int) integer1;

  return true;
}

bool
CStrUtil::
toInteger(const std::string &str, uint *integer)
{
  long integer1;

  if (! toInteger(str, &integer1))
    return false;

  if (integer1 < 0)
    return false;

  *integer = (uint) integer1;

  return true;
}

bool
CStrUtil::
toInteger(const std::string &str, long *integer)
{
  const char *c_str = str.c_str();

  int i = 0;

  while (c_str[i] != 0 && ::isspace(c_str[i]))
    ++i;

  if (c_str[i] == '\0') {
    error_msg_ = "Empty String";
    return false;
  }

  const char *p;

  errno = 0;

  *integer = strtol(&c_str[i], (char **) &p, 10);

  if (errno == ERANGE) {
    error_msg_ = "Out of Range";
    return false;
  }

  while (*p != 0 && ::isspace(*p))
    ++p;

  if (*p != '\0') {
    error_msg_ = "Trailing Characters";
    return false;
  }

  return true;
}

bool
CStrUtil::
isBaseInteger(const std::string &str, uint base)
{
  if (base < 2 || base > base_chars_.size()) {
    CTHROW("Unsupported Base " + CStrUtil::toString(base));
    return false;
  }

  uint i   = 0;
  uint len = str.size();

  while (i < len) {
    int c = str[i];

    if (! isBaseChar(c, base, NULL))
      return false;

    ++i;
  }

  return true;
}

long
CStrUtil::
toBaseInteger(const std::string &str, uint base)
{
  long integer;

  if (! toBaseInteger(str, base, &integer)) {
    CTHROW(error_msg_);
    return 0;
  }

  return integer;
}

bool
CStrUtil::
toBaseInteger(const std::string &str, uint base, int *integer)
{
  long integer1;

  if (! toBaseInteger(str, base, &integer1)) {
    CTHROW(error_msg_);
    return false;
  }

  *integer = (int) integer1;

  return true;
}

bool
CStrUtil::
toBaseInteger(const std::string &str, uint base, uint *integer)
{
  long integer1;

  if (! toBaseInteger(str, base, &integer1)) {
    CTHROW(error_msg_);
    return false;
  }

  *integer = (uint) integer1;

  return true;
}

bool
CStrUtil::
toBaseInteger(const std::string &str, uint base, long *integer)
{
  *integer = 0;

  if (base < 2 || base > base_chars_.size()) {
    error_msg_ = "Unsupported Base " + CStrUtil::toString(base);
    return false;
  }

  uint i   = 0;
  uint len = str.size();

  while (i < len) {
    int c = str[i];

    int value;

    if (! isBaseChar(c, base, &value))
      return false;

    long integer1 = base*(*integer) + value;

    if (long((integer1 - (long) value)/base) != *integer) {
      error_msg_ = "Overflow.";
      return false;
    }

    *integer = integer1;

    ++i;
  }

  if (*integer > INT_MAX || *integer < INT_MIN) {
    error_msg_ = "Overflow.";
    return false;
  }

  return true;
}

bool
CStrUtil::
isReal(const std::string &str)
{
  const char *c_str = str.c_str();

  int i = 0;

  while (c_str[i] != 0 && ::isspace(c_str[i]))
    ++i;

  if (c_str[i] == '\0')
    return false;

  const char *p;

#ifdef ALLOW_NAN
  if (COS::has_nan() && strncmp(&c_str[i], "NaN", 3) == 0)
    p = &c_str[i + 3];
  else {
    errno = 0;

    strtod(&c_str[i], (char **) &p);

    if (errno == ERANGE)
      return false;
  }
#else
  errno = 0;

  strtod(&c_str[i], (char **) &p);

  if (errno == ERANGE)
    return false;
#endif

  while (*p != 0 && ::isspace(*p))
    ++p;

  if (*p != '\0')
    return false;

  return true;
}

double
CStrUtil::
toReal(const std::string &str)
{
  double real;

  if (! toReal(str, &real)) {
    CTHROW(error_msg_);
    return 0.0;
  }

  return real;
}

bool
CStrUtil::
toReal(const std::string &str, double *real)
{
  const char *c_str = str.c_str();

  int i = 0;

  while (c_str[i] != 0 && ::isspace(c_str[i]))
    ++i;

  if (c_str[i] == '\0') {
    error_msg_ = "Empty String";

    return false;
  }

  const char *p;

#ifdef ALLOW_NAN
  if (COS::has_nan() && strncmp(&c_str[i], "NaN", 3) == 0) {
    p = &c_str[i + 3];

    COS::set_nan(real);
  }
  else {
    errno = 0;

    *real = strtod(&c_str[i], (char **) &p);

    if (errno == ERANGE) {
      error_msg_ = "Out of Range";

      return false;
    }
  }
#else
  errno = 0;

  *real = strtod(&c_str[i], (char **) &p);

  if (errno == ERANGE) {
    error_msg_ = "Out of Range";

    return false;
  }
#endif

  while (*p != 0 && ::isspace(*p))
    ++p;

  if (*p != '\0') {
    error_msg_ = "Trailing Characters";

    return false;
  }

  return true;
}

bool
CStrUtil::
isBaseChar(int c, uint base, int *value)
{
  if (base < 2 || base > base_chars_.size()) {
    CTHROW("Unsupported Base " + CStrUtil::toString(base));
    return false;
  }

  int c1 = c;

  if (::islower(c1))
    c1 = toupper(c1);

  std::string::size_type pos = base_chars_.find((char) c1);

  if (pos == std::string::npos || pos >= base) {
    error_msg_ = std::string("Invalid Character ") + char(c) +
                 " for Base " + CStrUtil::toString(base);
    return false;
  }

  if (value != NULL)
    *value = int(pos);

  return true;
}

bool
CStrUtil::
isCComment(const std::string &str, uint pos)
{
  uint len = str.size();

  if (pos < len - 1 && str[pos] == '/' && str[pos + 1] == '*')
    return true;

  return false;
}

bool
CStrUtil::
readCComment(const std::string &str, uint *pos, bool *in_comment, std::string &comment)
{
  uint len = str.size();

  if (! *in_comment) {
    if (*pos < len - 1 && str[*pos] == '/' && str[*pos + 1] == '*') {
      comment  = str[(*pos)++];
      comment += str[(*pos)++];
    }
    else
      return false;
  }

  *in_comment = true;

  while (*pos < len - 1 && ! (str[*pos] == '*' && str[*pos + 1] == '/'))
    comment += str[(*pos)++];

  if (*pos < len) {
    comment += str[(*pos)++];
    comment += str[(*pos)++];

    *in_comment = false;
  }

  return true;
}

bool
CStrUtil::
isCNumber(const std::string &str, uint pos)
{
  uint len = str.size();

  if (pos < len && ::isdigit(str[pos]))
    return true;

  if (pos < len - 1 && str[pos] == '.' && ::isdigit(str[pos + 1]))
    return true;

  return false;
}

bool
CStrUtil::
readCNumber(const std::string &str, uint *pos, std::string &number)
{
  number = "";

  uint len = str.size();

  // hexadecimal-literal:
  //  '0x' hexadecimal-digits integer-suffix(opt)
  //  '0X' hexadecimal-digits integer-suffix(opt)
  //
  // hexadecimal-digits:
  //   hexadecimal-digit hexadecimal-digits(opt)

  if (*pos < len - 1 && str[*pos] == '0' && (str[*pos + 1] == 'x' || str[*pos + 1] == 'X')) {
    // '0x' or '0X'
    number += str[(*pos)++];
    number += str[(*pos)++];

    // hexadecimal-digits
    while (*pos < len && ::isxdigit(str[*pos]))
      number += str[(*pos)++];

    // integer-suffix
    if (*pos < len) {
      if      (str[*pos] == 'u' || str[*pos] == 'U') {
        number += str[(*pos)++];

        if (*pos < len && (str[*pos] == 'l' || str[*pos] == 'L'))
          number += str[(*pos)++];
      }
      else if (str[*pos] == 'l' || str[*pos] == 'L') {
        number += str[(*pos)++];

        if (*pos < len && (str[*pos] == 'u' || str[*pos] == 'U'))
          number += str[(*pos)++];
      }
    }
  }

  // octal-literal:
  //  '0' octal-digits integer-suffix(opt)
  //
  // octal-digits:
  //   octal-digit octal-digits(opt)

  // floating-literal:
  //  fractional-constant exponent-part(opt) floating-suffix(opt)
  //  digit-sequence exponent-part floating-suffix(opt)
  //
  // fractional-constant:
  //  digit-sequence(opt) . digit-sequence
  //  digit-sequence .
  //
  // digit-sequence:
  //  digit
  //  digit-sequence digit
  //
  // exponent-part:
  //  e sign(opt) digit-sequence
  //  E sign(opt) digit-sequence

  else {
    bool point_found    = false;
    bool exponent_found = false;

    // Get leading digits
    while (*pos < len && ::isdigit(str[*pos]))
      number += str[(*pos)++];

    // Get decimal point and digits
    if (*pos < len && str[*pos] == '.') {
      point_found = true;

      number += str[(*pos)++];

      while (*pos < len && ::isdigit(str[*pos]))
        number += str[(*pos)++];
    }

    // Get exponent
    if (*pos < len && (str[*pos] == 'e' || str[*pos] == 'E')) {
      exponent_found = true;

      number += str[(*pos)++];

      // optional sign
      if (*pos < len && (str[*pos] == '+' || str[*pos] == '-'))
        number += str[(*pos)++];

      // must have digits
      if (*pos == len || ! ::isdigit(str[*pos]))
        return false;

      // read exponent digits
      while (*pos < len && ::isdigit(str[*pos]))
        number += str[(*pos)++];
    }

    // empty strint is no good
    if (number.size() == 0)
      return false;

    if (! point_found && ! exponent_found) {
      bool floating_specifier = false;

      // If not floating point get any integer type specifier
      if (*pos < len) {
        if      (str[*pos] == 'u' || str[*pos] == 'U') {
          number += str[(*pos)++];

          if (*pos < len && (str[*pos] == 'l' || str[*pos] == 'L'))
            number += str[(*pos)++];
        }
        else if (str[*pos] == 'l' || str[*pos] == 'L') {
          number += str[(*pos)++];

          if (*pos < len && (str[*pos] == 'u' || str[*pos] == 'U'))
            number += str[(*pos)++];
        }
        else if (str[*pos] == 'f' || str[*pos] == 'F') {
          number += str[(*pos)++];

          floating_specifier = true;
        }
      }

      if (! floating_specifier) {
        // Ensure leading zero integer is valid octal
        if (number[0] == '0' &&
            (number.find('8') != std::string::npos || number.find('9') != std::string::npos))
          return false;
      }
    }

    // Get any floating point type specifier

    else {
      if (*pos < len &&
          (str[*pos] == 'f' || str[*pos] == 'F' ||
           str[*pos] == 'l' || str[*pos] == 'L'))
        number += str[(*pos)++];
    }
  }

  return true;
}

bool
CStrUtil::
isCCharacter(const std::string &str, uint pos)
{
  uint len = str.size();

  if (pos < len && str[pos] == '\'')
    return true;

  if (pos < len - 1 && str[pos] == 'L' && str[pos + 1] == '\'')
    return true;

  return false;
}

bool
CStrUtil::
readCCharacter(const std::string &str, uint *pos, std::string &character)
{
  // TODO: support multi-character sequences

  uint len = str.size();

  character = "";

  if      (*pos < len - 1 && str[*pos] == 'L' && str[*pos + 1] == '\'') {
    character += str[(*pos)++];
    character += str[(*pos)++];
  }
  else if (*pos < len && str[*pos] == '\'')
    character += str[(*pos)++];
  else
    return false;

  /* Get Normal Character (not ' or \) */

  if      (*pos < len && str[*pos] != '\'' && str[*pos] != '\\') {
    character += str[(*pos)++];
  }

  /* If \ then process Special Character, Escaped Special Character,
     Octal Character Definition or Hex Character Definition */

  else if (*pos < len && str[*pos] == '\\') {
    character += str[(*pos)++];

    if (*pos < len) {
      switch (str[*pos]) {
        /* Special Character */

        case 'a': case 'b': case 'f': case 'n': case 'r': case 't': case 'v': {
          character += str[(*pos)++];
          break;
        }

        /* Escaped Special Character */

        case '\'': case '\"': case '?': case '\\': {
          character += str[(*pos)++];
          break;
        }

        /* Octal Character Definition */

        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': {
          // Add Octal Character

          character += str[(*pos)++];

          /* Add up to two more Octal Characters */

          if (*pos < len && CStrUtil::isodigit(str[*pos])) {
            character += str[(*pos)++];

            if (*pos < len && CStrUtil::isodigit(str[*pos]))
              character += str[(*pos)++];
          }

          break;
        }

        /* Hex Character Definition */

        case 'x': {
          // Add prefix

          character += str[(*pos)++];

          if (*pos >= len || ! ::isxdigit(str[*pos]))
            return false;

          /* Add any Number of Hex Characters */

          while (*pos < len && ::isxdigit(str[*pos]))
            character += str[(*pos)++];

          break;
        }

        // Universal Character Name (4 hex) (C++ only)

        case 'u': {
          // Add prefix

          character += str[(*pos)++];

          // Add 4 hex characters

          for (uint i = 0; i < 4; ++i) {
            if (*pos >= len || ! ::isxdigit(str[*pos]))
              return false;

            character += str[(*pos)++];
          }

          break;
        }

        // Universal Character Name (8 hex) (C++ only)

        case 'U': {
          // Add prefix

          character += str[(*pos)++];

          // Add 8 hex characters

          for (uint i = 0; i < 8; ++i) {
            if (*pos >= len || ! ::isxdigit(str[*pos]))
              return false;

            character += str[(*pos)++];
          }

          break;
        }

        default:
          return false;

          break;
      }
    }
  }
  else
    return false;

  /* Check for Terminating ' */

  if (*pos >= len || str[*pos] != '\'')
    return false;

  character += str[(*pos)++];

  return true;
}

bool
CStrUtil::
isCString(const std::string &str, uint pos)
{
  uint len = str.size();

  if (pos < len && str[pos] == '\"')
    return true;

  if (pos < len - 1 && str[pos] == 'L' && str[pos + 1] == '\"')
    return true;

  return false;
}

bool
CStrUtil::
readCString(const std::string &str, uint *pos, std::string &cstring)
{
  uint len = str.size();

  cstring = "";

  // get leading " or L"

  if      (*pos < len && str[*pos] == 'L' && str[*pos + 1] == '\"') {
    cstring += str[(*pos)++];
    cstring += str[(*pos)++];
  }
  else if (*pos < len && str[*pos] == '\"')
    cstring += str[(*pos)++];
  else
    return false;

  /* Get Characters until Closing " */

  while (*pos < len) {
    /* Ignore Escaped " or / */

    if      ((str[*pos] == '\\' && str[*pos + 1] == '\"') ||
             (str[*pos] == '\\' && str[*pos + 1] == '\\')) {
      cstring += str[(*pos)++];
      cstring += str[(*pos)++];
    }

    /* Break on Closing " */

    else if (str[*pos] == '\"')
      break;

    /* Get any Other Character */

    else
      cstring += str[(*pos)++];
  }

  /* If no Closing " then Fail */

  if (*pos == len || str[*pos] != '\"')
    return false;

  /* Get Closing " */

  cstring += str[(*pos)++];

  return true;
}

std::string
CStrUtil::
stripSpaces(const std::string &str, bool front, bool back)
{
  uint len = str.size();

  uint start_index = 0;

  if (front) {
    uint i = 0;

    while (i < len && ::isspace(str[i]))
      ++i;

    if (i >= len)
      return "";

    start_index = i;
  }

  uint end_index = len - 1;

  if (back) {
    int i = len - 1;

    while (i >= 0 && ::isspace(str[i]))
      i--;

    if (i < 0)
      return "";

    end_index = i;
  }

  return str.substr(start_index, end_index - start_index + 1);
}

const char *
CStrUtil::
stripSpaces(const char *str, bool front, bool back)
{
  std::string str1(str);

  static std::string str2 = stripSpaces(str1, front, back);

  return str2.c_str();
}

char *
CStrUtil::
stripSpaces(char *str, bool front, bool back)
{
  uint len = strlen(str);

  int start_index = 0;

  if (front) {
    uint i = 0;

    while (i < len && ::isspace(str[i]))
      ++i;

    if (i >= len) {
      str[0] = '\0';
      return str;
    }

    start_index = i;
  }

  int end_index = len - 1;

  if (back) {
    int i = len - 1;

    while (i >= 0 && ::isspace(str[i]))
      i--;

    if (i < 0) {
      str[0] = '\0';
      return str;
    }

    end_index = i;
  }

  str[end_index + 1] = '\0';

  if (start_index > 0)
    memmove(str, str + start_index, end_index - start_index + 2);

  return str;
}

std::string
CStrUtil::
compressSpaces(const std::string &str)
{
  uint len = str.size();

  uint i = 0;

  std::string str1;

  skipSpace(str, &i);

  while (i < len) {
    if (::isspace(str[i])) {
      skipSpace(str, &i);

      if (i < len)
        str1 += " ";
    }
    else
      str1 += str[i++];
  }

  return str1;
}

std::string
CStrUtil::
toUpper(const std::string &str)
{
  std::string str1 = str;

  uint len = str1.size();

  for (uint i = 0; i < len; i++)
    if (::islower(str1[i]))
      str1[i] = toupper(str1[i]);

  return str1;
}

char *
CStrUtil::
toUpper(char *str)
{
  uint len = strlen(str);

  for (uint i = 0; i < len; i++)
    if (::islower(str[i]))
      str[i] = toupper(str[i]);

  return str;
}

const char *
CStrUtil::
toUpper(const char *str)
{
  std::string str1(str);

  static std::string str2 = toUpper(str1);

  return str2.c_str();
}

std::string
CStrUtil::
toLower(const std::string &str)
{
  std::string str1 = str;

  uint len = str1.size();

  for (uint i = 0; i < len; i++)
    if (::isupper(str1[i]))
      str1[i] = tolower(str1[i]);

  return str1;
}

char *
CStrUtil::
toLower(char *str)
{
  uint len = strlen(str);

  for (uint i = 0; i < len; i++)
    if (::isupper(str[i]))
      str[i] = tolower(str[i]);

  return str;
}

const char *
CStrUtil::
toLower(const char *str)
{
  std::string str1(str);

  static std::string str2 = toLower(str1);

  return str2.c_str();
}

std::string
CStrUtil::
capitalize(const std::string &str)
{
  std::string str1 = str;

  uint len = str1.size();

  for (uint i = 0; i < len; i++) {
    if (i == 0 && ::islower(str1[i]))
      str1[i] = toupper(str1[i]);

    if (i > 0 && ::isupper(str1[i]))
      str1[i] = tolower(str1[i]);
  }

  return str1;
}

#if 0
int
CStrUtil::
gregsub(const std::string &istr, const CRegExp &pattern, const std::string &rstr, std::string &ostr)
{
  int count = 0;

  ostr = "";

  std::string istr1 = istr;

  while (pattern.find(istr1)) {
    ++count;

    int spos, epos;

    if (! pattern.getMatchRange(&spos, &epos))
      return false;

    if (spos > 0)
      ostr += istr1.substr(0, spos);

    std::string rstr1;

    uint rlen = rstr.size();

    for (uint i = 0; i < rlen; ++i) {
      if      (rstr[i] == '\\') {
        rstr1 += rstr[i++];

        if (i < rlen)
          rstr1 += rstr[i];
      }
      else if (rstr[i] == '&')
        rstr1 += istr1.substr(spos, epos - spos + 1);
      else
        rstr1 += rstr[i];
    }

    ostr += rstr1;

    istr1 = istr1.substr(epos + 1);
  }

  ostr += istr1;

  return count;
}

bool
CStrUtil::
regsub(const std::string &istr, const CRegExp &pattern, const std::string &rstr, std::string &ostr)
{
  if (! pattern.find(istr))
    return false;

  int spos, epos;

  if (! pattern.getMatchRange(&spos, &epos))
    return false;

  if (spos > 0)
    ostr += istr.substr(0, spos);

  std::string rstr1;

  uint rlen = rstr.size();

  for (uint i = 0; i < rlen; ++i) {
    if      (rstr[i] == '\\') {
      rstr1 += rstr[i++];

      if (i < rlen)
        rstr1 += rstr[i];
    }
    else if (rstr[i] == '&')
      rstr1 += istr.substr(spos, epos - spos + 1);
    else
      rstr1 += rstr[i];
  }

  ostr += rstr1;

  ostr += istr.substr(epos + 1);

  return true;
}
#endif

std::string
CStrUtil::
replace(const std::string &str, const std::string &old_str, const std::string &new_str)
{
  std::string::size_type pos = str.find(old_str);

  if (pos == std::string::npos)
    return str;

  std::string lhs = str.substr(0, pos);
  std::string rhs = str.substr(pos + old_str.size());

  return (lhs + new_str + rhs);
}

std::string
CStrUtil::
translate(const std::string &str, const std::string &old_chars,
          const std::string &new_chars, bool remove)
{
  bool one_to_n = (old_chars.size() == 1);

  std::string str1 = str;

  uint len = str1.size();

  for (uint i = 0; i < len; i++) {
    std::string::size_type pos = old_chars.find(str1[i]);

    if (pos == std::string::npos)
      continue;

    if (pos < new_chars.size()) {
      if (one_to_n) {
        str1 = str1.substr(0, i) + new_chars + str1.substr(i + 1);

        len = str1.size();
      }
      else
        str1[i] = new_chars[pos];

      continue;
    }

    if (remove) {
      std::string strl = "";
      std::string strr = "";

      if (i > 0)
        strl = str1.substr(0, i);

      if (i + 1 < len)
        strr = str1.substr(i + 1);

      str1 = strl + strr;

      len = str1.size();

      i--;
    }
  }

  return str1;
}




bool
CStrUtil::
skipSpace(const char *str, uint *pos)
{
  if (str[*pos] == '\0' || ! ::isspace(str[*pos]))
    return false;

  while (str[*pos] != '\0' && ::isspace(str[*pos]))
    ++(*pos);

  return true;
}

bool
CStrUtil::
skipSpace(const char **str)
{
  if (**str == '\0' || ! ::isspace(**str))
    return false;

  while (**str != '\0' && ::isspace(**str))
    ++(*str);

  return true;
}

bool
CStrUtil::
skipSpace(char **str)
{
  if (**str == '\0' || ! ::isspace(**str))
    return false;

  while (**str != '\0' && ::isspace(**str))
    ++(*str);

  return true;
}

bool
CStrUtil::
skipSpace(const std::string &str, uint *pos)
{
  uint len = str.size();

  if (*pos >= len || ! ::isspace(str[*pos]))
    return false;

  while (*pos < len && ::isspace(str[*pos]))
    ++(*pos);

  return true;
}

bool
CStrUtil::
skipSpace(const std::string &str, int *pos)
{
  uint len = str.size();

  if (*pos >= (int) len || ! ::isspace(str[*pos]))
    return false;

  while (*pos < (int) len && ::isspace(str[*pos]))
    ++(*pos);

  return true;
}

bool
CStrUtil::
skipNonSpace(const char *str, uint *pos)
{
  if (str[*pos] == '\0' || ::isspace(str[*pos]))
    return false;

  while (str[*pos] != '\0' && ! ::isspace(str[*pos]))
    ++(*pos);

  return true;
}

bool
CStrUtil::
skipNonSpace(const char **str)
{
  if (**str == '\0' || ::isspace(**str))
    return false;

  while (**str != '\0' && ! ::isspace(**str))
    ++(*str);

  return true;
}

bool
CStrUtil::
skipNonSpace(char **str)
{
  if (**str == '\0' || ::isspace(**str))
    return false;

  while (**str != '\0' && ! ::isspace(**str))
    ++(*str);

  return true;
}

bool
CStrUtil::
skipNonSpace(const std::string &str, int *pos)
{
  int len = str.size();

  if (*pos >= len || ::isspace(str[*pos]))
    return false;

  while (*pos < len && ! ::isspace(str[*pos]))
    ++(*pos);

  return true;
}

bool
CStrUtil::
skipNonSpace(const std::string &str, uint *pos)
{
  uint len = str.size();

  if (*pos >= len || ::isspace(str[*pos]))
    return false;

  while (*pos < len && ! ::isspace(str[*pos]))
    ++(*pos);

  return true;
}

bool
CStrUtil::
skipDoubleQuotedString(const std::string &str, uint *pos)
{
  uint len = str.size();

  if (*pos >= len || str[*pos] != '\"')
    return false;

  ++(*pos);

  while (*pos < len) {
    if      (str[*pos] == '\\') {
      ++(*pos);

      if (*pos < len)
        ++(*pos);
    }
    else if (str[*pos] == '\"')
      break;
    else
      ++(*pos);
  }

  if (*pos >= len)
    return false;

  ++(*pos);

  return true;
}

bool
CStrUtil::
skipSingleQuotedString(const std::string &str, uint *pos)
{
  uint len = str.size();

  if (*pos >= len || str[*pos] != '\'')
    return false;

  if (str[*pos] != '\'')
    return false;

  ++(*pos);

  while (*pos < len) {
    if      (str[*pos] == '\\') {
      ++(*pos);

      if (*pos < len)
        ++(*pos);
    }
    else if (str[*pos] == '\'')
      break;
    else
      ++(*pos);
  }

  if (*pos >= len)
    return false;

  ++(*pos);

  return true;
}

bool
CStrUtil::
skipBackQuotedString(const std::string &str, uint *pos)
{
  if (str[*pos] != '`')
    return false;

  uint len = str.size();

  ++(*pos);

  while (*pos < len) {
    if      (str[*pos] == '\\') {
      ++(*pos);

      if (*pos < len)
        ++(*pos);
    }
    else if (str[*pos] == '`')
      break;
    else
      ++(*pos);
  }

  if (*pos >= len)
    return false;

  ++(*pos);

  return true;
}


void
CStrUtil::
addFields(const std::string &str, std::vector<std::string> &words,
          const std::string &splitters, bool skipEmpty)
{
  uint i = 0;

  std::string word;

  uint len = str.size();

  bool use_splitters = ! splitters.empty();

  if (skipEmpty) {
    // skip separators at front of string
    if (use_splitters) {
      while (i < len && splitters.find(str[i]) != std::string::npos)
        ++i;
    }
    else {
      while (i < len && isspace(str[i]))
        ++i;
    }
  }

  bool sep = false;

  uint start_pos = i;
  uint end_pos   = i;

  while (i < len) {
    // add fields
    if (use_splitters) {
      while (i < len && splitters.find(str[i]) == std::string::npos)
        ++i;
    }
    else {
      while (i < len && ! isspace(str[i]))
        ++i;
    }

    end_pos = i;

    if (end_pos > start_pos) {
      word = str.substr(start_pos, end_pos - start_pos);

      words.push_back(word);
    }
    else {
      if (! skipEmpty) {
        word = "";

        words.push_back(word);
      }
    }

    // skip separator
    if (use_splitters) {
      if (i < len && splitters.find(str[i]) != std::string::npos) {
        ++i;

        sep = true;
      }
      else
        sep = false;
    }
    else {
      if (i < len && isspace(str[i])) {
        ++i;

        sep = true;
      }
      else
        sep = false;
    }

    if (skipEmpty) {
      // skip extra separators
      if (use_splitters) {
        while (i < len && splitters.find(str[i]) != std::string::npos)
          ++i;
      }
      else {
        while (i < len && isspace(str[i]))
          ++i;
      }
    }

    start_pos = i;
  }

  if (sep) {
    end_pos = i;

    if (end_pos > start_pos) {
      word = str.substr(start_pos, end_pos - start_pos);

      words.push_back(word);
    }
    else {
      if (! skipEmpty) {
        word = "";

        words.push_back(word);
      }
    }
  }
}


bool
CStrUtil::
readInteger(const std::string &str, uint *pos, int *integer)
{
//skipSpace(str, pos);

  //------

  uint i = *pos;

  //------

  if (! skipInteger(str, pos))
    return false;

  //------

  if (integer != NULL) {
    if (! toInteger(str.substr(i, *pos - i), integer))
      return false;
  }

  //------

  return true;
}

bool
CStrUtil::
readInteger(const char *str, uint *pos, int *integer)
{
//skipSpace(str, pos);

  //------

  uint i = *pos;

  //------

  if (! skipInteger(str, pos))
    return false;

  //------

  if (integer != NULL) {
    if (! toInteger(std::string(&str[i], *pos - i), integer))
      return false;
  }

  //------

  return true;
}

bool
CStrUtil::
readBaseInteger(const std::string &str, uint base, uint *pos, int *integer)
{
//skipSpace(str, pos);

  //------

  uint i = *pos;

  //------

  if (! skipBaseInteger(str, base, pos))
    return false;

  //------

  if (integer != NULL)
    *integer = toBaseInteger(str.substr(i, *pos - i), base);

  //------

  return true;
}

bool
CStrUtil::
readBaseInteger(const char *str, uint base, uint *pos, int *integer)
{
//skipSpace(str, pos);

  //------

  uint i = *pos;

  //------

  if (! skipBaseInteger(str, base, pos))
    return false;

  //------

  if (integer != NULL)
    *integer = toBaseInteger(std::string(&str[i], *pos - i), base);

  //------

  return true;
}

bool
CStrUtil::
skipInteger(const std::string &str, uint *pos)
{
  uint len = str.size();

  if (*pos < len && (str[*pos] == '+' || str[*pos] == '-'))
    ++(*pos);

  if (*pos >= len || ! ::isdigit(str[*pos]))
    return false;

  ++(*pos);

  while (*pos < len && ::isdigit(str[*pos]))
    ++(*pos);

  return true;
}

bool
CStrUtil::
skipInteger(const char *str, uint *pos)
{
  if (str[*pos] != '\0' && (str[*pos] == '+' || str[*pos] == '-'))
    ++(*pos);

  if (str[*pos] == '\0' || ! ::isdigit(str[*pos]))
    return false;

  ++(*pos);

  while (str[*pos] != '\0' && ::isdigit(str[*pos]))
    ++(*pos);

  return true;
}

bool
CStrUtil::
skipBaseInteger(const std::string &str, uint base, uint *pos)
{
  uint len = str.size();

  if (*pos < len && (str[*pos] == '+' || str[*pos] == '-'))
    ++(*pos);

  if (*pos >= len || ! isBaseChar(str[*pos], base, NULL))
    return false;

  ++(*pos);

  while (*pos < len && isBaseChar(str[*pos], base, NULL))
    ++(*pos);

  return true;
}

bool
CStrUtil::
skipBaseInteger(const char *str, uint base, uint *pos)
{
  if (str[*pos] != '\0' && (str[*pos] == '+' || str[*pos] == '-'))
    ++(*pos);

  if (str[*pos] == '\0' || ! isBaseChar(str[*pos], base, NULL))
    return false;

  ++(*pos);

  while (str[*pos] != '\0' && isBaseChar(str[*pos], base, NULL))
    ++(*pos);

  return true;
}

bool
CStrUtil::
readReal(const std::string &str, uint *pos, double *real)
{
  double r       = 0.0;
  int    i       = 0;
  bool   is_real = false;

  if (! readNumber(str, pos, r, i, is_real))
    return false;

  if (is_real)
    *real = r;
  else
    *real = i;

  return true;
}

bool
CStrUtil::
readNumber(const std::string &str, uint *pos, double &real, int &integer, bool &is_real)
{
  is_real = false;

  //------

  uint len = str.size();

  std::string number_str;

  //------

  if (*pos < len && (str[*pos] == '+' || str[*pos] == '-'))
    number_str += str[(*pos)++];

  //------

  while (*pos < len && ::isdigit(str[*pos]))
    number_str += str[(*pos)++];

  //------

  if (*pos < len && str[*pos] == '.') {
    is_real = true;

    number_str += str[(*pos)++];

    while (*pos < len && ::isdigit(str[*pos]))
      number_str += str[(*pos)++];
  }

  //------

  if (*pos < len && (str[*pos] == 'e' || str[*pos] == 'E')) {
    is_real = true;

    number_str += str[(*pos)++];

    if (*pos < len && (str[*pos] == '+' || str[*pos] == '-'))
      number_str += str[(*pos)++];

    if (*pos >= len || ! ::isdigit(str[*pos]))
      return false;

    while (*pos < len && ::isdigit(str[*pos]))
      number_str += str[(*pos)++];
  }

  //------

  if (number_str.size() == 0)
    return false;

  if (is_real) {
    if (! toReal(number_str, &real))
      return false;
  }
  else {
    if (! toInteger(number_str, &integer))
      return false;
  }

  //------

  return true;
}

bool
CStrUtil::
readReal(const char *str, uint *pos, double *real)
{
//skipSpace(str, pos);

  //------

  std::string number_str;

  //------

  if (str[*pos] != '\0' && (str[*pos] == '+' || str[*pos] == '-'))
    number_str += str[(*pos)++];

  //------

  while (str[*pos] != '\0' && ::isdigit(str[*pos]))
    number_str += str[(*pos)++];

  //------

  if (str[*pos] != '\0' && str[*pos] == '.') {
    number_str += str[(*pos)++];

    while (str[*pos] != '\0' && ::isdigit(str[*pos]))
      number_str += str[(*pos)++];
  }

  //------

  if (str[*pos] != '\0' && (str[*pos] == 'e' || str[*pos] == 'E')) {
    number_str += str[(*pos)++];

    if (str[*pos] != '\0' && (str[*pos] == '+' || str[*pos] == '-'))
      number_str += str[(*pos)++];

    if (*pos == '\0' || ! ::isdigit(str[*pos]))
      return false;

    while (str[*pos] != '\0' && ::isdigit(str[*pos]))
      number_str += str[(*pos)++];
  }

  //------

  if (number_str.size() == 0)
    return false;

  if (real != NULL) {
    if (! toReal(number_str, real))
      return false;
  }

  //------

  return true;
}

void
CStrUtil::
fput(const std::string &str, FILE *fp)
{
  fputs(str.c_str(), fp);
}

bool
CStrUtil::
isIdentifier(const std::string &str)
{
  uint len = str.size();

  if (len == 0)
    return false;

  if (str[0] != '_' && ! ::isalpha(str[0]))
    return false;

  for (uint i = 1; i < len; i++)
    if (str[i] != '_' && ! ::isalnum(str[i]))
      return false;

  return true;
}

bool
CStrUtil::
isIdentifier(const std::string &str, uint pos)
{
  uint len = str.size();

  if (pos < len && (str[pos] == '_' || ::isalpha(str[pos])))
    return true;

  return false;
}

bool
CStrUtil::
readIdentifier(const std::string &str, uint *pos, std::string &identifier)
{
  uint len = str.size();

  if (*pos < len && (str[*pos] == '_' || ::isalpha(str[*pos]))) {
    identifier = str[(*pos)++];

    while (*pos < len && (str[*pos] == '_' || ::isalnum(str[*pos])))
      identifier += str[(*pos)++];

    return true;
  }
  else
    return false;
}

bool
CStrUtil::
skipIdentifier(const std::string &str, uint *pos)
{
  uint len = str.size();

  if (*pos < len && (str[*pos] == '_' || ::isalpha(str[*pos]))) {
    ++(*pos);

    while (*pos < len && (str[*pos] == '_' || ::isalnum(str[*pos])))
      ++(*pos);

    return true;
  }
  else
    return false;
}

bool
CStrUtil::
isCIdentifier(const std::string &str, uint pos)
{
  return isIdentifier(str, pos);
}

bool
CStrUtil::
readCIdentifier(const std::string &str, uint *pos, std::string &identifier)
{
  uint pos1 = *pos;

  if (! readIdentifier(str, &pos1, identifier))
    return false;

  *pos = pos1;

  return true;
}

bool
CStrUtil::
isCOperator(const std::string &str, uint pos)
{
  uint len = str.size();

  return (pos < len && isCOperatorChar(str[pos]));
}

bool
CStrUtil::
readCOperator(const std::string &str, uint *pos, std::string &opstr)
{
  uint len = str.size();

  opstr = "";

  /* Get Operator Characters */

  if (*pos < len) {
    switch (str[*pos]) {
      case '(':
      case ')':
      case '[':
      case ']':
      case '~':
      case ',':
      case '?':
      case ':':
        opstr += str[(*pos)++];

        break;
      case '=':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '!':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '+':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '+':
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '-':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '>':
            case '-':
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '*':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '/':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '%':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '&':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '&':
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '^':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '|':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '|':
            case '=':
              opstr += str[(*pos)++];

              break;
            default:
              break;
          }
        }

        break;
      case '<':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '=':
              opstr += str[(*pos)++];

              break;
            case '<':
              opstr += str[(*pos)++];

              if (*pos < len) {
                switch (str[*pos]) {
                  case '=':
                    opstr += str[(*pos)++];

                    break;
                  default:
                    break;
                }
              }

              break;
            default:
              break;
          }
        }

        break;
      case '>':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '=':
              opstr += str[(*pos)++];

              break;
            case '>':
              opstr += str[(*pos)++];

              if (*pos < len) {
                switch (str[*pos]) {
                  case '=':
                    opstr += str[(*pos)++];

                    break;
                  default:
                    break;
                }
              }

              break;
            default:
              break;
          }
        }

        break;
      case '.':
        opstr += str[(*pos)++];

        if (*pos < len) {
          switch (str[*pos]) {
            case '.':
              if (*pos < len) {
                switch (str[*pos + 1]) {
                  case '.':
                    opstr += str[(*pos)++];
                    opstr += str[(*pos)++];

                    break;
                  default:
                    break;
                }
              }

              break;
            default:
              break;
          }
        }

        break;
      default:
        break;
    }
  }

  if (opstr == "")
    return false;

  return true;
}

bool
CStrUtil::
isCOperatorChar(char c)
{
  return (strchr("()[]+-*/%<>=&|!~^.?:", c) != NULL);
}

bool
CStrUtil::
isCSeparator(const std::string &str, uint pos)
{
  uint len = str.size();

  return (pos < len && isCSeparatorChar(str[pos]));
}

bool
CStrUtil::
readCSeparator(const std::string &str, uint *pos, std::string &separator)
{
  uint len = str.size();

  separator = "";

  /* Get Separator Character */

  if (*pos < len) {
    switch (str[*pos]) {
      case '{':
      case '}':
      case ';':
      case ',':
        separator += str[(*pos)++];
        break;
      default:
       break;
    }
  }

  if (separator == "")
    return false;

  return true;
}

bool
CStrUtil::
isCSeparatorChar(char c)
{
  return (strchr("{};,", c) != NULL);
}

bool
CStrUtil::
replaceCTriGraphs(std::string &line)
{
  std::string line1;

  uint len = line.size();
  uint pos = 0;

  while (pos < len) {
    if (pos < len + 2 &&
        line[pos] == '?' && line[pos + 1] == '?' &&
        strchr("=/'()!<>-", line[pos + 2]) != NULL) {
      /* Replace Trigraph */

      if      (line[pos + 2] == '=')
        line1 += '#';
      else if (line[pos + 2] == '/')
        line1 += '\\';
      else if (line[pos + 2] == '\'')
        line1 += '^';
      else if (line[pos + 2] == '(')
        line1 += '[';
      else if (line[pos + 2] == ')')
        line1 += ']';
      else if (line[pos + 2] == '!')
        line1 += '|';
      else if (line[pos + 2] == '<')
        line1 += '{';
      else if (line[pos + 2] == '>')
        line1 += '}';
      else if (line[pos + 2] == '-')
        line1 += '~';

      pos += 2;
    }
    else
      line1 += line[pos++];
  }

  line = line1;

  return true;
}

bool
CStrUtil::
readNonSpace(const std::string &str, uint *pos, std::string &word)
{
  uint len = str.size();

  if (*pos >= len || ::isspace(str[*pos]))
    return false;

  word = str[(*pos)++];

  while (*pos < len && ! ::isspace(str[*pos]))
    word += str[(*pos)++];

  return true;
}

std::string
CStrUtil::
replaceEscapeCodes(const std::string &str)
{
  int len = str.size();

  bool has_escape = false;

  for (int i = 0; i < len - 1; ++i)
    if (str[i] == '\\') {
      has_escape = true;
      break;
    }

  if (! has_escape)
    return str;

  std::string str1;

  int i = 0;

  while (i < len - 1) {
    if (str[i] != '\\') {
      str1 += str[i++];
      continue;
    }

    ++i;

    switch (str[i]) {
      case 'a':
        str1 += '\a';
        break;
      case 'b':
        str1 += '\b';
        break;
      case 'e':
        str1 += '\033';
        break;
      case 'f':
        str1 += '\f';
        break;
      case 'n':
        str1 += '\n';
        break;
      case 'r':
        str1 += '\r';
        break;
      case 't':
        str1 += '\t';
        break;
      case 'v':
        str1 += '\v';
        break;
      case 'x':
        if (i < len - 1 && ::isxdigit(str[i + 1])) {
          int hex_value = 0;

          ++i;

          if      (::isdigit(str[i]))
            hex_value += (str[i] - '0');
          else if (::islower(str[i]))
            hex_value += (str[i] - 'a' + 10);
          else
            hex_value += (str[i] - 'A' + 10);

          if (i < len - 1 && ::isxdigit(str[i + 1])) {
            hex_value *= 16;

            ++i;

            if      (::isdigit(str[i]))
              hex_value += (str[i] - '0');
            else if (::islower(str[i]))
              hex_value += (str[i] - 'a' + 10);
            else
              hex_value += (str[i] - 'A' + 10);
          }

          str1 += hex_value;
        }
        else {
          str1 += '\\';
          str1 += str[i++];
        }

        break;
      case '\\':
        str1 += '\\';
        break;
      case '0':
        if (i < len - 1 && CStrUtil::isodigit(str[i + 1])) {
          int oct_value = 0;

          ++i;

          oct_value += (str[i] - '0');

          if (i < len - 1 && CStrUtil::isodigit(str[i + 1])) {
            oct_value *= 8;

            ++i;

            oct_value += (str[i] - '0');
          }

          if (i < len - 1 && CStrUtil::isodigit(str[i + 1])) {
            oct_value *= 8;

            ++i;

            oct_value += (str[i] - '0');
          }

          str1 += oct_value;
        }
        else {
          str1 += '\\';
          str1 += str[i++];
        }

        break;
      default:
        str1 += '\\';
        str1 += str[i++];
        break;
    }

    ++i;
  }

  if (i < len)
    str1 += str[i++];

  return str1;
}

bool
CStrUtil::
encodeEscapeChar(const std::string &str, char *c)
{
  *c = '\0';

  uint len = str.size();

  uint pos = 0;

  if (pos + 1 >= len || str[pos] != '\\')
    return false;

  ++pos;

  switch (str[pos]) {
    case 'a':
      *c = '\a';
      break;
    case 'b':
      *c = '\b';
      break;
    case 'e':
      *c = '\033';
      break;
    case 'f':
      *c = '\f';
      break;
    case 'n':
      *c = '\n';
      break;
    case 'r':
      *c = '\r';
      break;
    case 't':
      *c = '\t';
      break;
    case 'v':
      *c = '\v';
      break;
    case 'x':
      if (pos < len - 1 && ::isxdigit(str[pos + 1])) {
        int hex_value = 0;

        ++pos;

        if      (::isdigit(str[pos]))
          hex_value += (str[pos] - '0');
        else if (::islower(str[pos]))
          hex_value += (str[pos] - 'a' + 10);
        else
          hex_value += (str[pos] - 'A' + 10);

        if (pos < len - 1 && ::isxdigit(str[pos + 1])) {
          hex_value *= 16;

          ++pos;

          if      (::isdigit(str[pos]))
            hex_value += (str[pos] - '0');
          else if (::islower(str[pos]))
            hex_value += (str[pos] - 'a' + 10);
          else
            hex_value += (str[pos] - 'A' + 10);
        }

        *c = (char) hex_value;
      }
      else
        return false;

      break;
    case '\\':
      *c = '\\';
      break;
    case '0':
      if (pos < len - 1 && CStrUtil::isodigit(str[pos + 1])) {
        int oct_value = 0;

        ++pos;

        oct_value += (str[pos] - '0');

        if (pos < len - 1 && CStrUtil::isodigit(str[pos + 1])) {
          oct_value *= 8;

          ++pos;

          oct_value += (str[pos] - '0');
        }

        if (pos < len - 1 && CStrUtil::isodigit(str[pos + 1])) {
          oct_value *= 8;

          ++pos;

          oct_value += (str[pos] - '0');
        }

        *c = (char) oct_value;
      }
      else
        *c = '\0';

      break;
    default:
      return false;
  }

  ++pos;

  if (pos != len)
    return false;

  return true;
}

std::string
CStrUtil::
addEscapeChars(const std::string &str, const std::string &chars)
{
  std::string str1;

  uint len = str.size();

  for (uint i = 0; i < len; i++) {
    if (str[i] == '\\' || chars.find(str[i]) != std::string::npos)
      str1 += '\\';

    str1 += str[i];
  }

  return str1;
}

std::string
CStrUtil::
removeEscapeChars(const std::string &str)
{
  std::string str1;

  int len = str.size();

  int i = 0;

  while (i < len) {
    if (i < len - 1 && str[i] == '\\')
      ++i;

    str1 += str[i++];
  }

  return str1;
}

std::string
CStrUtil::
encodeCharString(char c)
{
  if      (c == '\b')
    return "\\b";
  else if (c == '\n')
    return "\\n";
  else if (c == '\t')
    return "\\t";
  else if (::isprint(c))
    return std::string("") + c;
  else
    return std::string("0") + CStrUtil::strprintf("%o", c);
}


std::string
CStrUtil::
insertEscapeCodes(const std::string &str)
{
  uint len = str.size();

  uint i = 0;

  for (i = 0; i < len; ++i)
    if (str[i] == '\\' || str[i] == '\"' || str[i] == '\'' ||
        (str[i] != ' ' && ! isgraph(str[i])))
      break;

  if (i >= len)
    return "";

  std::string str1;

  for (i = 0; i < len; ++i) {
    char c = str[i];

    if (c == ' ' || (c != '\\' && c != '\"' && c != '\'' && isgraph(c))) {
      str1 += c;

      continue;
    }

    str1 += '\\';

    switch (c) {
      case '\a':
        str1 += 'a';
        break;
      case '\b':
        str1 += 'b';
        break;
      case '\f':
        str1 += 'f';
        break;
      case '\n':
        str1 += 'n';
        break;
      case '\r':
        str1 += 'r';
        break;
      case '\t':
        str1 += 't';
        break;
      case '\v':
        str1 += 'v';
        break;
      case '\033':
        str1 += 'e';
        break;
      case '\"':
        str1 += '\"';
        break;
      case '\'':
        str1 += '\'';
        break;
      default: {
        int digit1 = c/64;
        int digit2 = (c - digit1*64)/8;
        int digit3 = c - digit1*64 - digit2*8;

        str1 += '0' + digit1;
        str1 += '0' + digit2;
        str1 += '0' + digit3;

        break;
      }
    }
  }

  return str1;
}

void
CStrUtil::
sort(std::vector<std::string> &strs)
{
  std::sort(strs.begin(), strs.end(), CStrCmpFunctor());
}

void
CStrUtil::
uniq(const std::vector<std::string> &strs, std::vector<std::string> &uniq_strs)
{
  std::vector<std::string>::const_iterator p1 = strs.begin();
  std::vector<std::string>::const_iterator p2 = strs.end  ();

  std::string last = "";

  if (p1 != p2) {
    last = *p1;

    uniq_strs.push_back(*p1);

    ++p1;
  }

  for ( ; p1 != p2; ++p1) {
    if (*p1 != last) {
      uniq_strs.push_back(*p1);

      last = *p1;
    }
  }
}

std::string
CStrUtil::
mostMatch(const std::vector<std::string> &strs)
{
  uint num_strs = strs.size();

  if (num_strs == 0)
    return "";

  if (num_strs == 1)
    return strs[0];

  uint len = strs[0].size();

  for (uint i = 0; i < len; i++)
    for (uint j = 1; j < num_strs; j++) {
      uint len1 = strs[j].size();

      if (i >= len1 || strs[0][i] != strs[j][i])
        return strs[0].substr(0, i);
    }

  return strs[0];
}

void
CStrUtil::
print(std::ostream &os, const std::vector<std::string> &strs)
{
  std::vector<std::string>::const_iterator p1 = strs.begin();
  std::vector<std::string>::const_iterator p2 = strs.end  ();

  bool first = true;

  for ( ; p1 != p2; ++p1) {
    if (! first)
      os << " ";

    os << *p1;

    first = false;
  }

  os << std::endl;
}

char *
CStrUtil::
strdup(const char *str)
{
  return strcpy(new char [strlen(str) + 1], str);
}

char *
CStrUtil::
strdup(const std::string &str)
{
  uint len = str.size();

  char *str1 = new char [len + 1];

  memcpy(str1, str.c_str(), len);

  str1[len] = '\0';

  return str1;
}

char *
CStrUtil::
strndup(const char *s, uint n)
{
  char *str1 = new char [n + 1];

  memcpy(str1, s, n);

  str1[n] = '\0';

  return str1;
}

char *
CStrUtil::
strstr(const char *str1, const char *str2)
{
  int len = strlen(str1);

  char *p1 = (char *) str1;
  char *p2 = (char *) &str1[len - 1];

  return strstr(p1, p2, str2, -1);
}

char *
CStrUtil::
strrstr(const char *str1, const char *str2)
{
  int len = strlen(str1);

  char *p1 = (char *) &str1[len - 1];
  char *p2 = (char *) str1;

  return strrstr(p1, p2, str2, -1);
}

char *
CStrUtil::
strstr(const char *p1, const char *p2, const char *str, int len)
{
  if (len < 0)
    len = strlen(str);

  if (len == 0)
    return 0;

  char c = str[0];

  char *ps = (char *) p1;
  char *pe = (char *) p2 - len + 1;

  char *p = strchr(ps, pe, c);

  while (p) {
    if (strncmp(p, str, len) == 0)
      return p;

    ++ps;

    if (ps > pe)
      return 0;

    p = strchr(ps, pe, c);
  }

  return 0;
}

char *
CStrUtil::
strrstr(const char *p1, const char *p2, const char *str, int len)
{
  if (len < 0)
    len = strlen(str);

  if (len == 0)
    return 0;

  char c = str[0];

  char *ps = (char *) p1 - len + 1;
  char *pe = (char *) p2;

  char *p = strrchr(ps, pe, c);

  while (p) {
    if (strncmp(p, str, len) == 0)
      return p;

    --ps;

    if (ps < pe)
      return 0;

    p = strrchr(ps, pe, c);
  }

  return 0;
}

char *
CStrUtil::
strchr(const char *str, char c)
{
  int len = strlen(str);

  char *p1 = (char *) str;
  char *p2 = (char *) &str[len - 1];

  return strchr(p1, p2, c);
}

char *
CStrUtil::
strrchr(const char *str, char c)
{
  int len = strlen(str);

  char *p1 = (char *) &str[len - 1];
  char *p2 = (char *) str;

  return strrchr(p1, p2, c);
}

char *
CStrUtil::
strchr(const char *p1, const char *p2, char c)
{
  for (const char *p = p1; p <= p2; ++p)
    if (*p == c)
      return (char *) p;

  return 0;
}

char *
CStrUtil::
strrchr(const char *p1, const char *p2, char c)
{
  for (const char *p = p1; p >= p2; --p)
    if (*p == c)
      return (char *) p;

  return 0;
}

void
CStrUtil::
addLines(const std::string &str, std::vector<std::string> &lines)
{
  uint len = str.size();

  std::string str1;
  std::string line;

  if (len > 0) {
    str1 = readLine(str, line);

    lines.push_back(line);
  }

  len = str1.size();

  while (len > 0) {
    str1 = readLine(str1, line);

    lines.push_back(line);

    len = str1.size();
  }
}

std::string
CStrUtil::
readLine(const std::string &str, std::string &line)
{
  uint len = str.size();

  line = "";

  uint i = 0;

  while (i < len) {
    if (str[i] == '\n')
      break;

    line += str[i++];
  }

  if (i < len && str[i] == '\n')
    ++i;

  return str.substr(i);
}

int
CStrUtil::
cmp(const std::string &str1, const std::string &str2)
{
  if      (str1 == str2) return 0;
  else if (str1 <  str2) return -1;
  else                   return  1;
}

int
CStrUtil::
casecmp(const std::string &str1, const std::string &str2)
{
  return cmp(CStrUtil::toLower(str1), CStrUtil::toLower(str2));
}

std::string::size_type
CStrUtil::
casefind(const std::string &str1, const std::string &str2)
{
  return CStrUtil::toLower(str1).find(CStrUtil::toLower(str2));
}

bool
CStrUtil::
equal(char *str1, char *str2)
{
  return (strcmp(str1, str2) == 0);
}

std::string
CStrUtil::
concatFileNames(const std::string &lhs, const std::string &rhs)
{
  int l2 = lhs.size();

  while (l2 > 0 && lhs[l2 - 1] == '/')
    l2--;

  int r1 = 0;
  int r2 = rhs.size();

  while (r1 < r2 && rhs[r1] == '/')
    ++r1;

  return lhs.substr(0, l2) + "/" + rhs.substr(r1, r2 - r1);
}

uint
CStrUtil::
maxLen(std::vector<std::string> &strs)
{
  uint len = 0;

  std::vector<std::string>::const_iterator p1 = strs.begin();
  std::vector<std::string>::const_iterator p2 = strs.end  ();

  for ( ; p1 != p2; ++p1) {
    uint len1 = (*p1).size();

    len = std::max(len, len1);
  }

  return len;
}

std::string
CStrUtil::
duplicate(const std::string &str, uint n)
{
  if (n <= 0)
    return "";

  std::string str1 = str;

  for ( ; n > 1; --n)
    str1 += str;

  return str1;
}

std::string
CStrUtil::
single_quote(const std::string &str)
{
  return "'" + str + "'";
}

std::string
CStrUtil::
double_quote(const std::string &str)
{
  return "\"" + str + "\"";
}

std::string
CStrUtil::
back_quote(const std::string &str)
{
  return "`" + str + "`";
}

std::string
CStrUtil::
charsToString(int c, ...)
{
  std::string str;

  va_list vargs;

  va_start(vargs, c);

  while (c != '\0') {
    str += (char) c;

    c = va_arg(vargs, int);
  }

  va_end(vargs);

  return str;
}

void
CStrUtil::
stringExpand(const std::string &str, std::vector<std::string> &ostrs)
{
  ostrs.push_back(str);

  uint count = 0;

  uint len = str.size();

  for (uint i = 0; i < len; ++i)
    if (str[i] == '%')
      ++count;

  if (count == 0)
    return;

  std::vector<std::string> istrs;

  for (uint i = 0; i < count; ++i) {
    istrs = ostrs;

    ostrs.clear();

    stringExpand1(istrs, ostrs);
  }
}

void
CStrUtil::
stringExpand1(const std::vector<std::string> &istrs, std::vector<std::string> &ostrs)
{
  uint num_strs = istrs.size();

  for (uint i = 0; i < num_strs; ++i) {
   const std::string &str = istrs[i];

    uint len = str.size();

    for (uint j = 0; j < len; ++j) {
      char c = str[j];

      if (c == '%') {
        ++j;

        if (j < len) {
          c = str[j];

          std::string lhs = str.substr(0, j - 1);

          if      (c == 'n') {
            std::string rhs = str.substr(j + 1);

            stringExpand2(lhs, rhs, "0123456789", ostrs);
          }
          else if (c == 'N') {
            std::string rhs = str.substr(j + 1);

            stringExpand2(lhs, rhs, "123456789", ostrs);
          }
          else if (c == 'a') {
            std::string rhs = str.substr(j + 1);

            stringExpand2(lhs, rhs, "abcdefghijklmnopqrstuvwxyz", ostrs);
          }
          else if (c == 'A') {
            std::string rhs = str.substr(j + 1);

            stringExpand2(lhs, rhs, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", ostrs);
          }
          else if (c == '[') {
            std::string chars;

            ++j;

            while (j < len && str[j] != ']')
              chars += str[j++];

            std::string rhs = str.substr(j + 1);

            stringExpand2(lhs, rhs, chars, ostrs);
          }
          else
            std::cerr << "Illegal format code %" << c << std::endl;
        }

        break;
      }
    }
  }
}

void
CStrUtil::
stringExpand2(const std::string &lhs, const std::string &rhs,
              const std::string &chars, std::vector<std::string> &strs)
{
  uint len = chars.size();

  for (uint i = 0; i < len; ++i)
    strs.push_back(lhs + chars[i] + rhs);
}

std::string
CStrUtil::
caseSepToUnderscoreSep(const std::string &str)
{
  int len = str.size();

  std::string str1;

  for (int i = 0; i < len; ++i) {
    if (i > 0 && ::isupper(str[i])) {
      str1 += "_";
      str1 += tolower(str[i]);
    }
    else
      str1 += str[i];
  }

  return str1;
}

std::string
CStrUtil::
underscoreSepToCaseSep(const std::string &str)
{
  int len = str.size();

  std::string str1;

  for (int i = 0; i < len; ++i) {
    if (i > 0 && i < len - 1 && str[i] == '_' &&
        (::islower(str[i + 1]) || ::isdigit(str[i + 1]))) {
      ++i;

      str1 += toupper(str[i]);
    }
    else
      str1 += str[i];
  }

  return str1;
}

//------------------

CStrUtil::IsCType
CStrUtil::
getIsCType(const std::string &is_type)
{
  if      (CStrUtil::casecmp(is_type, "alnum") == 0)
    return CStrUtil::isalnum;
  else if (CStrUtil::casecmp(is_type, "alpha") == 0)
    return CStrUtil::isalpha;
  else if (CStrUtil::casecmp(is_type, "cntrl") == 0)
    return CStrUtil::iscntrl;
  else if (CStrUtil::casecmp(is_type, "digit") == 0)
    return CStrUtil::isdigit;
  else if (CStrUtil::casecmp(is_type, "graph") == 0)
    return CStrUtil::isgraph;
  else if (CStrUtil::casecmp(is_type, "lower") == 0)
    return CStrUtil::islower;
  else if (CStrUtil::casecmp(is_type, "odigit") == 0)
    return CStrUtil::isodigit;
  else if (CStrUtil::casecmp(is_type, "print") == 0)
    return CStrUtil::isprint;
  else if (CStrUtil::casecmp(is_type, "punct") == 0)
    return CStrUtil::ispunct;
  else if (CStrUtil::casecmp(is_type, "space") == 0)
    return CStrUtil::isspace;
  else if (CStrUtil::casecmp(is_type, "upper") == 0)
    return CStrUtil::isupper;
  else if (CStrUtil::casecmp(is_type, "xdigit") == 0)
    return CStrUtil::isxdigit;
  else
    return NULL;
}

/* isalnum for machines which only have macro */

bool
CStrUtil::
isalnum(int c)
{
  return ::isalnum(c);
}

/* isalpha for machines which only have macro */

bool
CStrUtil::
isalpha(int c)
{
  return ::isalpha(c);
}


/* iscntrl for machines which only have macro */

bool
CStrUtil::
iscntrl(int c)
{
  return ::iscntrl(c);
}

/* isdigit for machines which only have macro */

bool
CStrUtil::
isdigit(int c)
{
  return ::isdigit(c);
}

/* isgraph for machines which only have macro */

bool
CStrUtil::
isgraph(int c)
{
  return ::isgraph(c);
}

/* islower for machines which only have macro */

bool
CStrUtil::
islower(int c)
{
  return ::islower(c);
}

/* isprint for machines which only have macro */

bool
CStrUtil::
isprint(int c)
{
  return ::isprint(c);
}

/* ispunct for machines which only have macro */

bool
CStrUtil::
ispunct(int c)
{
  return ::ispunct(c);
}

/* isspace for machines which only have macro */

bool
CStrUtil::
isspace(int c)
{
  return ::isspace(c);
}

/* isupper for machines which only have macro */

bool
CStrUtil::
isupper(int c)
{
  return ::isupper(c);
}

/* isxdigit for machines which only have macro */

bool
CStrUtil::
isxdigit(int c)
{
  return ::isxdigit(c);
}

/* isodigit for machines which only have macro */

bool
CStrUtil::
isodigit(int c)
{
  return (c >= '0' && c <= '7');
}

std::string
CStrUtil::
toEnglish(uint i)
{
  if (i <= 100) {
    switch (i) {
      case   0: return "zero";
      case   1: return "one";
      case   2: return "two";
      case   3: return "three";
      case   4: return "four";
      case   5: return "five";
      case   6: return "six";
      case   7: return "seven";
      case   8: return "eight";
      case   9: return "nine";
      case  10: return "ten";
      case  11: return "eleven";
      case  12: return "twelve";
      case  13: return "thirteen";
      case  14: return "fourteen";
      case  15: return "fifteen";
      case  16: return "sixteen";
      case  17: return "seventeen";
      case  18: return "eighteen";
      case  19: return "nineteen";
      case  20: return "twenty";
      case  30: return "thirty";
      case  40: return "fourty";
      case  50: return "fifty";
      case  60: return "sixty";
      case  70: return "seventy";
      case  80: return "eighty";
      case  90: return "ninety";
      case 100: return "one hundred";
      default: {
        int tens = i/10;

        return toEnglish(10*tens) + " " + toEnglish(i - 10*tens);
      }
    }
  }

  if (i < 1000) {
    int hundreds = i/100;
    int units    = i - 100*hundreds;

    if (units > 0)
      return toEnglish(hundreds) + " hundred and " + toEnglish(units);
    else
      return toEnglish(hundreds) + " hundred";
  }

  if (i < 1000000) {
    int thousands = i/1000;
    int units     = i - 1000*thousands;

    if (units > 0)
      return toEnglish(thousands) + " thousand " + toEnglish(units);
    else
      return toEnglish(thousands) + " thousand";
  }

  int millions = i/1000000;
  int units    = i - 1000000*millions;

  if (units > 0)
    return toEnglish(millions) + " million " + toEnglish(units);
  else
    return toEnglish(millions) + " million";
}

//---------

static void
subPermute(char *src, uint len, char *dst, uint pos, uint n)
{
  for (uint i = 0; i < len; ++i) {
    if (src[i] == '\0') continue;

    std::swap(dst[pos], src[i]);

    if (pos + 1 < n)
      subPermute(src, len, dst, pos + 1, n);
    else
      std::cerr << &dst[0] << std::endl;

    std::swap(dst[pos], src[i]);
  }
}

void
CStrUtil::
permute(const std::string &word, uint n)
{
  uint len = word.size();

  std::vector<char> src(word.begin(), word.end());

  std::vector<char> dst;

  dst.resize(n, '\0');

  // for each position (0 to n-1) select each word char in turn

  subPermute(&src[0], len, &dst[0], 0, n);
}

//---------

void
CStrUtil::
printf(const char *format, ...)
{
  va_list vargs;

  va_start(vargs, format);

  vfprintf(std::cout, format, &vargs);

  va_end(vargs);
}

void
CStrUtil::
eprintf(const char *format, ...)
{
  va_list vargs;

  va_start(vargs, format);

  vfprintf(std::cerr, format, &vargs);

  va_end(vargs);
}

void
CStrUtil::
fprintf(std::ostream &os, const char *format, ...)
{
  va_list vargs;

  va_start(vargs, format);

  vfprintf(os, format, &vargs);

  va_end(vargs);
}

void
CStrUtil::
sprintf(std::string &str, const char *format, ...)
{
  va_list vargs;

  va_start(vargs, format);

  vsprintf(str, format, &vargs);

  va_end(vargs);
}

std::string
CStrUtil::
strprintf(const std::string *format, ...)
{
  std::string str;

  va_list vargs;

  va_start(vargs, format);

  vsprintf(str, format->c_str(), &vargs);

  va_end(vargs);

  return str;
}

std::string
CStrUtil::
strprintf(const char *format, ...)
{
  std::string str;

  va_list vargs;

  va_start(vargs, format);

  vsprintf(str, format, &vargs);

  va_end(vargs);

  return str;
}

void
CStrUtil::
vprintf(const char *format, va_list *vargs)
{
  vfprintf(std::cout, format, vargs);
}

void
CStrUtil::
veprintf(const char *format, va_list *vargs)
{
  vfprintf(std::cerr, format, vargs);
}

void
CStrUtil::
vfprintf(std::ostream &os, const char *format, va_list *vargs)
{
  std::string str;

  vsprintf(str, format, vargs);

  os << str;
}

void
CStrUtil::
vsprintf(std::string &str, const char *format, va_list *vargs)
{
  
}

std::string
CStrUtil::
vstrprintf(const char *format, va_list *vargs)
{
  std::string str;

  vsprintf(str, format, vargs);

  return str;
}

bool
CStrUtil::
readFormat(const std::string &str, uint *pos, std::string &format,
           int *field_width, int *precision, char *length_modifier,
           char *format_code, int *flags)
{
  uint save_pos = *pos;

  uint len = str.size();

  format = "";

  *flags = 0;

  /* Required '%' */

  if (*pos >= len || str[*pos] != '%') {
    *pos = save_pos;
    return false;
  }

  format += str[(*pos)++];

  /*------*/

  /* Optional '-+ #0' chars (multiples valid ?) */

  while (*pos < len && strchr("-+ #0", str[*pos]) != NULL) {
    if      (str[*pos] == '-')
      *flags |= CPRINTF_LEFT_JUSTIFY;
    else if (str[*pos] == '+')
      *flags |= CPRINTF_DISPLAY_SIGN;
    else if (str[*pos] == ' ')
      *flags |= CPRINTF_PAD_POSITIVE;
    else if (str[*pos] == '#')
      *flags |= CPRINTF_USE_ALTERNATE;
    else if (str[*pos] == '0')
      *flags |= CPRINTF_ZERO_PAD;

    format += str[(*pos)++];
  }

  /*------*/

  /* optional field width */

  *field_width = -1;

  if (*pos < len && str[*pos] == '*') {
    *flags |= CPRINTF_FIELD_WIDTH_AS_VALUE;

    format += str[(*pos)++];
  }
  else {
    std::string field_width_str;

    while (*pos < len && isdigit(str[*pos]))
      field_width_str += str[(*pos)++];

    *field_width = atoi(field_width_str.c_str());

    format += field_width_str;
  }

  /*------*/

  /* optional precision */

  *precision = -1;

  if (*pos < len && str[*pos] == '.') {
    format = str[(*pos)++];

    /* optional precision value */

    if (*pos < len && str[*pos] == '*') {
      *flags |= CPRINTF_PRECISION_AS_VALUE;

      format = str[(*pos)++];
    }
    else {
      std::string precision_str;

      while (*pos < len && isdigit(str[*pos]))
        precision_str += str[(*pos)++];

      *precision = atoi(precision_str.c_str());

      format += precision_str;
    }
  }

  /*------*/

  /* optional length modifier */

  if (*pos < len &&
      (str[*pos] == 'h' || str[*pos] == 'l' ||  str[*pos] == 'L')) {
    *length_modifier = str[(*pos)++];

    format += *length_modifier;
  }

  /*------*/

  /* Required format code */

  if (*pos >= len) {
    *pos = save_pos;
    return false;
  }

  *format_code = str[(*pos)++];

  format += format_code;

  return true;
}

bool
CStrUtil::
readRealFormat(const std::string &str, uint *pos, std::string &format)
{
  int  flags;
  char format_code;
  char length_modifier;
  int  field_width, precision;

  if (! readFormat(str, pos, format, &field_width, &precision, &length_modifier,
                   &format_code, &flags))
    return false;

  if (strchr("feEgG", format_code) == NULL)
    return false;

  return true;
}

bool
CStrUtil::
readIntegerFormat(const std::string &str, uint *pos, std::string &format)
{
  int  flags;
  char format_code;
  char length_modifier;
  int  field_width, precision;

  if (! readFormat(str, pos, format, &field_width, &precision, &length_modifier,
                   &format_code, &flags))
    return false;

  if (strchr("diouxXc", format_code) == NULL)
    return false;

  return true;
}

bool
CStrUtil::
readStringFormat(const std::string &str, uint *pos, std::string &format)
{
  int  flags;
  char format_code;
  char length_modifier;
  int  field_width, precision;

  if (! readFormat(str, pos, format, &field_width, &precision, &length_modifier,
                   &format_code, &flags))
    return false;

  if (format_code != 's')
    return false;

  return true;
}

//---------

bool
CWordDef::
isWordChar(char c) const
{
  return ! isSpace(c);
}

bool
CWordDef::
isSpace(char c) const
{
  return ::isspace(c);
}

bool
CWordDef::
isStartGroupI(char c) const
{
  if (isStartGroup(c)) {
    CWordDef *th = const_cast<CWordDef *>(this);

    th->group_char = c;

    return true;
  }

  return false;
}

bool
CWordDef::
isEndGroupI(char c) const
{
  if (isEndGroup(c)) {
    CWordDef *th = const_cast<CWordDef *>(this);

    th->group_char = '\0';

    return true;
  }

  return false;
}

bool
CWordDef::
isStartGroup(char c) const
{
  if (c == '\'' || c == '\"')
    return true;

  return false;
}

bool
CWordDef::
isEndGroup(char c) const
{
  if ((c == '\'' && group_char == '\'') ||
      (c == '\"' && group_char == '\"'))
    return true;

  return false;
}

//---------

long
CStrWord::
toInteger() const
{
  return CStrUtil::toInteger(word_);
}

double
CStrWord::
toReal() const
{
  return CStrUtil::toReal(word_);
}

//---------

void
CStrWords::
truncate(int start, int end)
{
  std::vector<CStrWord> word_datas1;

  int delta = word_datas_[start].getStartPos();

  for (int i = start; i <= end; i++) {
    word_datas_[i].shift(-delta);

    word_datas1.push_back(word_datas_[i]);
  }

  word_datas_ = word_datas1;

  str_ = CStrUtil::toString(*this, " ");
}

void
CStrWords::
truncateWord(int pos, int start, int end)
{
  int new_size = end - start + 1;

  int delta = new_size - word_datas_[pos].size();

  word_datas_[pos].truncate(start, end);

  for (uint i = pos + 1; i < word_datas_.size(); i++)
    word_datas_[i].shift(delta);

  str_ = CStrUtil::toString(*this, " ");
}
