#include "fns-compare.hh"
#include <iostream>

static double
linear(double n)
{
  enum { C = 10000 };
  return C*n;
}

static const bool isRegistered =
  register_fn(FnInfo("linear", linear));
