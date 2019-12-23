/* 
** BOJ 5427
** 문제 유형 : BFS 
** 문제 제목 : 불 
** https://www.acmicpc.net/problem/5427
*/ 
#include<iostream>
#include<queue>
#include<utility>

using namespace std;

const int MAX = 1002;
char map[MAX][MAX] = {0};
int visited[MAX][MAX] = {0}; 

// 오른쪽, 아래쪽, 왼쪽, 위쪽으로 이동 
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

// 전역변수로 두는게 좋을까 인자로 넘겨주는게 좋을까 
int w;
int h; 

int bfs() {
	queue <pair<int,int> > q; // 상근이 위치 관리용 큐 생성 
	queue <pair<int,int> > p; // 불이 안붙은 나무 저장용 큐 생성
	
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			// #, *은 못가는 길로 표시 
			if (map[i][j] == '*' || map[i][j] == '#') {
				visited[i][j] == 1;
			}
			// @은 상근이 위치도 방문한걸로, 큐에 푸시한다. 
			else if (map[i][j] == '@') {
				visited[i][j] == 0;
				q.push(make_pair(i, j));
			}
			// .은 아직 갈수 있는 길이므로 큐에 푸시한다. 
			else if (map[i][j] == '.') {
				p.push(make_pair(i, j));
			}
		}
	}
	while(q.empty() == false) {
		// 상근이 위치 설정 
		int x = q.front().second;
		int y = q.front().first;
		q.pop();
		// 상근이 이동시키기 
		// printf("현재 상근이의 위치 %d %d \n", x, y);
		for (int i = 0; i < 4; i++) {
			int moveX = x + dx[i];
			int moveY = y + dy[i];
			if (moveX < 0 || moveY < 0 || moveX >= w || moveY >= h) {
				// 탈출 성공한 경우
				return visited[y][x] + 1;
			}
			// 상근이 이동 
			if (map[moveY][moveX] == '.' && visited[moveY][moveX] == 0) {
				visited[moveY][moveX] = visited[y][x] + 1;
				q.push(make_pair(moveY, moveX)); 
			}
		}
		// 불 퍼트리기 
		while(p.empty() == false) {
			int treeX = p.front().second;
			int treeY = p.front().first;
			p.pop();
			for (int i = 0 ; i < 4; i++) {
				int moveX = treeX + dx[i];
				int moveY = treeY + dy[i];
				if (moveX < 0 || moveY < 0 || moveX >= w || moveY >= h) {
					continue;
				}
				// 상하좌우에 불이 있다. 옮겨붙는다. 
				if (map[moveY][moveX] == '*' && visited[treeY][treeX]) {
					map[treeY][treeX] = '*';
					visited[treeY][treeX] = 1;
				}
			}	
		} 
	}
	
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	char fail[] = "IMPOSSIBLE";
	
	int tc;
	int result = 0;
	scanf("%d", &tc);
	for (int i = 0; i < tc; i++) {
		// 너비, 높이를 입력 받습니다.
		scanf("%d %d", &w, &h);
		map[MAX][MAX] = {0};
		visited[MAX][MAX] = {0};
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
			}
		}
		result = bfs();
		if (result == 0) {
			printf("%s\n", fail);
		} else{
			printf("%d\n", result);	
		}
	}
	return 0;
}
