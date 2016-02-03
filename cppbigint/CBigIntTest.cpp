#include "CBigInt.h"

using std::cout;
using std::endl;

//https://github.com/colinw7/CBigInt
int main(int argc, char **argv)
{
  if (argc != 3) {
    std::cerr << "Usage: CBigIntTest a b" << std::endl;
    exit(1);
  }

  CBigInt a(argv[1]);
  CBigInt b(argv[2]);

  CBigInt c = a + b;
  CBigInt d = a - b;
  CBigInt e = a * b;
  CBigInt f = a / b;
  CBigInt g = a % b;

  cout << a << " + " << b << " = " << c << endl;
  cout << a << " - " << b << " = " << d << endl;
  cout << a << " * " << b << " = " << e << endl;
  cout << a << " / " << b << " = " << f << endl;
  cout << a << " % " << b << " = " << g << endl;

  cout << a << " >  " << b << " = " << (a >  b) << endl;
  cout << a << " <  " << b << " = " << (a <  b) << endl;
  cout << a << " >= " << b << " = " << (a >= b) << endl;
  cout << a << " <= " << b << " = " << (a <= b) << endl;
  cout << a << " == " << b << " = " << (a == b) << endl;

  CBigInt p1 = 2;
  CBigInt p2 = 64;

  CBigInt pp = p1.power(p2);

  cout << p1 << " ** " << p2 << " = " << pp << endl;

  CBigInt fi = 50;

  CBigInt fo = fi.factorial();

  cout << fi << "! = " << fo << endl;

  return 0;
}
