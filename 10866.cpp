/* 
** BOJ 10866
** 문제 유형 : Deque
** 문제 제목 : 덱
** https://www.acmicpc.net/problem/10866
*/

#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main() {
	
    string k;
    deque <int> d;
    int loop, num;
    cin >> loop;
	
	for (int i = 0; i < loop; i++) {
        cin >> k;
        if (k == "push_front") {
            cin >> num;
            d.push_front(num);
        }
        else if (k == "push_back") {
            cin >> num;
            d.push_back(num);
        }
        else if (k == "pop_front")
        {
            if (!d.empty()) {
                cout << d.front() << endl;
                d.pop_front();
            }
            else
                cout << "-1" << endl;
        }
		else if (k == "pop_back")
        {
            if (!d.empty())
            {
                cout << d.back() << endl;
                d.pop_back();
            }
            else
                cout << "-1" << endl;
        }
        else if (k == "size")
        {
            cout << d.size() <<endl;
        }
        else if (k == "empty")
        {
			if (!d.empty()) {
				cout << 0 << endl;
			} else {
				cout << 1 << endl;
			}
        }
        else if (k == "front")
        {
            if (!d.empty())
                cout << d.front() << endl;
            else
                cout << "-1" << endl;
        }
        else if (k == "back")
        {
            if (!d.empty())
                cout << d.back() << endl;
            else
                cout << "-1" << endl;
        }
    }
	return 0;
}