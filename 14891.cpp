/* 
** BOJ 14891
** 문제 유형 : 시뮬레이션 
** 문제 제목 : 톱니바퀴 
** https://www.acmicpc.net/problem/14891
*/

#include <iostream>
#include <queue>
#include <utility>
#include <memory.h> 

using namespace std;

int wheel_info[4][8] = {0}; // 톱니 바퀴 정보를 저장할 배열 0으로 초기화
queue <pair<int,int> > q; // 움직일 target 바퀴와 방향 (시계, 반시계)을 저장

void move_left(int);
void move_right(int);
void move_wheel(int, int);

bool visited[4] = {false}; // 톱니바퀴를 여러번 돌리지 않기 위한 플래그 배열 

const int wheel = 4; // 톱니 바퀴는 4개
const int node = 8; // 각 톱니 바퀴의 노드는 8개
 
int main () {
	int score; // 결과 저장용 변수
	int cnt; // 움직일 횟수 저장용 변수 
	int target; // 움직일 톱니바퀴 
	int direction; // 방향 
	
	// 입력
	for (int j = 0; j < wheel; j++) {
		for (int i = 0; i < node; i++) {
			scanf("%1d", &wheel_info[j][i]);
		}
	}
	scanf("%d", &cnt);
	for (int i = 0; i < cnt; i++) {	
		
		scanf("%d %d", &target, &direction);
		q.push(make_pair(target, direction));
	}
	// 로직	
	while(q.empty() == false) { // 큐가 emtpy일때까지 톱니바퀴를 돌린다. 
		int target = q.front().first -1;
		int direction = q.front().second;
		q.pop();
		move_wheel(target, direction);
		memset(visited, false, sizeof(visited)); // visited 배열을 false로 다시 초기화. 
	}
	// 출력
	score = wheel_info[0][0] + wheel_info[1][0] * 2 + wheel_info[2][0] * 4 + wheel_info[3][0] * 8;
	printf("%d", score);
	return 0 ;
}

// 반시계 이동 : 톱니바퀴를 왼쪽으로 움직인다. 
void move_unclock(int target) {
	int temp = wheel_info[target][0];
	for (int i=0; i<7; i++) {
		wheel_info[target][i] = wheel_info[target][i+1];		
	}
	wheel_info[target][7] = temp;
}

// 시계 이동 : 톱니바퀴를 오른쪽으로 움직인다. 
void move_clock(int target) {
	int temp = wheel_info[target][7];
	for (int i=7; i>0; i--) {	
		wheel_info[target][i] = wheel_info[target][i-1];
	}
	wheel_info[target][0] = temp;
}

void move_wheel(int target, int direction) {				
	// 왼쪽과 오른쪽을 움직일지 결정하는 플래그 
	bool move_left = false;
	bool move_right = false; 
	// left와 right 저장용
	int left = target - 1;
	int right = target + 1; 
	// 움직이려는 톱니 바퀴의 왼쪽과 비교	
	if (wheel_info[left][2] != wheel_info[target][6] && left >= 0) {
		move_left = true; 
	}
	// 움직이려는 톱니 바퀴의 오른쪽과 비교 
	if (wheel_info[target][2] != wheel_info[right][6] && right <= 3) {
		move_right = true;
	}
	// 중앙에 있는 톱니 바퀴를 움직인다. 
	if (direction == 1) {
		move_clock(target);	
	} else {
		move_unclock(target);	
	}

	visited[target] = true;
	// 왼쪽을 움직인다. 
	if (move_left == true && visited[left] == false) {
		move_wheel(left, direction * -1);	
	}
	// 오른쪽을 움직인다.
	if (move_right == true && visited[right] == false) {
		move_wheel(right, direction * -1);
	}
}
/*
생각해보기
1. 최초 문제를 읽었을 때, 톱니바퀴들이 연쇄적으로 움직일 수 있다는 사실을 놓쳤다.
2. 하나의 톱니바퀴가 움직일때, 톱니바퀴들이 움직이는 행위는 모두 동시에 일어난다. 
3. 배열에 요소들을 밀어내거나 댕겨오는 로직을 외울 필요가 있다. 
4. 루프를 돌때 초기화할 배열이나 변수들이 없는지 항상 생각한다. 
*/
