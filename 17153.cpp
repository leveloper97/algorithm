#include <iostream>

const int MAX = 10;
int map[MAX][MAX];
int main() {
	for (int y = 0; y < MAX; y++) {
		for (int x = 0; x < MAX; x++) {
			scnaf("%d", &map[y][x]);
		}
	}
	
	return 0;
}
