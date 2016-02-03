#include "CBigInt.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>

typedef unsigned long         IResult;
typedef std::map<int,IResult> IMap;
typedef std::map<int,CBigInt> BigMap;

IMap   fibICache;
BigMap fibBigCache;

IResult fib(int n) {
  if (n <= 0) return 0;
  if (n <= 1) return 1;

  auto p = fibICache.find(n);

  if (p == fibICache.end()) {
    IResult res = fib(n - 2) + fib(n - 1);

    p = fibICache.insert(p, IMap::value_type(n, res));
  }

  return (*p).second;
}

CBigInt fibBig(int n) {
  if (n <= 0) return CBigIntC::Zero;
  if (n <= 1) return CBigIntC::One;

  auto p = fibBigCache.find(n);

  if (p == fibBigCache.end()) {
    CBigInt res = fibBig(n - 2) + fibBig(n - 1);

    p = fibBigCache.insert(p, BigMap::value_type(n, res));
  }

  return (*p).second;
}

int
main(int argc, char **argv)
{
  if (argc <= 1)
    exit(1);

  int n = atoi(argv[1]);

  std::cerr << fib(n) << std::endl;

  std::cerr << fibBig(n) << std::endl;

  return 0;
}
