/* 
** BOJ 2589
** 문제 유형 : BFS
** 문제 제목 : 불 
** https://www.acmicpc.net/problem/2589
*/
#include <iostream>
#include <utility>
#include <queue>
#include <memory.h>
#include <cmath>
using namespace std;

int width, height;
char map[50][50];
int dist[50][50] = {0, };
bool visited[50][50] = {false, };
void bfs();
queue <pair <int, int> > land; // 땅
queue <pair <int, int> > q;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};
int answer = 0;
int main() {
	// 입력 
	ios_base::sync_with_stdio(false);
	cin >> height >> width;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cin >> map[y][x];
			if (map[y][x] == 'L') {
				land.push(make_pair(y, x));
			}
		}
	}
	bfs();
	cout << answer;
}
void bfs() {
	while(land.empty() == false) {
		int pos_y = land.front().first;
		int pos_x = land.front().second;
		land.pop();
		memset(dist,0,sizeof(dist));
		
		visited[pos_y][pos_x] = true;
		q.push(make_pair(pos_y, pos_x));
		printf("새로운 출발 \n");
		cout << "pos_y: "<< pos_y << "x:" << pos_x << endl;
		while(q.empty() == false) {
			int y = q.front().first;
			int x = q.front().second;	
			q.pop();
				
			for (int dir = 0; dir < 4; dir++) { 
				int ny = y + dy[dir];
				int nx = x + dx[dir];
				if (ny < 0 || ny >= height || nx < 0 || nx >= width) {
					continue; // 지도 인덱싱 예외 처리 
				}
				if (map[ny][nx] == 'W' || (pos_y == ny && pos_x == nx)) {
					continue; // 바다, 방문한 곳에 대한 예외처리 
				}
				if (dist[ny][nx] == 0 || dist[ny][nx] > dist[y][x] +1){
					//visited[ny][nx] = true;
                    dist[ny][nx] = dist[y][x] + 1;
                    q.push(make_pair(ny, nx));
                } 
			}		
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (dist[y][x] != 0) {
				answer = max(answer, dist[y][x]);
			}
		}   
	}
            
}
