/* 
** BOJ 10845
** 문제 유형 : Queue
** 문제 제목 : 큐
** https://www.acmicpc.net/problem/10845
*/

#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main() {
	int n, num;
    cin >> n;
    queue<int> q;
    
    string str;
    for (int i = 0; i < n; i++) {
        cin >> str;
        if (str == "push") {
            cin >> num;
            q.push(num);
        }
        if (str == "pop") {
            if (!q.empty()) {
                cout << q.front() << endl;
                q.pop();
            } else {
                cout << "-1" << endl;
            }
        }
        if (str == "size") {
            cout << q.size() << endl;
        }
        if (str == "empty") {
            if (q.empty()) {
                    cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
        }
        if (str == "front") {
            if (q.empty()) {
                cout << "-1" << endl;
            } else {
                cout << q.front() << endl;
            }
        }
		if (str == "back") {
            if (q.empty()) {
                cout << "-1" << endl;
            } else {
                cout << q.back() << endl;
            }
        }
    }
	return 0;
}
