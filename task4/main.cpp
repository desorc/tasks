
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

size_t hod(vector<int> &arr){
  size_t i;
  size_t min = 0;
  int center = arr.size() / 2;
  for(i = 0; i < center; i++)
    min += abs(arr[i] - arr[center]);
  for(i = center+1; i < arr.size(); i++)
    min += abs(arr[i] - arr[center]);

  return min;
}

size_t test2(vector<int> &arr){
  size_t i, j;
  size_t min = 0;
  int aver;
  size_t center;
  if((arr.size() % 2) == 0){
    center = arr.size()/2;
    aver = (arr[center] - arr[center-1]) / 2;
    aver += arr[center-1];
    for(i = 0; i < arr.size(); i++){
      min += abs(aver - arr[i]);
    }
  }
  return min;
}

size_t test1(vector<int> &arr){
  size_t i, j;
  size_t min = -1;
  size_t now = 0;
  for(i = 0; i < arr.size(); i++){
    now = 0;
    for(j = 0; j < arr.size(); j++){
      if(j != i){
        now += abs(arr[j] - arr[i]);
      }
    }
    /* cout << now << " "; */
    if(min == -1 || now < min)
      min = now;
  }
  /* cout << endl; */
  return min;
}

void test(){
  int max = 10;
  int min = -10;
  int i;
  size_t size = 8;
  vector<int> arr;

  for(i = 0; i < size; i++)
    arr.push_back(min);

  bool mod2 = false;
  if((size % 2) == 0)
    mod2 = true;
  size_t t1, t2, val, tmin;
  while(arr[size-1] <= max){
    arr[0]++;
    for(int i = 1; i < size; i++){
      if(arr[i-1] > max){
        arr[i]++;
        arr[i-1] = min;
      }
    }
    vector<int> arr1 = arr;
    sort(arr1.begin(), arr1.end());
    t1 = test1(arr1);
    t2 = test2(arr1);
    val = hod(arr1);
    if(mod2){
      if(t1 != t2){
        cout << "uncorrect: " << t1 << " " << t2 << endl;
      }
      if(t1 < t2)
        tmin = t1;
      else
        tmin = t2;
      if(tmin != val){
        printf("ERROR %lu %lu\n", tmin, val);
        exit(1);
      }
    }else{
      tmin = t1;
      if(tmin != val){
        printf("ERROR %lu %lu\n", tmin, val);
        exit(1);
      }
    }
  }
  exit(0);
}

int main(int argc, char *argv[])
{
  if(argc < 2)
    return 1;
  int val;
  vector<int> arr;
  ifstream file(argv[1]);
  while(file >> val){
    arr.push_back(val);
  }
  sort(arr.begin(), arr.end());
  cout << hod(arr);
  return 0;
}
