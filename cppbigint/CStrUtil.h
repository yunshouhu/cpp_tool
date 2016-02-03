#ifndef CSTRUTIL_H
#define CSTRUTIL_H

#define _CRT_SECURE_NO_DEPRECATE

#include <vector>
#include <string>
#include <cstdarg>
#include <sys/types.h>
//#define uint unsigned  int 
//#define ulong unsigned  long 

typedef unsigned int uint;
typedef unsigned long ulong;

class CRegExp;

enum CPrintFFlags {
  CPRINTF_LEFT_JUSTIFY         = (1<<0),
  CPRINTF_DISPLAY_SIGN         = (1<<1),
  CPRINTF_PAD_POSITIVE         = (1<<2),
  CPRINTF_USE_ALTERNATE        = (1<<3),
  CPRINTF_ZERO_PAD             = (1<<4),
  CPRINTF_FIELD_WIDTH_AS_VALUE = (1<<5),
  CPRINTF_PRECISION_AS_VALUE   = (1<<6)
};

class CStrCmp;
class CStrWord;
class CStrWords;

class CStrCmpFunctor {
 public:
  int operator()(const std::string &str1, const std::string &str2) {
    return str1 < str2;
  }
};

class CWordDef {
 protected:
  int  group_char;
  char escape_char_;
  bool allow_escapes_;

 public:
  CWordDef() :
   group_char(0), escape_char_('\\'), allow_escapes_(true) {
  }

  virtual ~CWordDef() { }

  bool getEscapeChar  () const { return escape_char_  ; }
  bool getAllowEscapes() const { return allow_escapes_; }

  virtual bool isWordChar(char c) const;
  virtual bool isSpace(char c) const;
  virtual bool isStartGroup(char c) const;
  virtual bool isEndGroup(char c) const;

  bool isStartGroupI(char c) const;
  bool isEndGroupI  (char c) const;
};

namespace CStrUtil {
  std::string toString(const char *str);
  std::string toString(const std::string &str);

  std::string toString(char c);
  std::string toString(bool flag);
  std::string toString(int integer);
  std::string toString(uint integer);
  std::string toString(long integer);
  std::string toString(ulong integer);
  std::string toString(double real);
  std::string toString(const std::vector<std::string> &words,
                       const std::string &sep="");
  std::string toString(const std::vector<std::string> &words,
                       int start, int end=-1, const std::string &sep="");
  std::string toString(const char **words, uint num_words,
                       int start, int end=-1, const std::string &sep="");
  std::string toString(const char **words, uint num_words,
                       const std::string &sep="");
  std::string toString(std::vector<std::string>::const_iterator pstr1,
                       std::vector<std::string>::const_iterator pstr2,
                       const std::string &sep="");
  std::string toString(const CStrWords &words, const std::string &sep="");

  bool decodeHexString(const std::string &str, uint *value);
  bool decodeHexChar(unsigned char c, uint *value);

  void setHexUpper(bool upper);

  std::string toHexString(uint integer, uint width=4);
  std::string toHexString(signed int integer, uint width=4);

  std::string toOctString(int integer);
  std::string toOctStringInWidth(int integer, uint width=4);

  std::string toBitString(int c);

  bool isBool(const std::string &str);
  bool toBool(const std::string &str);
  bool toBool(const std::string &str, bool *value);

  bool isBaseInteger(const std::string &str, uint base);
  long toBaseInteger(const std::string &str, uint base);
  bool toBaseInteger(const std::string &str, uint base, int *integer);
  bool toBaseInteger(const std::string &str, uint base, uint *integer);
  bool toBaseInteger(const std::string &str, uint base, long *integer);

  bool isInteger(const std::string &str);
  long toInteger(const std::string &str);
  bool toInteger(const std::string &str, short *integer);
  bool toInteger(const std::string &str, int *integer);
  bool toInteger(const std::string &str, uint *integer);
  bool toInteger(const std::string &str, long *integer);

