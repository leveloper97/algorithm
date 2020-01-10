#include <iostream>

using namespace std;

int start_x = 0;
int start_y = 0;
int present = 0;
int map[100][100];

void insert_edge(int map[][100], int n) {
	int next_x = 0;
	int next_y = 0;
	// 윗줄 채우기 
	for (int i = 0; i < n; i++) {
		next_y = start_y;
		next_x = start_x + i;
		map[next_y][next_x] = ++present;
		printf("윗줄 채우기 %d%d", next_y, next_x);
		printf("%d\n", map[next_y][next_x]);
	}
	// 오른쪽 채우기
	for (int i = 0; i < n-1; i++) {
		next_y = next_y+1;
		next_x = next_x;
		map[next_y][next_x] = ++present;
		printf("오른쪽 채우기 %d%d", next_y, next_x);
		printf("%d\n", map[next_y][next_x]);
	}
	// 아래쪽 채우기
	for (int i = 0; i < n-1; i++) {
		next_y = next_y;
		next_x = next_x-1;
		map[next_y][next_x] = ++present;
		printf("아래쪽 채우기 %d%d", next_y, next_x);
		printf("%d\n", map[next_y][next_x]);
	}
	// 왼쪽 채우기 
	for (int i = 0; i < n-2; i++) {
		next_y = next_y - 1;
		next_x = next_x;
		map[next_y][next_x] = ++present;
		printf("왼쪽 채우기 %d%d", next_y, next_x);
		printf("%d\n", map[next_y][next_x]);
	}
	
	int next = n - 2;
	if (next > 0) {
		start_x++;
		start_y++;
		insert_edge(map, next);
	}
	if (next <= 0) {
		return;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	insert_edge(map, n);
	for (int y = 0; y < n; y++) {
		printf("\n");
		for (int x = 0; x < n; x++) {
			printf("%d ", map[y][x]);
		}
	}
	return 0;
}
