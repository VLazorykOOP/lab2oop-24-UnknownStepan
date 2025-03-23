#include <bitset>
#include <iostream>
using namespace std;
namespace encode {
char shif_left(char a, int i) { return (a << i) | (a >> (8 - i)); }
char shif_right(char a, int i) {
  unsigned char b = a;
  b = b >> i;
  b |= a << (8 - i);
  return b;
}
void console_to_array(char *a, int size) {
  cout << "array" << endl;
  for (int i = 0; i < size; i++) {
    cin >> a[i];
  }
}
void shuffle(char *a, int flag, int size) {
  int shift = 0;
  cout << "shift" << endl;
  cin >> shift;

  for (int i = 0; i < size; i++) {
    if (flag == 0) {
      cout << shif_left(a[i], shift);
      a[i] = shif_left(a[i], shift);
    } else {
      cout << shif_right(a[i], shift);
      a[i] = shif_right(a[i], shift);
      cout << bitset<8>(a[i]) << endl;
    }
  }
}
void array_to_console(char *a, int size) {
  for (int i = 0; i < size; i++) {
    cout << bitset<8>(a[i]) << endl;
    cout << "a[i]= " << a[i] << endl;
  }
}
int run() {
  int size = 0;
  cout << "size" << endl;
  cin >> size;

  char a[size];
  console_to_array(a, size);
  int flag = 0;
  char ch = '0';
  do {
    system("clear");
    cout << "1 - crypt \n2 - decrypt \n3 - console to array \n0 - exit\n";
    cin >> ch;
    switch (ch) {
    case '0':
      break;
    case '1':
      shuffle(a, 0, size);

      break;

    case '2':
      shuffle(a, 1, size);
      break;
    case '3':
      array_to_console(a, size);
      break;
    }
    cin.get();
    cin.get();
  } while (ch != '0');
  return 0;
}
} // namespace encode
