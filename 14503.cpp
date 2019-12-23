#include <iostream>
#include <queue>
#include <memory.h>

using namespace std;
int N, M;
int map[51][51];
bool visited[51][51];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int cnt;

void dfs(int y, int x, int dir) {
    //cout << " 현재 위치 : (" << y << "," << x << ")" << endl;
    int next_dir = dir;
    bool is_clean = false;
    for (int k = 0; k < 4; k++) {
        next_dir = (next_dir + 3) % 4;
        int ny = y + dy[next_dir]; 
		int nx = x + dx[next_dir];
        if (!visited[ny][nx] && ny >= 0 && nx >= 0 && ny < N && nx < M && map[ny][nx]==0) {
            is_clean = true;
            visited[ny][nx] = true;
            cnt++;
            dfs(ny, nx, next_dir);
            return;
        }
    }
    int move_dir = (dir + 2) % 4;
    if (map[y+dy[move_dir]][x+dx[move_dir]] == 0) {
    	dfs(y + dy[move_dir], x + dx[move_dir], dir);
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> N >> M;
    int r, c, d; //row,col, direction
    cin >> r >> c >> d;
    visited[r][c] = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
    cnt = 1;
    dfs(r, c, d);
    cout << cnt << endl;
}

