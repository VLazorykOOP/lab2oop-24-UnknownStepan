#include <bitset>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/types.h>
using namespace std;

typedef struct cryptstruct {
  union return_value {

    struct {
      unsigned int num : 7;
      unsigned int ch : 8;
      unsigned int set_of_bits : 1;
    };

    unsigned int return_value;
  } return_value;
} cryptstruct;

// read from file and split each character in list
char output[128];
char a[128];
unsigned short data_is[128];

void space();
void read_txt_file();
void console_to_array(char *a);
void write_bins(unsigned short *a);
void crypt();
void decrypt();
void output_console();
void read_crypt_bin();
void crypt2();
void decrypt2();

int main() {
  char inp = 'a';

  do {
    system("clear");
    cout << "1 - crypt \n2 - decrypt \n3 - console to array \n4 - read from "
            "file \n5 - read from bin \n6 - write in bin\n7 - output \n0 - "
            "exit\n8 - crypt2\n9 - decrypt2 [ ]\b\b";
    char inp = 'a';
    cin >> inp;
    switch (inp) {
    case '1':
      crypt();
      break;
    case '2':
      decrypt();
      break;
    case '3':
      console_to_array(a);
      break;
    case '4':
      read_txt_file();
      break;
    case '5':
      read_crypt_bin();
      break;
    case '6':
      write_bins(data_is);
      break;
    case '7':
      output_console();
      break;
    case '8':
      crypt2();
      break;
    case '9':
      decrypt2();
      break;
    case '0':
      break;
    }
    cin.get();
    cin.get();
  } while (inp != '0');
  return 0;
}

void read_txt_file() {
  FILE *f = fopen("test.txt", "r");
  fread(a, sizeof(char), 128, f);
  fclose(f);
  space();
}
void console_to_array(char *a) {
  string s;
  cin >> s;
  for (int i = 0; i < s.length(); i++) {
    a[i] = s[i];
  }
  space();
  cout << endl;
}
// write in binary file array
void write_bins(unsigned short *a) {
  ofstream ofsb("test.bin", ios::out | ios::binary);
  ofsb.write((char *)a, sizeof(unsigned short) * 128);
  ofsb.close();
}
void read_crypt_bin() {
  FILE *f = fopen("test.bin", "r");
  fread(data_is, sizeof(char), 256, f);
  fclose(f);
}
void output_console() {
  for (int i = 0; i < 128; i++) {
    cout << output[i];
  }
}
void space() {
  for (int i = 0; i < 128; i++) {

    if (a[i] == '\0') {
      a[i] = ' ';
    }
  }
}

void crypt() {
  for (int i = 0; i < 128; i++) {
    cout << a[i] << endl;
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
    if (counts % 2 == 0) {
      data_is[i] = 0;
    } else {
      data_is[i] = 1;
    }
    data_is[i] <<= 8;
    data_is[i] |= b;
    data_is[i] <<= 7;
    data_is[i] |= i;
  }
}
void decrypt() {
  cout << "decrypt" << endl;
  for (int i = 0; i < 128; i++) {
    int sets = 0;
    cout << bitset<16>(data_is[i]) << endl;
    for (int j = 0; j < 15; j++) {
      if (data_is[i] & (1 << j)) {
        sets++;
      }
    }
    if ((sets & 1) == (data_is[i] >> 15)) {
      cout << "integirity passed";
    } else {
      cout << "integirity failed";
      continue;
    }

    int index = (data_is[i] & 127);
    char b = (data_is[i] >> 7) & 255;
    output[index] = b;
    cout << output[index];

    cout << endl;
  }
}

void crypt2() {
  for (int i = 0; i < 128; i++) {
    char b = a[i];
    int counts = 0;
    for (int j = 0; j < 16; j++) {
      if (b & (1 << j)) {
        counts = !(counts);
      }
      if (i & (1 << j)) {
        counts = !(counts);
      }
    }
    cryptstruct c;

    c.return_value.set_of_bits = counts;
    c.return_value.ch = b;
    c.return_value.num = i;

    data_is[i] = c.return_value.return_value;
    cout << bitset<16>(data_is[i]) << endl;
  }
}
void decrypt2() {

  cout << "decrypt" << endl;
  for (int i = 0; i < 128; i++) {
    int sets = 0;
    cout << bitset<16>(data_is[i]) << endl;
    cryptstruct c;
    c.return_value.return_value = data_is[i];
    for (int j = 0; j < 15; j++) {
      if (c.return_value.return_value & (1 << j)) {
        sets++;
      }
    }
    if ((sets & 1) == (c.return_value.return_value >> 15)) {
      cout << "integirity passed";
    } else {
      cout << "integirity failed";
      continue;
    }

    int index = (c.return_value.num);
    char b = (c.return_value.ch);
    output[index] = b;
    cout << output[index];

    cout << endl;
  }
}