  bool   isReal(const std::string &str);
  double toReal(const std::string &str);
  bool   toReal(const std::string &str, double *real);

  bool isBaseChar(int c, uint base, int *value = NULL);

  bool isCComment(const std::string &str, uint pos);
  bool readCComment(const std::string &str, uint *pos,
                    bool *in_comment, std::string &comment);

  bool isCNumber(const std::string &str, uint pos);
  bool readCNumber(const std::string &str, uint *pos, std::string &number);

  bool isCCharacter(const std::string &str, uint pos);
  bool readCCharacter(const std::string &str, uint *pos, std::string &number);

  bool isCString(const std::string &str, uint pos);
  bool readCString(const std::string &str, uint *pos, std::string &number);

  std::string stripSpaces(const std::string &str,
                          bool front=true, bool back=true);

  char *stripSpaces(char *str, bool front=true, bool back=true);

  const char *stripSpaces(const char *str, bool front=true, bool back=true);

  std::string compressSpaces(const std::string &str);

  std::string   toUpper(const std::string &str);
  char         *toUpper(char *str);
  const char   *toUpper(const char *str);
  std::string   toLower(const std::string &str);
  char         *toLower(char *str);
  const char   *toLower(const char *str);

  std::string capitalize(const std::string &str);

#if 0
  int gregsub(const std::string &istr, const CRegExp &pattern,
              const std::string &rstr, std::string &ostr);
  bool regsub(const std::string &istr, const CRegExp &pattern,
              const std::string &rstr, std::string &ostr);
#endif

  std::string replace(const std::string &str, const std::string &old_str,
                      const std::string &new_str);

  std::string translate(const std::string &str,
                        const std::string &old_chars,
                        const std::string &new_chars, bool remove=false);

  void addFields(const std::string &str, std::vector<std::string> &words,
                 const std::string &splitters="", bool skipEmpty=false);
  bool skipSpace(const char *str, uint *pos);
  bool skipSpace(const char **str);
  bool skipSpace(char **str);
  bool skipSpace(const std::string &str, int *pos);
  bool skipSpace(const std::string &str, uint *pos);

  bool skipNonSpace(const char *str, uint *pos);
  bool skipNonSpace(const char **str);
  bool skipNonSpace(char **str);
  bool skipNonSpace(const std::string &str, int *pos);
  bool skipNonSpace(const std::string &str, uint *pos);

  bool skipDoubleQuotedString(const std::string &str, uint *pos);
  bool skipSingleQuotedString(const std::string &str, uint *pos);
  bool skipBackQuotedString  (const std::string &str, uint *pos);

  bool readInteger(const std::string &str, uint *pos, int *integer);
  bool readInteger(const char *str, uint *pos, int *integer);

  bool readBaseInteger(const std::string &str, uint base,
                       uint *pos, int *integer);
  bool readBaseInteger(const char *str, uint base,
                       uint *pos, int *integer);

  bool skipInteger(const std::string &str, uint *pos);
  bool skipInteger(const char *str, uint *pos);

  bool skipBaseInteger(const std::string &str, uint base, uint *pos);
  bool skipBaseInteger(const char *str, uint base, uint *pos);

  bool readReal(const std::string &str, uint *pos, double *real);
  bool readReal(const char *str, uint *pos, double *real);

  bool readNumber(const std::string &str, uint *pos, double &real, int &integer, bool &is_real);

  void fput(const std::string &str, FILE *fp);

  bool isIdentifier(const std::string &str);
  bool isIdentifier(const std::string &str, uint pos);
  bool readIdentifier(const std::string &str, uint *pos,
                      std::string &identifier);
  bool skipIdentifier(const std::string &str, uint *pos);

  bool isCIdentifier(const std::string &str, uint pos);
  bool readCIdentifier(const std::string &str, uint *pos,
                              std::string &identifier);

  bool isCOperator(const std::string &str, uint pos);
  bool readCOperator(const std::string &str, uint *pos, std::string &opstr);
  bool isCOperatorChar(char c);

