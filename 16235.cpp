/*
** BOJ 16235
** 문제 유형 : 시뮬레이션 
** 문제 제목 : 나무 재테크
** https://www.acmicpc.net/problem/14501
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 10; // n의 최대는 10이다. 
int map[MAX][MAX] = {0}; // 현재 양분의 상태 
int winter_food[MAX][MAX] = {0}; // 매 겨울마다 추가되는 양분 
int n; // 사재기한 땅의 행, 열 
int m; // 나무의 개수 
int k; // k년 후 
int tree_add; // 추가된 나무 개수 
int answer = 0;

struct Tree {
	int y;
	int x;
	int year;
	bool death = false; 
};
struct Tree tree[1000]; // 1000개의 구조체 배열을 생성한다. 
void do_spring();
void do_summer();
void do_fall();
void do_winter();
void make_tree(int, int); 

int main() {
	
	scanf("%d%d%d", &n, &m, &k);
	// 양분의 정보(5)를 입력한다. 
	answer = m;
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			map[y][x] = 5;
		}
	}
	// 겨울마다 추가할 양분을 입력받는다. 
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			scanf("%d", &winter_food[y][x]);
		}
	}
	
	// 심은 나무의 정보를 입력 받는다. 
//	printf("나무 정보를 입력받습니다. \n");
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &tree[i].y, &tree[i].x, &tree[i].year);
	}
	// 나무들을 나이를 토대로 정렬한다. (버블 정렬) 
//	printf("나이순으로 정렬합니다\n");
	for (int i = 0; i < m; i++) { // i번째를 찾는다. 
		for (int j = 1; j < m - i; j++) {
			int index;
			// 옆에 있는 놈이 더 어리면 temp를 바꾼다. 
			if (tree[j-1].year > tree[j].year) {
//				printf("옆에 놈이 더 어리다\n");
				Tree temp = tree[j-1];
				tree[j-1] = tree[j];
				tree[j] = temp;
			}
		}
	}
	
//	for (int i = 0; i < m; i++) {
//		printf("%d%d%d", tree[i].y, tree[i].x, tree[i].year);
//	}
	
	// k년만큼 사계절을 보낸다. 
	for (int i = 0 ; i < k; i++) {
		do_spring();
		do_summer();
		do_fall();
		do_winter();	
//		printf("%d년후 나무의 개수 %d\n", i+1, answer);
	}
	
	if (answer < 0) {
		answer = 0;
	}
	printf("%d", answer);		
		
	return 0;
}
// 봄, 자신의 나이만큼 양분을 먹고 나이를 먹는다. 하나의 칸에 여러개의 나무가 있으면 어린 나무부터 양분을 먹는다. 양분이 부족하면 즉사한다. 
void do_spring() {
//	printf("봄을 시작합니다.\n");
	for (int i = 0; i < m; i++) {
		if (tree[i].death == true) {
//			printf("죽은 나무입니다. 양분를 먹지 않습니다.\n");
			break; 
		}
		int food = map[tree[i].y][tree[i].x]; // 현재 나무가 있는 곳의 양분의 양
//	printf("현재 남은 양분 : %d\n", food);
		if (food - tree[i].year < 0) {
//			printf("나무가 죽었습니다.\n");
			answer--;
			tree[i].death = true;
		} else {
//			printf("양분을 먹었습니다. \n");
			food -= tree[i].year; // 나무의 나이만큼 양분을 처묵
			tree[i].year++; // 나이 한살 처묵 	
		}
		map[tree[i].y][tree[i].x] = food; // 남은 양분 맵에 업데이트 
	}
}
// 여름, 죽은 나무가 양분으로 변한다. 죽은 나무의 나이를 2로 나눈 값을 양분을 더한다. (소수점은 버린다.) 
void do_summer() {
//	printf("여름을 시작합니다.\n");
	for (int i = 0; i < m; i++) {
		if (tree[i].death == true) {
//			printf("죽은 나무를 양분으로 바꿉니다.\n");
			int food = tree[i].year / 2;
			map[tree[i].y][tree[i].x] += food;
		}
	}
}
// 가을, 나무의 나이가 5의 배수이면 인접한 8개의 칸에 번식한다. 땅을 벗어나면 나무가 생기지 않는다. 
void do_fall() {
//	printf("가을을 시작합니다.\n");
	tree_add = 0;
	for (int i = 0; i < m; i++) {
		if (tree[i].year % 5 == 0 && tree[i].death == false) {
//			printf("나무의 나이가 5의 배수이다. 번식한다\n");
			int y = tree[i].y;
			int x = tree[i].x;
//			printf("번식할 녀석의 y 좌표 %d\n", y);
//			printf("번식할 녀석의 x 좌표 %d\n", x);
			if (0 < y-1 && y-1 < n + 1 && 0 < x-1 && x-1 < n + 1) {
//				printf("번식 성공 %d%d\n", y-1, x-1);
				tree_add++;
				make_tree(y-1, x-1);	
			}
			if (0 < y-1 && y-1 < n + 1 && 0 < x && x < n + 1) {
//				printf("번식 성공 %d%d\n", y-1, x);
				tree_add++;
				make_tree(y-1, x);	
			}
			if (0 < y-1 && y-1< n + 1 && 0 < x+1 && x+1< n + 1) {
//				printf("번식 성공 %d%d\n", y-1, x+1);
				tree_add++;
				make_tree(y-1, x+1);	
				
			}
			if (0 < y && y < n + 1 && 0 < x-1 && x-1 < n + 1) {
//				printf("번식 성공 %d%d\n", y, x-1);
				tree_add++;
				make_tree(y, x-1);	
				
			}
			if (0 < y && y < n + 1 && 0 < x+1 && x+1 < n + 1) {
//				printf("번식 성공 %d%d\n", y, x+1);
				tree_add++;
				make_tree(y, x+1);	
				
			}
			if (0 < y+1 && y+1 < n + 1 && 0 < x-1 && x-1 < n + 1) {
//				printf("번식 성공 %d%d\n", y+1, x-1);
				tree_add++;
				make_tree(y+1, x-1);	
				
			}
			if (0 < y+1 && y+1 < n + 1 && 0 < x && x < n + 1) {
//				printf("번식 성공 %d%d\n", y+1, x);
				tree_add++;
				make_tree(y+1, x);	
				
			}
			if (0 < y+1 && y+1 < n + 1 && 0 < x+1 && x+1< n + 1) {
//				printf("번식 성공 %d%d\n", y+1, x+1);
				tree_add++;
				make_tree(y+1, x+1);		
			} else {
//				printf("번식 실패이유 : %d%d", y+1, x+1);
			}
			 
		}
	}
	m += tree_add;
	// 번식한 기념으로 나이순 정렬을 한다. 
	for (int i = 0; i < m; i++) { // i번째를 찾는다. 
		for (int j = 1; j < m - i; j++) {
			int index;
			// 옆에 있는 놈이 더 어리면 temp를 바꾼다. 
			if (tree[j-1].year > tree[j].year) {
//				/printf("옆에 놈이 더 어리다\n");
				Tree temp = tree[j-1];
				tree[j-1] = tree[j];
				tree[j] = temp;
			}
		}
	}
}
// 겨울, 로봇이 땅을 돌아다니면서 양분을 추가한다. 입력으로 주어짐.. 
void do_winter() {
//	printf("겨울을 시작합니다.\n");
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			map[y][x] += winter_food[y][x];
		}
	}
}
// 인자에서 인접한 8개의 칸에 나이가 1인 나무를 생성한다. 
void make_tree(int y, int x) {
	// 나무 추가 
	tree[m -1 + tree_add].y = y;
	tree[m -1 + tree_add].x = x;
	tree[m -1 + tree_add].year = 1;
	tree[m -1 + tree_add].death = false;
	
	answer++;	
}
/*
다시생각해보기
1. 일반적인 이차원 배열의 인덱싱은 0,0부터 시작하는데,
이경우는 1부터 시작하기 때문에 이러한 처리에 많은 어려움이 있엇다.
2. 관리해줘야할 프로퍼티들이 많아 구조체를 쓰게 되었다.  
 
*/
