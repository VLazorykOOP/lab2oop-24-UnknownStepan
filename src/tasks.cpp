#include "tasks.h"
#include "crypt.h"
#include "encode.h"
#include "math.h"
void task1() {
  cout << " Calculation of expressions using bitwise operations  \n";
  cout << "enter the input a,b,c,d" << endl;
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  cout << "the result is "
       << multiply(33, b) + divide(multiply(d, 15) + multiply(12, a), 512) -
              multiply(65, c) + multiply(d, 14)
       << endl;
  cout << 33 * b + ((d * 15 + 12 * a) / 512) - 65 * c + d * 14 << endl;
}
void task2() { cryptprog::run(); }
void task3() { encode::run(); }
