/* 
** BOJ 17144
** 문제 유형 : 
** 문제 제목 : 미세먼지 안녕! 
** https://www.acmicpc.net/problem/17144
*/

#include <stdio.h>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int dy = {1, -1, 0, 0};
const int dx = {0, 0, -1, 1};
int R, C, T;
int total = 0;
int map[50][50];
int temp[50][50] = {0 ,};
queue <pair <int, int> > dust;
vector <pair <int, int> > air_con[2];

void bfs(int );
void spread_dust(); // 미세먼지를 퍼트린다.
void do_clean(); // 청소기를 돌린다. 
int main() {
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			scanf("%d", &map[y][x]);
			if (map[y][x] > 0) { // 공기청정기도 미세먼지도 없는 경우 
				total += map[y][x];
				dust.push(make_pair(y, x)); // 미세 먼지 큐에 푸시 
			} else if (map[y][x] == -1) { // 공기 청정기임. 
				air_con.push_back(make_pair(y, x));
			} 
		}
	}
	bfs(T);
	printf("%d", total); // 정답 출력 
	return 0;
}
void bfs(int t) {
	for (int i = 0; i < t; i++) { // t초 만큼 확산과 청소를 반복한다. 
		spread_dust();
		do_clean();
	}
}

void spread_dust() {
	while(dust.empty() == false) {
		int y = dust.front().first;
		int x = dust.front().second;
		dust.pop();
		int spread_cnt = 0;
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny > 0 && nx > 0 && ny < R && nx < C && map[ny][nx] != -1) { // 확산 시킬수 있다. 
				spread_cnt++;
				temp[ny][nx] = map[y][x] / 5;
			}
		}
		map[y][x] = map[y][x] - (spread_cnt * 5);
	}
	// 미세먼지 갱신 
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			map[y][x] += temp[y][x];
			if (map[y][x] > 0) { // 큐에 다시 푸시
				dust.push(make_pair(y, x));
			}
		}
	}
} 

void do_clean() { // 청소 시작 
	
}

