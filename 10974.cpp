/* 
** BOJ 10974
** 문제 유형 : 순열
** 문제 제목 : 모든 순열
** https://www.acmicpc.net/problem/10974
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
/* 풀이방법 1
	C++ STL의 next_permutation()을 사용하면 쉽게 풀 수 있다. 
*/

int main() {
		
	int n;
	cin >> n;
	vector<int> a(n);

 
    for (int i = 1; i <= n; i ++) {
        a[i - 1] = i;
    }
 
    do {
        for (int i = 0; i < n; i ++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
    } while(next_permutation(a.begin(), a.end()));
 
    return 0;
}