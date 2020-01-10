// 배열의 레퍼런스 
#include <iostream>
using namespace std;
int main() {
  int arr[3] = {1, 2, 3};
  int (&ref)[3] = arr;

  ref[0] = 3;
  ref[1] = 2;
  ref[2] = 1;

  cout << arr[0] << arr[1] << arr[2] << endl;
  return 0;
}
