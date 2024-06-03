
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int arr_end(int begin, int num, int size);

int arr_end_test(int begin, int num, int size);
void arr_test();

int main(int argc, char* argv[])
{
  // test
  /* arr_test(); */

  if(argc < 3)
    return 1;

  string str;
  int n, m;
  int begin = 1;

  n = atoi(argv[1]);
  m = atoi(argv[2]);

  while(1){
    str += to_string(begin);
    begin = arr_end(begin, n, m);
    if(begin == 1)
      break;
  }
  cout << str;
  return 0;
}

int arr_end(int begin, int num, int size)
{
  int res = (size % num) - 1;
  begin += res;
  if (begin > num)
    begin -= num;
  else if (begin < 1)
    begin = num;
  return begin;
}

int test_arr_end(int begin, int num, int size)
{
  int i, j;
  for (i = 1; i < size; i++) {
    if (++begin > num)
      begin = 1;
  }
  return begin;
}

void arr_test()
{
  int n, m, k;
  for (n = 2; n < 10; n++) {
    for (m = 2; m < 10; m++) {
      for (k = 1; k <= n; k++) {
        int sucess = test_arr_end(k, n, m);
        int val = arr_end(k, n, m);
        if (sucess != val) {
          cout << "ERROR" << endl;
          cout << ">>>>> n = " << n << " m = " << m << "<<<<<" << endl;
          cout << "begin(" << k << "): ";
          cout << sucess << " " << val << endl;
          exit(1);
        }
      }
    }
  }
  cout << "successfull test\n";
  exit(0);
}
