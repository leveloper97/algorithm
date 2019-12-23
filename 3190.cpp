#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;

int answer = 0;
int n; // 보드의 크기 
int apple_cnt; // 사과의 크기
int command_cnt; // 명령의 크 
int map[100][100] = {0, }; // 사과 정보를 가지고 있는 배열
queue <pair <int, int> > snake; // 뱀 정보를 가지고 있는 큐 
int seconds = 0;
char direction;
queue <pair <int, int> > time;
void start();
int dy[4] = {0, 1, 0, -1}; // 최초 오른쪽 아래쪽 왼쪽 위쪽
int dx[4] = {1, 0, -1, 0};
int index = 0;
int total_sec = 0;
// x초가 끝난뒤 L 왼쪽 90, D 오른쪽 90도 
int main() {
   scanf("%d", &n);
   scanf("%d", &apple_cnt);
   int apple_y, apple_x;
   for (int i = 0; i < apple_cnt; i++) {
      scanf("%d %d", &apple_y, &apple_x);
      map[apple_y-1][apple_x-1] = 1;
   }
   map[0][0] = 0;
   scanf("%d", &command_cnt);
   for (int i = 0; i < command_cnt; i++) { 
      cin >> seconds;
      cin >> direction;
//      printf("%d %c", seconds, direction);
      time.push(make_pair(seconds, direction));
   }
   
//   for (int i = 0 ; i  < command_cnt; i++) {
//      printf("%d", time[i].first);
//   } 
	snake.push(make_pair(0,0)); // 뱀은 00부터 시작. 
   start();
   printf("%d", total_sec);
   return 0;
}
void start() {
   int change_time = 0;
   char change_dir;
   if (time.empty() == false) {
      change_time = time.front().first;
      change_dir = time.front().second;
      time.pop();
   }
   int y = 0;
   int x = 0;
   
   while(1) {
		total_sec++; // 초 증가 
		
		y = y + dy[index];
        x = x + dx[index];
//        printf("현재 뱀머리 의 좌표: %d %d\n", y, x); 
//		printf("뱀의 정보%d\n", map[y][x]);	  
		// 진행하는 방향이 종료 조건인지 검사한다.
		if (0 > y || y >= n || 0 > x || x >=n) {
//			printf("게임 오버\n");
			return;
		}
		if (map[y][x] == 2) {
//			printf("나와 부딪혔다.%d%d\n", y, x);
			return;
		}
		
		// 진행하는 방향으로 뱀을 확장한다.
		snake.push(make_pair(y, x));
		// 사과가 있는지 검사한다.
        if (map[y][x] == 1) { 
//        	printf("사과를 먹었다%d%d.\n", y+1, x+1); 
        } else { // 사과가 없을때 
           map[snake.front().first][snake.front().second] = 0;
		   snake.pop(); // 뱀 꼬리 제거   
        }
        map[y][x] = 2;

		// 시간이 방향 바꾸는 동작이면 바꿔준다.
	    if (total_sec == change_time) {
	  		if (change_dir == 'D') {
//	  			printf("90도 시계 회전\n"); 
				index = (index+1) % 4;
		  	} else if (change_dir == 'L') {
//		  		printf("90도 반시계 회\n");
				index = (index+3) % 4;
		  	}
			if (time.empty() == false) {
			    change_time = time.front().first;
  				change_dir = time.front().second;
  				time.pop();
  			}
		}  
    }
}

