/* 
** BOJ 10828
** 자료 구조 문제(Stack)
** 스택
** https://www.acmicpc.net/problem/10828
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    // n ( 1 <= n <= 10000 )
    int n, num;
    cin >> n;
    stack<int> st;
    
    string str;
    for (int i = 0; i < n; i++) {
        cin >> str;
        if (str == "push") {
            cin >> num;
            st.push(num);
        }
        if (str == "pop") {
            if (!st.empty()) {
                cout << st.top() << endl;
                st.pop();
            } else {
                cout << "-1" << endl;
            }
        }
        if (str == "size") {
            cout << st.size() << endl;
        }
        if (str == "empty") {
            if (st.empty()) {
                    cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
        }
        if (str == "top") {
            if (st.empty()) {
                cout << "-1" << endl;
            } else {
                cout << st.top() << endl;
            }
        }
    }
    return 0;
}