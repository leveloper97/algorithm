#include <iostream>
#include <queue>
#include <utility>
#include <cmath>
#include <memory.h>
using namespace std;

int answer = 0;
int N, M;
int map[10][10];
int origin_map[10][10];
queue <pair <int, int> > virus;
vector <pair <int, int> > backup;   
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void recover_origin();
void spread_virus();
void make_wall(int);


int main () {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
			origin_map[y][x] = map[y][x];
			if (map[y][x] == 2) { // 바이러스 
				virus.push(make_pair(y, x));
			}
		}
	}
	for (int y = 0; y < N; y++) { 
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 0) {
				map[y][x] = 1; // 벽을 세운 상태로 만든다. 
				backup.push_back(make_pair(y,x));
				make_wall(1); // 벽을 만들기 시작한다. 
				map[y][x] = 0; // 백트래킹을 위해 다시 0을 넣는다. 
				backup.pop_back();
			} 
		}	
	}
	// 답을 출력한다. 
	cout << answer;
	return 0;
}

void recover_origin() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			map[y][x] = origin_map[y][x];
			if (origin_map[y][x] == 2) {
				virus.push(make_pair(y, x));
			}
		}
	}
	for (int i = 0; i < backup.size(); i++) {
		int y = backup[i].first;
		int x = backup[i].second;
		map[y][x] = 1;
	}
}

void make_wall(int cnt) { // 3개의 벽을 세운다. 
	if (cnt == 3) { //3개의 벽을 골랐다.
		spread_virus(); // 바이러스를 퍼트린다. 
		return; 
	}
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 0) {
				map[y][x] = 1; // 벽을 세운다.
				backup.push_back(make_pair(y,x));
				make_wall(cnt+1); 
				map[y][x] = 0; // 백트래킹을 위해 다시 초기화한다. 
				backup.pop_back();
			}
		}
	} 
}
void spread_virus() { // 바이러스를 퍼트린다. 
	while (virus.empty() == false) {
		int y = virus.front().first;
		int x = virus.front().second;
		virus.pop();
		// 상하 좌우로 계속 움직인다.
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
				continue; // 예외처리 
			}
			if (map[ny][nx] == 0) { // 빈칸일때 퍼트린다. 
//				cout << "퍼트린다" << endl;
				map[ny][nx] = 2; 
				virus.push(make_pair(ny, nx));
			} 
		}
	}
	
	int cnt = 0;
	for (int y = 0; y < N; y++) {
//		cout << endl;
		for (int x = 0; x < M; x++) {
//			cout << map[y][x] << " ";
			if (map[y][x] == 0) {
				// cout << map[y][x] << " ";
				cnt++; // 안전 구역을 센다. 
			}
		}
	}
	// 최대값을 갱신한다. 
	answer = max(cnt, answer);
	recover_origin();
}
//// 지도용 
//void copy_map(int (*a)[10], int (*b)[10]){
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < M; j++) {
//            a[i][j] = b[i][j];
//        }
//    }
//}
