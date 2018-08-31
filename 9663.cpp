/* 
** BOJ 9663
** 문제 유형 : 백트래킹
** 문제 제목 : N-Queen
** https://www.acmicpc.net/problem/9663
*/

#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

void dfs(int);
bool isPossible(int);

int arr[16];
int ans;
int n;

int main() {
	
	
	cin >> n;
	
	
	for(int i = 1; i <= n; i++) {
		arr[1] = i;
		dfs(2);
	}
	cout << ans;

	return 0;
}

void dfs(int row) {
   if (row > n) {
		++ans;
	} else {
		for (int i = 1; i <= n; i++) {
			// 노드의 좌표를 저장 (row: 열, i: 행)
			arr[row] = i;
			// 유망한 노드 검토
			if (isPossible(row)) {
				// 서브 트리 이동 (해당 노드의 하위 노드)
				dfs(row + 1);
			} else {
				// 백트래킹 수행, 해당 노드는 가지치기.
				arr[row] = 0;
			}
		}
	}
}

bool isPossible(int c) {
	// 이전 열들을 탐색하면서 유망한 노드인지 확인
	for (int i = 1; i < c; i++) {
		// 상위 노드에서 같은 행에 퀸이 있는지 여부
		if (arr[i] == arr[c]) {
			return false;
		}
		// 대각선 검사, 상위 노드의 퀸과 현재 노드의 퀸의 가로 세로 거리가 같은지 검사
		if (abs(arr[i] - arr[c]) == abs(i - c)) {
			return false;
		}
	}
	return true;
}



