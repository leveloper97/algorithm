/* 
** BOJ 11403
** 문제 유형 : DFS
** 문제 제목 : 경로 찾기
** https://www.acmicpc.net/problem/11403
*/

#include <iostream>

using namespace std;

void dfs(int top, int x, int y);

int N;	
bool input[101][101];
bool visited[101][101];
int result[101][101];

int main() {
	// 입력
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> input[i][j];
		}
	}
	// 로직
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (input[i][j] && !visited[i][i]) {
				dfs(i, i, j);	
			}
		}
	}
	// 출력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << result[i][j] << ' ';
		}
		cout << endl;
	}

	return 0;
}
/*
top = 시작 정점 (root)
i = 
j = 
*/

// dfs가 호출된다는 것은 
// 1) i -> j로 갈 수 있다.
// 2) visisted 검사를 하지 않았다.
void dfs(int top, int x, int y) {
	// i -> j로 갈 수 있으니까 result[top][y]의 값을 1로 할당한다.
	result[top][y] = 1;
	// 방문했으니까 더 이상 방문 안하게 true 값을 할당한다.
	visited[top][y] = true;

	// j에서 다른 정점으로 갈 수 있는지 검사한다.
	// TODO: 여기서 for문을 N번 도는게 효율적인가?
	for (int i = 0; i < N; i++) {
		if(input[y][i] && !visited[top][i]) {
			dfs(top, y, i);
		}
	}
}
/* 시행 착오
Q. 로직은 맞는데 계속 메모리가 초과한다.
A. visited[top][y]에 값을 true로 바꿔줘야 재귀적으로 덜 도는데 visted[x][y]로 돌려서 함수 호출이 많아져 메모리가 초과했다.
Q. 출력 형식이 잘못 됨.
A. 백준은 개행 한줄이라도 철저한 검사를 하는것 같다.
*/
