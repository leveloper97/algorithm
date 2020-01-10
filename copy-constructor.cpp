// 복사 생성자의 호출 
#include<iostream>
using namespace std;
class A {
  int x;

 public:
  A(int c) : x(c) {}
  A(const A& a) {
    x = a.x;
    cout << "복사생성" << endl;
  }
};

class B {
  A a;

 public:
  B(int c) : a(c) {}
  B(const B& b) : a(b.a) {}
  A get_A() { return a; }
};

int main() {
  B b(10);
  A a1 = b.get_A();
}