  bool isCSeparator(const std::string &str, uint pos);
  bool readCSeparator(const std::string &str, uint *pos, std::string &opstr);
  bool isCSeparatorChar(char c);

  bool replaceCTriGraphs(std::string &str);

  bool readNonSpace(const std::string &str, uint *pos, std::string &word);

  std::string replaceEscapeCodes(const std::string &str);

  std::string addEscapeChars(const std::string &str, const std::string &chars);
  std::string removeEscapeChars(const std::string &str);

  bool encodeEscapeChar(const std::string &str, char *c);

  std::string encodeCharString(char c);

  std::string insertEscapeCodes(const std::string &str);

  void sort(std::vector<std::string> &strs);
  void uniq(const std::vector<std::string> &strs,
            std::vector<std::string> &uniq_strs);

  std::string mostMatch(const std::vector<std::string> &strs);

  void print(std::ostream &os, const std::vector<std::string> &strs);

  void        printf(const char *format, ...);
  void        eprintf(const char *format, ...);
  void        fprintf(std::ostream &os, const char *format, ...);
  void        sprintf(std::string &str, const char *format, ...);
  std::string strprintf(const std::string *format, ...);
  std::string strprintf(const char *format, ...);

  void        vprintf(const char *format, va_list *vargs);
  void        veprintf(const char *format, va_list *vargs);
  void        vfprintf(std::ostream &os, const char *format, va_list *vargs);
  void        vsprintf(std::string &str, const char *format, va_list *vargs);
  std::string vstrprintf(const char *format, va_list *vargs);

  bool readFormat(const std::string &str, uint *pos, std::string &format,
                  int *field_width, int *precision,
                  char *length_modifier, char *format_code, int *flags);
  bool readRealFormat(const std::string &str, uint *pos, std::string &format);
  bool readIntegerFormat(const std::string &str, uint *pos,
                         std::string &format);
  bool readStringFormat(const std::string &str, uint *pos,
                        std::string &format);

  char *strdup(const char *str);
  char *strdup(const std::string &str);
  char *strndup(const char *s, uint n);

  char *strstr(const char *str1, const char *str2);
  char *strstr(const char *p1, const char *p2, const char *str2, int len=-1);

  char *strrstr(const char *str1, const char *str2);
  char *strrstr(const char *p1, const char *p2, const char *str2, int len=-1);

  char *strchr(const char *str, char c);
  char *strchr(const char *p1, const char *p2, char c);

  char *strrchr(const char *str, char c);
  char *strrchr(const char *p1, const char *p2, char c);

  void addLines(const std::string &str, std::vector<std::string> &lines);

  std::string readLine(const std::string &str, std::string &line);

  int cmp(const std::string &str1, const std::string &str2);

  int casecmp(const std::string &str1, const std::string &str2);

  std::string::size_type casefind(const std::string &str1, const std::string &str2);

  bool equal(char *str1, char *str2);

  std::string concatFileNames(const std::string &lhs,
                              const std::string &rhs);

  uint maxLen(std::vector<std::string> &words);

  std::string duplicate(const std::string &str, uint n);

  std::string single_quote(const std::string &str);
  std::string double_quote(const std::string &str);
  std::string back_quote(const std::string &str);

  std::string charsToString(int c, ...);

  void stringExpand(const std::string &str, std::vector<std::string> &ostrs);

  void stringExpand1(const std::vector<std::string> &istrs,
                     std::vector<std::string> &ostrs);
  void stringExpand2(const std::string &lhs, const std::string &rhs,
                     const std::string &chars,
                     std::vector<std::string> &strs);

  std::string caseSepToUnderscoreSep(const std::string &str);
  std::string underscoreSepToCaseSep(const std::string &str);

  typedef bool (*IsCType)(int c);

  IsCType getIsCType(const std::string &is_type);

