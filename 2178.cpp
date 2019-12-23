/* 
** BOJ 2178
** 문제 유형 : BFS
** 문제 제목 : 미로 찾기 
** https://www.acmicpc.net/problem/2178
*/

#include <iostream>
#include <queue>
#include <utility>

using namespace std;

const int MAX = 102; // 가로, 세로 최대 100입니다. (인덱스오버플로우 대비 +2) 

int n = 0; // 세로 크기
int m = 0; // 가로 크기

int map[MAX][MAX]; // 지도 정보 배열을 생성합니다. 
int visited[MAX][MAX] = {0}; // 이 경로로 오기까지 최소 회수 저장 용도의 배열입니다. 

// 동서남북으로 이동시키기 위한 배열입니다. 
int dx[4]={1, 0, 0, -1};
int dy[4]={0, 1, -1, 0};

// bfs를 위한 queue를 선언합니다. 
queue<pair<int,int> > q; 

void bfs(int x, int y) {	
	q.push(make_pair(x, y)); 
	visited[x][y] = 1;
	
	while(q.empty() == false) {
		int first = q.front().first;
		int second = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nextX = first + dx[i];
			int nextY = second + dy[i];
			if (nextX < 0 || n < nextX || nextY < 0 || m < nextY) {
				// 인덱싱 오버플러우를 처리합니다. 
				continue;
			}
			// 미로를 헤매다 도착된 시점을 이미 visit가 된 상태이므로 예외처리를 고려하지 않습니다. 
			if (map[nextX][nextY] == 1 && visited[nextX][nextY] == 0) {
				q.push(make_pair(nextX, nextY));		
				visited[nextX][nextY] = visited[first][second] + 1;
			}
		}
	}
} 

int main() {
	scanf("%d", &n);
	scanf("%d", &m);
	   
    // 지도의 정보를 입력 받습니다.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
           scanf("%1d", &map[i][j]);
        }
    }
    // 지도 끝까지 가는 것을 보장하므로 바로 출발합니다.
   	bfs(0, 0);	
	
    // 제일 마지막의 횟수를 출력합니다. 
    printf("%d\n", visited[n-1][m-1]);
    
    return 0;
}


