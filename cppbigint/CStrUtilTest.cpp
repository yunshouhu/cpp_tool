#include "CStrUtil.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

int
main(int argc, char **argv)
{
  string istring = CStrUtil::toString(45);

  cout << istring << endl;

  string rstring = CStrUtil::toString(3.563);

  cout << rstring << endl;

  cout << CStrUtil::toInteger(istring) << endl;

  cout << CStrUtil::toReal(rstring) << endl;

  cout << "'" << CStrUtil::stripSpaces("fred")                    <<
          "'" << endl;
  cout << "'" << CStrUtil::stripSpaces("  fred")                  <<
          "'" << endl;
  cout << "'" << CStrUtil::stripSpaces("fred  ")                  <<
          "'" << endl;
  cout << "'" << CStrUtil::stripSpaces(" fred    ")               <<
          "'" << endl;
  cout << "'" << CStrUtil::stripSpaces(" fred    ", true, false)  <<
          "'" << endl;
  cout << "'" << CStrUtil::stripSpaces(" fred    ", false, true)  <<
          "'" << endl;
  cout << "'" << CStrUtil::stripSpaces(" fred    ", false, false) <<
          "'" << endl;

  cout << CStrUtil::toLower   ("heLLo") << endl;
  cout << CStrUtil::toUpper   ("heLLo") << endl;
  cout << CStrUtil::capitalize("heLLo") << endl;

  cout << CStrUtil::translate("1234", "0123456789", "1234567890") << endl;
  cout << CStrUtil::translate("a2aa2a", "a", "", true) << endl;


  int n = 1;

  for (int i = 0; i < 10; ++i) {
    cout << CStrUtil::toOctStringInWidth(n, 3);

    n *= 2;
  }

  cout << endl;
}
