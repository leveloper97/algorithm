#include <iostream>
using namespace std;
int default_test (int a = 1, int b = 2);

int main() {
	
	cout << default_test();
}

int default_test(int a, int b) {
	return a+b;	
}
