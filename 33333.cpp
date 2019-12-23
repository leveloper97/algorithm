#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct virus {
    int x, y;
};

int a[50][50], dist[50][50];
int n, m, k, ans=1e9;
bool select[10];
vector<virus> v;
queue<virus> q;
const int dx[] = {-1, 0 , 1, 0}, dy[] = {0, 1, 0, -1};

void bfs() {
    int infect=0, times=0;
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y; q.pop(); 
        for (int i=0; i<4; i++) {
            int nx = x+dx[i], ny = y+dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (a[nx][ny] != 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y]+1;
                if (a[nx][ny] == 0) {
                    infect += 1;
                    times = dist[nx][ny];
                }
                q.push({nx, ny});
            }
        }
    }
    if (infect == k && ans > times) ans = times;
}

void solve(int idx, int cnt, int d) {
    if (cnt == m) {
        memset(dist, -1, sizeof(dist));
        for (int i=0; i<d; i++) {
            if (select[i]) {
                q.push({v[i].x, v[i].y});
                dist[v[i].x][v[i].y] = 0;
            }
        }
        bfs();
        return;
    }
    for (int i=idx; i<d; i++) {
        if (!select[i]) {
            select[i] = true;
            solve(i+1, cnt+1, d);
            select[i] = false;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 2) v.push_back({i, j});
            if (a[i][j] == 0) k += 1;
        }
    }
    solve(0, 0, v.size());
    printf("%d\n", ans == 1e9 ? -1 : ans);
    return 0;
}


