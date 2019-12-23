/* 
** BOJ 14499
** 문제 유형 : BFS
** 문제 제목 : 주사위 
** https://www.acmicpc.net/problem/14499
*/

#include <iostream>
#include <queue>

using namespace std;

int dice[6] = {0, }; // 주사위의 상태 
int temp[6] = {0, }; // 복사용 임시 주사위 
int y, x; // 지도 좌표 
int map[20][20] = {0, }; // 지도 
queue <int> q;
int dice_y, dice_x; // 주사위의 좌표 
 
void move_dice(int, int ,int);
int main() {
	scanf("%d%d", &y, &x);
	
	scanf("%d%d", &dice_y, &dice_x);
	int cnt;
	scanf("%d", &cnt);
	// 지도 입력 
//	printf("지도를 입력받는다\n");
	for (int j = 0; j< y; j++) {
		for (int i = 0; i < x; i++) {
			scanf("%d", &map[j][i]);
		}
	}
	// 방향 입력
//	printf("방향를 입력받는다\n");
	int direction;
	for (int i = 0; i < cnt; i++) {
		scanf("%d", &direction);
		q.push(direction);
	} 
	
	// 로직
	while(q.empty() == false) {
		int dir = q.front();
		q.pop();
		if (dir == 1) { // 동쪽 
			move_dice(dice_y, dice_x+1, dir);
		} else if (dir == 2) { // 서 
			move_dice(dice_y, dice_x-1, dir);
		} else if (dir == 3) { // 북 
			move_dice(dice_y-1, dice_x, dir);
		} else if (dir == 4) { // 남 
			move_dice(dice_y+1, dice_x, dir);
		}
	} 
   return 0;
}

void move_dice(int curY, int curX, int dir) {
//	printf("주사위를 (%d, %d)로 이동시킵니다.\n", curY, curX);
//	printf("지도 인덱스 %d%d\n", y, x);
	if (curY < 0 || curY > y-1 || curX < 0 || curX > x -1) {
//		printf("주사위가 이동할 수 없습니다.\n"); 
		return;
	}
	
	// 임시 복사 
	for (int i = 0; i < 6; i++) {
		temp[i] = dice[i]; 
	}
//	printf("임시로 주사위의 값을 복사합니다.\n"); 
	for (int i = 0; i < 6; i++) {
//		 printf("%d\n", temp[i]);
	}
	
	if (dir == 1) {
		dice[0] = temp[3];
		dice[1] = temp[1];		
		dice[2] = temp[0];
		dice[3] = temp[5];
		dice[4] = temp[4]; 
		dice[5] = temp[2];
	} else if(dir == 2) {
		dice[0] = temp[2];		
		dice[1] = temp[1];		
		dice[2] = temp[5];
		dice[3] = temp[0];
		dice[4] = temp[4];		
		dice[5] = temp[3];
	} else if(dir == 3) {
		dice[0] = temp[4];		
		dice[1] = temp[0];
		dice[2] = temp[2];		
		dice[3] = temp[3];		
		dice[4] = temp[5];
		dice[5] = temp[1];
	} else if(dir == 4) {
//		printf("남쪽으로 이동합니다.\n");
		dice[0] = temp[1];		
		dice[1] = temp[5];
		dice[2] = temp[2];		
		dice[3] = temp[3];		
		dice[4] = temp[0];
		dice[5] = temp[4];
	}
	
	if (map[curY][curX] == 0) { // 지도가 0이면 주사위를 지도로 복사 
//		printf("주사위의 값: %d을 지도로 복사합니다.", dice[5]);
		map[curY][curX] = dice[5];
	} else { // 지도가 0이 아니면 칸을 주사위로 복사 칸은 0이된다. 
//		printf("지도의 값: %d을 주사위로 복사합니다.", map[curY][curX]);
		dice[5] = map[curY][curX];
		map[curY][curX] = 0;
	}
	dice_y = curY;
	dice_x = curX;
	// 지도 업데이트
//	printf("회전한 결과입니다");
		for (int i = 0; i < 6; i++) {
//		printf("%d", dice[i]);
	}
	printf("%d\n", dice[0]);
}
/*
생각해보기
주사위들을 굴렸을때 바뀌는 위치들만 넣을라했었는데
temp는 계속 변하기 문에 인덱스가 바뀌지 않는 것들도 바꿔야했다. 
반복문 예외처리 연산자 잘 확인하기./ 
*/

	

