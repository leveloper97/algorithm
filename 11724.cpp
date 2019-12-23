/* 
** BOJ 11724
** ???? ???? : DFS
** ???? ???? : ???? ????? ???? 
** https://www.acmicpc.net/problem/11724
*/

#include <iostream>

using namespace std;

void dfs(int );
bool input[1001][1001];
bool visited[1001] = {false};
int N, M;

int main() {
	// ??? 
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b = 0;
		cin >> a >> b;
		input[a - 1][b- 1] = true;
		input[b- 1][a - 1] = true;
	}
	// ???? 
	int result = 0;
	for (int i = 0; i < N; i++) {
		if (visited[i] == false) {
			dfs(i);
			result++;
		} 
	}
	
	// ??? 
	cout << result;
	
	return 0;
}

void dfs(int node) {
	visited[node] = true;
	for (int i = 0; i < N; i++) {
		if(visited[i] == false && input[node][i] == true) {
			dfs(i);
		}
	}
}
