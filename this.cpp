#include <iostream>
using namespace std;
class Data {
	int number;
	char *name;
	public: 
		Data(int number, char *name) {
			this->number = number;
			this->name = name;
		}
		void print() {
			cout << number << " " << name << endl;
		}
};
int main() {
	Data data(100, "name");
	data.print();
	
	return 0;
}
