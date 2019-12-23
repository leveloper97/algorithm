/* 
** BOJ 7576
** 문제 유형 : BFS
** 문제 제목 : 토마토 
** https://www.acmicpc.net/problem/7576
*/

#include<iostream> 
#include<queue>
#include<utility>

using namespace std;

const int MAX = 1002;

int map[MAX][MAX];
int visited[MAX][MAX] = {0};

int dx[4] = {1, 0 , -1, 0};
int dy[4] = {0, -1 , 0, 1};
queue<pair<int,int> > q; 

int n;
int m;

bool tomato = false;

void bfs() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			// 토마토가 없는 상태 방문한걸로 처리한다. 
			if (map[i][j] == -1) {
//				visited[i][j] = 1;
			}
			// 익은 토마토들을 큐에다가 넣는다.
			else if (map[i][j] == 1) {
				visited[i][j] = 0;
				q.push(make_pair(i, j));
			}
			else {
				tomato = true;
			}
		}
	}
	
	if (tomato == false) {
		// 익힐 토마토가 없으니까 리턴해버린다.
		return; 
	}
	// 큐가 안비어있으면 계속 익도록 만든다. 
	while(q.empty() == false) {
		int x = q.front().first;
		int y = q.front().second;
		// 사용한 토마토는 필요가 없으므로 빼버린다. 
		q.pop();
		// 상하 좌우를 익힌다.
		for (int i = 0; i < 4; i++) {
			int moveX = x + dx[i];
			int moveY = y + dy[i];
	
			// 인덱싱 예외처리를 한다. 
			if (moveX < 0 || moveX >= m || moveY < 0 || moveY >= n) {
				continue;
			}
			// 익혀야하는 토마토를 익힌다. 
			if (map[moveX][moveY] == 0 && visited[moveX][moveY] == 0) {
				// 익은 걸로 처리한다. 
				map[moveX][moveY] = 1;
				// 걸린 일수를 저장한다. 
				visited[moveX][moveY] = visited[x][y] + 1;
				// 익은 토마토는 큐에 넣는다. 
				q.push(make_pair(moveX, moveY));
			}
		}
	}
} 

int main() {
	scanf("%d %d", &n, &m);
	
	// 토마토 정보를 입력 받습니다. 
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}
 
	// 토마토 익히기를 시작합니다. 
	bfs();
	
	// 익지 않은 토마토가 있는지 검사하고 걸린 일을 출력합니다. 
	int max = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == 0 && map[i][j] == 0) {
				printf("-1");
				return 0;
			}
			
			max = max < visited[i][j]? visited[i][j]:max;
		}
	}
	printf("%d", max);
	
	return 0;
}
