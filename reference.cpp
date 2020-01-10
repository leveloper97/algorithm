#include <iostream>
using namespace std;
int main(void) {
	int a = 4;
	int *pA = &a;
	int &b = a;
	cout <<	a << *pA << b << endl;
}
