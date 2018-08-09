/* 
** BOJ 1012
** 문제 유형 : DFS
** 문제 제목 : 유기농 배추
** https://www.acmicpc.net/problem/1012
*/

#include <iostream>

using namespace std;

int tc;
int K;
int M;
int N;
int res[51];
int cab[51][51] = {1};
bool visited[51][51] = {false};
// 동서남북 순서로 이동.
int moveX[] = {1, -1, 0, 0};
int moveY[] = {0, 0, -1, 1};
int cnt;
int index = 0;


void dfs(int x, int y);

int main() {
	// 입력을 받는다.
	int x, y;
	cin >> tc;
	while (tc--) {
		// 입력
		cin >> M;
		cin >> N;
		cin >> K;
		// TC 마다 새롭게 쓸 것들 초기화 한다. (cnt, cab[][], visited[][])
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				cab[i][j] = 0;
				visited[i][j] = false;
			}
		}
		cnt = 0;
		// 배추의 위치를 입력 받는다.
		for (int i = 0; i < K; i++) {
			cin >> x >> y;
			cab[x][y] = 1;
		}
		// DFS를 수행한다.
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (cab[i][j] && !visited[i][j]) {
					dfs(i, j);
					cnt++;
				}
			}
		}
		cout << cnt << endl;
	}
	return 0;
}

void dfs(int x, int y) {
	visited[x][y] = true;
	cab[x][y] = 0;
	for (int i = 0; i < 4; i++) {
		int nextX = x + moveX[i];
		int nextY = y + moveY[i];
		if (nextX >= 0 && nextY >= 0 && nextX < M && nextY < N) {
			if (cab[nextX][nextY] && !visited[nextX][nextY]) {
				dfs(nextX, nextY);
			}
		}
	}
}

/* 시행 착오
Q. 맞았는데 백준이 자꾸 틀렸대?
A. cout을 TC가 검사가 끝날때 마다 했어야했다.
A. TC가 새롭게 시작할때마다 전역변수를 원래대로 초기화 안해줘서 틀렸다.
A. if 문 로직을 너무 대충 짰다.
*/
