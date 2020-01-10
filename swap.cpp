#include <iostream>

using namespace std;

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(void) {
	int input1, input2;
	cin >> input1 >> input2;
	swap(&input1, &input2);
	cout << input1 << " " << input2 << endl;
}

