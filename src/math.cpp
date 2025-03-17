#include "math.h"
#include <iostream>

int multiply(int a, int b) {
  // bitwise
  int result = 0;
  bool is_Negative = false;
  is_Negative = (((a < 0) and (b < 0)) or ((a > 0) and (b > 0))) ? false : true;
  a = (a < 0) ? -a : a;
  b = (b < 0) ? -b : b;
  while (b != 0) {
    if (b & 1) {
      result += a;
    }
    a <<= 1;
    b >>= 1;
  }
  if (is_Negative) {
    result = -result;
  }
  return result;
}
int divide(int a, int b) {
  // bitwise
  if (b == 0) {
    return 0;
  }
  int result = 0;
  int sign = ((a < 0) and (b < 0)) or ((a > 0) and (b > 0)) ? 1 : -1;
  unsigned int a_de = (a < 0) ? -a : a;
  unsigned int b_do = (b < 0) ? -b : b;
  while (a_de >= b_do) {
    int temp = b_do;
    int multiplier = 1;
    while ((temp << 1) <= a_de) {
      temp <<= 1;
      multiplier <<= 1;
    }
    a_de -= temp;
    result += multiplier;
  }
  return result * sign;
}
