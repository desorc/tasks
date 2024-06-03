
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#define open_file(var, filename, mode) \
  var.open(filename, mode);            \
  if (!var.is_open()) {                \
    perror("file open");               \
    exit(1);                           \
  }

int read_dnum(double* arr, int size, ifstream* file);
int check(double cx, double cy, double cr2, double tx, double ty);

int main(int argc, char* argv[])
{
  if(argc < 3)
    return 1;
  string str;
  double t[2];
  double circ[3];

  ifstream cf, tf;
  string cname = argv[1];
  string tname = argv[2];

  open_file(cf, cname, ifstream::in);
  open_file(tf, tname, ifstream::in);

  if (read_dnum(circ, 3, &cf))
    return 1;

  circ[2] = pow(circ[2], 2);

  while (1) {
    if (read_dnum(t, 2, &tf))
      break;
    str += to_string(check(circ[0], circ[1], circ[2], t[0], t[1])) + "\n";
  }
  cout << str;
  return 0;
}

int read_dnum(double* arr, int size, ifstream* file)
{
  int i;
  for (i = 0; i < size; i++) {
    if (!(*file >> arr[i])) {
      return 1;
    }
  }
  return 0;
}

int check(double cx, double cy, double cr2, double tx, double ty)
{
  double d = pow(tx - cx, 2) + pow(ty - cy, 2);
  if (cr2 < d)
    return 2;
  if (cr2 > d)
    return 1;
  return 0;
}
