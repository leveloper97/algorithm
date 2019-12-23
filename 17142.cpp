/* 
** BOJ 17142
** 문제 유형 : 시뮬레이션 
** 문제 제목 : 연구소3 
** https://www.acmicpc.net/problem/17142
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <iostream>
#include <utility>
using namespace std;

int map[50][50]; // 원본 배열 저장용
int visited[50][50]; // 연산용
int N, M, K;
int target = 0;
int answer = 1e9;
bool selected[10];
vector <pair <int, int> > virus;
queue <pair <int, int> > select_virus;

const int dy[4] = {0, 1, 0, -1};
const int dx[4] = {-1, 0 , 1, 0};

void bfs() {
    int infect = 0;
    int sec = 0;
    while (select_virus.empty() == false) {
        int y = select_virus.front().first;
        int x = select_virus.front().second; 
        select_virus.pop();
        for (int i = 0; i < 4; i++) { // 네 방향 탐색
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) 
                continue; // 예외처리
            if (map[ny][nx] != 1 && visited[ny][nx] == -1) { // 벽이 아니고 초기 상태라면
                visited[ny][nx] = visited[y][x] + 1;
                if (map[ny][nx] == 0) {
                    infect++; // 감염 개수 증가
                    sec = visited[ny][nx];
                }
                select_virus.push(make_pair(ny, nx));
            }
        }
    }
    if (infect == target && answer > sec) {
        answer = sec;
    }
}

void solve(int idx, int cnt) {
    if (cnt == M) { // 3개의 조합을 완성한 경우
        memset(visited, -1, sizeof(visited));
        for (int i = 0; i < virus.size(); i++) {
            if (selected[i] == true) {
                select_virus.push(make_pair(virus[i].first, virus[i].second));
                visited[virus[i].first][virus[i].second] = 0;
            }
        }
        bfs();
        return;
    }
    for (int i = idx; i < virus.size(); i++) {
        if (selected[i] == false) { // 선택하지 않았으면 선택
            selected[i] = true;
            solve(i+1, cnt+1); // 3개 만들때까지 재귀 호출
            selected[i] = false;
        }
    }
}

int main() {
    cin >> N >> M;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> map[y][x];
            if (map[y][x] == 2) { // 바이러스
                virus.push_back(make_pair(y, x));
            } else if (map[y][x] == 0) { // 빈 집
                target++;
            }
        }
    }
    solve(0, 0);
    if (answer == 1e9) {
        cout << -1;
    } else {
        cout << answer;
    }
    return 0;
}


