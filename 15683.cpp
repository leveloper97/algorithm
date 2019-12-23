/* 
** BOJ 15683
** 문제 유형 : 시뮬레이션 
** 문제 제목 : 감시 
** https://www.acmicpc.net/problem/15683
*/

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;
int result;
int n, m; // 사무실 크기 
int k; // CCTV 개수 
queue <pair<int, int> > cctv; //cctv 저장용
int map[8][8]; // 맵 배열 
bool visited[8][8] = {false}; // 방문 확인 배열 
void search(); // 분기용 함수 
int bfs(int, int, int); //탐색 후 
int go_toward(int, int, int); //실질적인 탐색 
void check_visited(int, int, int); // 방문처리 

int main () {
   // 입력 
   scanf("%d%d", &n, &m);
   result = n * m;
   for (int y = 0; y < n; y++) {
      for (int x = 0; x < m; x++) {
         scanf("%d", &map[y][x]);
         if (map[y][x] != 0 && map[y][x] != 6) {
            cctv.push(make_pair(y, x));
            result--;
         }
         if (map[y][x] == 6) {
            result--;
         }
      }
   }
   // 로직 
   search();
   // 결과 
   printf("%d", result);
   return 0;
}

void search() {
   while(cctv.empty() == false) { 
      int x = cctv.front().second;
      int y = cctv.front().first;
      cctv.pop();
      if (map[y][x] == 1) { // 1번 cctv (동, 서, 남, 북) 
         result -= bfs(1, y, x);
       //  printf("result 감소, 1이라서:%d\n", result);
      } else if (map[y][x] == 2) { // 2번 cctv (남북, 동서) 
         result -= bfs(2, y, x);
       //  printf("result 감소, 2이라서:%d\n", result);
      } else if (map[y][x] == 3) { // 3번 cctv (북동, 동남, 남서, 서북) 
         result -= bfs(3, y, x);
    //     printf("result 감소, 3이라서:%d\n", result);
      } else if (map[y][x] == 4) { // 4번 cctv (북동서, 북동남, 동남서, 서남북) 
         result -= bfs(4, y, x);
       //  printf("result 감소, 4이라서:%d\n", result);
      } else if (map[y][x] == 5) { // 5번 cctv (동서남북) 
         result -= bfs(5, y, x);
      //   printf("result 감소, 5이라서:%d\n", result);
      }
   }   
}
// 너비 탐색 후 가장 큰 놈을 리턴한다. 
int bfs(int index, int y, int x) {
//   printf("검색할 y: %d, 검색할 x: %d\n", y ,x);
   int max = 0;
//   int visited_x, visited_y, direction;
	int direction = 0; 
   
   if (index == 1) {
      for (int i = 1; i < 5; i++) {
//         printf("%d 탐색 시작\n", index);
         int temp = go_toward(i, y, x);
         if (max < temp) {
            max = temp;
            direction = i;
         }
      }
      if (max != 0 && direction != 0) { // 방문 처리 
      	check_visited(direction, y, x);
      }
   } else if (index == 2) {
//      printf("%d 탐색 시작\n", index);
      int temp = go_toward(1, y, x) + go_toward(3, y, x);
      int temp2 = go_toward(2, y, x) + go_toward(4, y, x);
      if (temp < temp2) {
         max = temp2;
         check_visited(2, y, x); 
         check_visited(4, y, x);
         direction = 1;
      } else {
         max = temp;
         check_visited(1, y, x);
         check_visited(3, y, x);
         direction = 2;
      }
      if (max != 0 && direction != 0) { // 방문 처리 
	  	if (direction == 1) {
	  		check_visited(2, y, x);
	  		check_visited(4, y, x);
		} else if (direction == 2) {
			check_visited(1, y, x);
	  		check_visited(3, y, x);
		}       
      }
   } else if (index == 3) {
      int temp = go_toward(1, y, x) + go_toward(2, y, x);
      if (temp > max) {
      	max = temp;
        direction = 1;
      }
      int temp2 = go_toward(2, y, x) + go_toward(3, y, x);
      if (temp2 > max) {
         max = temp2;
         direction = 2;
      }
      int temp3 = go_toward(3, y, x) + go_toward(4, y, x);
      if (temp2 > max) {
         max = temp3;
         direction = 3;
      }
      int temp4 = go_toward(4, y, x) + go_toward(1, y, x);
      if (temp2 > max) {
         max = temp4;
         direction = 4;
      }
	  if (max != 0 && direction != 0) { // 방문 처리 
	  	if (direction == 1) {
	  		check_visited(1, y, x);
			check_visited(2, y, x);
		} else if(direction == 2) {
			check_visited(2, y, x);
			check_visited(3, y, x);
		} else if(direction == 3) {
			check_visited(3, y, x);
			check_visited(4, y, x);
		} else if(direction == 4) {
			check_visited(4, y, x);
			check_visited(1, y, x);
		}
	  }   
   } else if (index == 4) {
    //  printf("%d 탐색 시작\n", index);
      int temp = go_toward(1, y, x) + go_toward(2, y, x) + go_toward(3, y, x);
      if (temp > max) {
      	max = temp;
      	direction = 1;
	  }
      int temp2 = go_toward(2, y, x) + go_toward(3, y, x) + go_toward(4, y, x);
      if (temp2 > max) {
         max = temp2;
         direction = 2;
      }
      int temp3 = go_toward(3, y, x) + go_toward(4, y, x) + go_toward(1, y, x);
      if (temp2 > max) {
      	direction = 3;
         max = temp3;
      }
      int temp4 = go_toward(4, y, x) + go_toward(1, y, x) + go_toward(2, y, x);
      if (temp2 > max) {
         max = temp4;
         direction = 4;
      }
	  if (max != 0 && direction != 0) { // 방문 처리 
	  	if (direction == 1) {
	  		check_visited(1, y, x);
			check_visited(2, y, x);
			check_visited(3, y, x);
		} else if(direction == 2) {
			check_visited(2, y, x);
			check_visited(3, y, x);
			check_visited(4, y, x);
		} else if(direction == 3) {
			check_visited(3, y, x);
			check_visited(4, y, x);
			check_visited(1, y, x);
		} else if(direction == 4) {
			check_visited(4, y, x);
			check_visited(1, y, x);
			check_visited(2, y, x);
		}
	  }   
	        
   } else if (index == 5) {
     // printf("%d 탐색 시작\n", index);
      max = go_toward(1, y, x) + go_toward(2, y, x) + go_toward(3, y, x) + go_toward(4, y, x);
      check_visited(1, y, x);
      check_visited(2, y, x);
      check_visited(3, y, x);
      check_visited(4, y, x);
   }
   
   return max;
}
//  
int go_toward(int dir, int y, int x) {
   int temp = 0;
   if (dir == 1) { // 위쪽 쭉 탐색 
//      printf("%d 시작", dir);
      while (y - 1 >= 0) { 
         if (map[y-1][x] == 6) {
            break;
         }
         if (map[y-1][x] == 0 && visited[y-1][x] == false) {
            temp++; 
         }
         y--;
      }
   } else if (dir == 2) { // 오른쪽 쭉 탐색
//   printf("%d 시작", dir);
      while (x + 1 <= m - 1) { // 인덱싱 초과에 따른 탈출
         if (map[y][x+1] == 6) { // 벽을 만남에 따른 탈출 
            break;
         }
         if (map[y][x+1] == 0 && visited[y][x+1] == false) {
            temp++;   
         }
         x++;
      }
   } else if (dir == 3) { // 아래쪽 쭉 탐색
//   printf("%d 시작", dir);
      while (y + 1 <= n - 1) { 
         if (map[y+1][x] == 6) {
            break;
         }
         if (map[y+1][x] == 0 && visited[y+1][x] == false) {
//            visited[y+1][x] = true;
            temp++;   
         }
         y++;
      }
   } else if (dir == 4) { // 왼쪽 쭉 탐색
 //  printf("%d 시작", dir);
      while (x - 1 >= 0) { // 인덱싱 초과에 따른 탈출
         if (map[y][x-1] == 6) { // 벽을 만남에 따른 탈출 
            break;
         }
         if (map[y][x-1] == 0 && visited[y][x-1] == false) {
//            visited[y][x-1] = true;
            temp++;   
         }
         x--;
      }   
   }
   //printf("리턴,%d\n", temp);
   return temp;
}

