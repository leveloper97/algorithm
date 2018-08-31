/* 
** BOJ 9095
** 문제 유형 : DP
** 문제 제목 : 1, 2, 3 더하기
** https://www.acmicpc.net/problem/9095
*/
#include <iostream>
#include <queue>

using namespace std;

/*
n이 11보다 작고 1, 2, 3의 조합으로 cnt를 찾아야한다고해
더하기 연산만으로 이루어져 있어서 반드시 점화식이 존재할 거라 생각했다.
합으로만 이뤄져 있기 때문에 f(n) = f(n-1) + f(n-2) + f(n=3)임을 빠르게 찾았다.
*/

int main() {
	
	int tc, n;
	cin >> tc;
	int cnt[12]= {0, 1, 2, 4};
	queue <int> answer;
	while (tc--) {
		cin >> n;
		for (int i = 4; i <= n; i++) {
			cnt[i] = cnt[i-1] + cnt[i-2] + cnt[i-3];
		}
		answer.push(cnt[n]);
	}
 	while (!answer.empty()) {
     	cout << answer.front() << endl;
		answer.pop();
  	}
	
	return 0;
}