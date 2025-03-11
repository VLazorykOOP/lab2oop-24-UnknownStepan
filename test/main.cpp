#include <bitset>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

// read from file and split each character in list

char a[128];
unsigned short data_is[128];
int read() {
  FILE *f = fopen("test.txt", "r");
  fread(a, sizeof(char), 128, f);
  fclose(f);
  return 0;
}
// write in binary file array
void write(unsigned short *a) {
  ofstream ofsb("test.bin", ios::out | ios::binary);
  ofsb.write((char *)a, sizeof(unsigned short) * 128);
  ofsb.close();
}
void read_crypt() {
  FILE *f = fopen("test.bin", "r");
  fread(data_is, sizeof(char), 256, f);
  fclose(f);
}

int crypt() {
  read();
  for (int i = 0; i < 128; i++) {

    if (a[i] == '\0') {
      a[i] = ' ';
    }
  }
  unsigned short c[128];
  for (int i = 0; i < 128; i++) {
    char b = a[i];
    int counts = 0;
    for (int j = 0; j < 16; j++) {
      if (b & (1 << j)) {
        counts++;
      }
      if (i & (1 << j)) {
        counts++;
      }
    }
    cout << "b " << b << endl;
    if (counts % 2 == 0) {
      c[i] = 0;
    } else {
      c[i] = 1;
    }
    c[i] <<= 8;
    c[i] |= b;
    c[i] <<= 7;
    c[i] |= i;
    cout << bitset<16>(c[i]) << endl;
  }
  write(c);
  return 0;
}
void decrypt() {
  cout << "decrypt" << endl;
  read_crypt();
  for (int i = 0; i < 128; i++) {
    cout << i << " " << bitset<16>(data_is[i]) << endl;
  }
}
int main() {
  cout << bitset<16>('a') << endl;
  crypt();
  decrypt();
  return 0;
}
