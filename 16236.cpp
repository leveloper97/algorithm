/* 
** BOJ 16236
** 문제 유형 : DFS
** 문제 제목 : 아기 상어 
** https://www.acmicpc.net/problem/16236
*/

#include <iostream>
#include <queue>
#include <utility> 

using namespace std;

int n; // 공간의 크기
struct SHARK {
	int y, x, time;
}; // 상어 정보 
int map[20][20];
SHARK shark;
// 이동용 좌표 
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1}; 
     
int main() {
	int shark_eat = 0;
	int shark_size = 2;
	// 입력
	scanf("%d", &n);
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			scanf("%d", &map[y][x]);
			if (map[y][x] == 9) {
				shark.y = y, shark.x = x, shark.time = 0;
				map[y][x] = 0;
			}
		}
	}
	// 로직 
	bool is_update = true;
	while (is_update) {
		is_update = false;
		 
		bool visited[20][20] = {false, };
		queue <SHARK> q; // 상어 정보를 담는 큐 생성
		visited[shark.y][shark.x] = true; // 상어 현재 위치 방문 처리 
		q.push(shark);
		
		SHARK candi; // 먹을 수 있는 물고기 후보 
		candi.y = 20, candi.time = -1;
		while (q.empty() == false) {
			SHARK cur = q.front(); q.pop();
			
			// 먹을수 있는 물고기가 없다. 
			if (candi.time == -1 && candi.time < cur.time) {
				break;
			}
			// 물고기를 먹을 수 있으면서 y좌표가 가장 먼 것을 넣는다. 
			if (map[cur.y][cur.x] < shark_size && map[cur.y][cur.x] != 0) {
				is_update = true;
				if (candi.y > cur.y || (candi.y == cur.y && cur.x > candi.x)) {
					candi = cur;
				}
			}
			
			for (int dir = 0; dir < 4; ++dir) {
				SHARK next;
				next.y = cur.y + dy[dir];
				next.x = cur.x + dx[dir];
				next.time = cur.time + 1;
				// 예외 처리 
				if (next.y < 0 || next.y >= n || next.x < 0 || next.x >= n) {
					continue;
				}
				// 아기 상어가 물고기를 먹는 조건 
				if (visited[next.y][next.x] == false && shark_size >= map[next.y][next.x]) {
					visited[next.y][next.x] = true;
					q.push(next);
				}
			}
		}
		if (is_update == true) {
			shark = candi;
			++shark_eat;
			// 먹은 물고기의 개수와 상어의 크키가 같으면 사이즈를 올린다. 
			if (shark_eat == shark_size) { 
				++shark_size;
				shark_eat = 0;
			}
			map[shark.y][shark.x] = 0;
		} 
	} 
	
	// 출력
	printf("%d", shark.x); 
	return 0;
}