void check_visited(int dir, int y, int x) {
   int temp = 0;
   if (dir == 1) { // 위쪽 쭉 탐색 

      while (y - 1 >= 0) { 
         if (map[y-1][x] == 6) {
            break;
         }
         if (map[y-1][x] == 0 && visited[y-1][x] == false) {
            visited[y-1][x] = true;  
         }
         y--;
      }
   } else if (dir == 2) { // 오른쪽 쭉 탐색
      while (x + 1 <= m - 1) { // 인덱싱 초과에 따른 탈출
         if (map[y][x+1] == 6) { // 벽을 만남에 따른 탈출 
            break;
         }
         if (map[y][x+1] == 0 && visited[y][x+1] == false) {
            visited[y][x+1] = true;
            
         }
         x++;
      }
   } else if (dir == 3) { // 아래쪽 쭉 탐색
      while (y + 1 <= n - 1) { 
         if (map[y+1][x] == 6) {
            break;
         }
         if (map[y+1][x] == 0 && visited[y+1][x] == false) {
            visited[y+1][x] = true;
            
         }
         y++;
      }
   } else if (dir == 4) { // 왼쪽 쭉 탐색 
      while (x - 1 >= 0) { // 인덱싱 초과에 따른 탈출
         if (map[y][x-1] == 6) { // 벽을 만남에 따른 탈출 
            break;
         }
         if (map[y][x-1] == 0 && visited[y][x-1] == false) {
            visited[y][x-1] = true;
         }
         x--;
      }   
   }
   
}
/*
생각해보기
1. 최초에 visited 처리를 bfs할때마다 해줘서 틀렸다. 
2. 실질적으로 방문한 곳에만 visited를 true를 넣어야한다. 
3. 내가 짠 코드는 비지트드 처리를 매번해야되서 번거롭다... 
*/