  bool isalnum (int c);
  bool isalpha (int c);
  bool iscntrl (int c);
  bool isdigit (int c);
  bool isgraph (int c);
  bool islower (int c);
  bool isprint (int c);
  bool ispunct (int c);
  bool isspace (int c);
  bool isupper (int c);
  bool isxdigit(int c);
  bool isodigit(int c);

  std::string toEnglish(uint i);

  void permute(const std::string &word, uint n);
}

class CStrCharPos {
 private:
  char c_;
  int  pos_;

 public:
  CStrCharPos(char c, int pos) : c_(c), pos_(pos) { }

  char getChar() const { return c_; }
  int  getPos () const { return pos_; }

  void shift(int delta) { pos_ += delta; }
};

class CStrWord {
 private:
  typedef std::vector<CStrCharPos> PosList;

  std::string word_;
  int         pos_;
  char        start_group_;
  char        end_group_;
  PosList     escape_chars_;

 public:
  CStrWord(const std::string &word=std::string(""), int pos=0) :
   word_(word), pos_(pos), start_group_('\0'), end_group_('\0'), escape_chars_() {
  }

  const std::string &getWord() const { return word_; }

  int getStartPos() const { return pos_; }
  int getEndPos  () const { return pos_ + word_.size() - 1; }

  char getStartGroup() const { return start_group_; }
  char getEndGroup  () const { return end_group_  ; }

  int getNumEscapeChars() const { return escape_chars_.size(); }

  const CStrCharPos &getEscapeChar(int i) const { return escape_chars_[i]; }

  long   toInteger() const;
  double toReal   () const;

  int size() const { return word_.size(); }

  const char *c_str() const { return word_.c_str(); }

  void truncate(int start, int end) {
    std::vector<CStrCharPos> escape_chars1;

    for (uint i = 0; i < escape_chars_.size(); i++) {
      if (escape_chars_[i].getPos() >= start ||
          escape_chars_[i].getPos() <= end) {
        escape_chars_[i].shift(-start);

        escape_chars1.push_back(escape_chars_[i]);
      }
    }

    escape_chars_ = escape_chars1;

    word_ = word_.substr(start, end - start + 1);
  }

  void shift(int delta) {
    pos_ +=  delta;

    for (uint i = 0; i < escape_chars_.size(); i++)
      escape_chars_[i].shift(delta);
  }

  int operator==(const std::string &str) const { return word_ == str; }
  int operator==(const char *str) const { return word_ == str; }

  void setStartGroup(char c) { start_group_ = c; }
  void setEndGroup  (char c) { end_group_   = c; }

  void addEscapeChar(char c, int pos) {
    escape_chars_.push_back(CStrCharPos(c, pos));
  }

  void setWord(const std::string &word, int pos) {
    word_ = word;
    pos_  = pos;
  }
};

class CStrWords {
 private:
  std::string           str_;
  std::vector<CStrWord> word_datas_;

 public:
  typedef std::vector<CStrWord>::iterator iterator;
  typedef std::vector<CStrWord>::const_iterator const_iterator;

  CStrWords(const std::string &str) : str_(str), word_datas_() { }

 ~CStrWords() { }

  int size() const { return word_datas_.size(); }

  void addWord(const std::string &word, int start_pos) {
    CStrWord word_data(word, start_pos);

    word_datas_.push_back(word_data);
  }

  void addWord(const CStrWord &word) {
    word_datas_.push_back(word);
  }

  const CStrWord &getWord(int pos) const {
    if (pos < 0 || pos > size())
      throw "Invalid Subscript";

    return word_datas_[pos];
  }

  void truncate(int start, int end);

  void truncateWord(int pos, int start, int end);

  iterator begin() { return word_datas_.begin(); }
  iterator end  () { return word_datas_.end  (); }

  const_iterator begin() const { return word_datas_.begin(); }
  const_iterator end  () const { return word_datas_.end  (); }

  const CStrWord &operator[](int pos) const {
    return getWord(pos);
  }
};

#endif
