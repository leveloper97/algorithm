/* 
** BOJ 17135
** 문제 유형 : 조합 및 시뮬레이션 
** 문제 제목 : 캐슬 디펜스 
** https://www.acmicpc.net/problem/17135
*/

#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include <cmath>

using namespace std;

int MAX = 15;
int n, m, r; //n은 행 m은 열, r은 공격 범위 
int map[15][15];
int temp[15][15] = {0};
int temp_origin[15][15] = {0};
bool visited[15][15] = {false};
int enemy_cnt = 0;
int enemy_cnt_origin = 0;
//vector <pair<int, int> > archer;
struct archer {
   int one = 0;
   int two = 0;
   int three = 0;
};
vector <archer> archer_list;
int archers[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
bool selected[15];
void make_union(int, int);

void attack_enemy(int, int, int);
void enemy_down();
bool check_enemy(int, int);
void cal_max(struct archer);
vector <pair<int, int> > kill_list;
int kill_cnt = 0;
void recover_origin();

int main() {
   int answer = 0;
   // 1. 입력을 받는다.
   scanf("%d%d%d", &n, &m, &r);
   for (int j = 0; j < n; j++) {
      for (int i = 0; i < m; i++) {
         scanf("%d", &map[j][i]);
         if (map[j][i] == 1) {
            temp[j][i] = 1;
            temp_origin[j][i]= 1;
            enemy_cnt++;
            enemy_cnt_origin++;
         }
      }
   }
   // 2. 배치할 궁수의 조합을 만든다.
   make_union(0, 0);
   // 3. 궁수 조합 리스트들을 반복하면서 최대를 뽑아낸다.
   while(archer_list.empty() == false) {
		recover_origin();
	    struct archer a = archer_list.back();
		archer_list.pop_back();
		cal_max(a);
		printf("%d %d %d %d\n", a.one, a.two, a.three, kill_cnt);
		if (kill_cnt > answer) {
			answer = kill_cnt;
      	}
   }
   
   printf("%d", answer);
    
   return 0;
}

void recover_origin() {
	for (int y = 0; y < n; y++) {
      for (int x = 0; x < m; x++) {
         map[y][x] = temp_origin[y][x];
         temp[y][x] = temp_origin[y][x];
      }
   	}
    kill_cnt = 0;
	enemy_cnt = enemy_cnt_origin;
}

void cal_max(struct archer a) {
   int first = a.one;
   // 2번 녀석
   int second = a.two;
   // 3번 녀석 
   int third = a.three;
   // n번 만큼 턴을 진행한다. 
   for (int i = 0; i < n; i++) {
//   		printf("남은 적의 수 : %d\n", enemy_cnt);
   		if (enemy_cnt == 0) { // 적이 모두 전사했다. 
   			printf("적이 모두 전사\n", first, second, third);
			   break;
		} else {
//			printf("보이는 적이 잇다. 공격하라 %d\n", enemy_cnt);
		} 
        attack_enemy(first, second, third);
      	enemy_down();
   }

}

// 궁수가 적을 공격한다. 1 2 3이라면 x가 0, 1, 2이다. 
void attack_enemy(int first, int second, int third) {
//	printf("궁수야 공격해라\n");
//	printf("삼총사의 위치 %d, %d, %d\n", first-1, second-1, third-1);
   bool first_end = false;
   bool second_end = false;
   bool third_end = false;
   // 공격하기전에 적을 찾는다. 
   for (int i = 1; i <= r; i++) {
      first_end = check_enemy(first-1, i);
      if (first_end == true) {
         break;
      }
   }
   for (int i = 1; i <= r; i++) {
      second_end = check_enemy(second-1, i);
      if (second_end == true) {
         break;
      }
   }
   for (int i = 1; i <= r; i++) {
      third_end = check_enemy(third-1, i);
      if (third_end == true) {
         break;
      }
   }
   // 지도상에서 지워준다. 
   while(kill_list.empty() == false) {
      int targetY = kill_list.back().first;
      int targetX = kill_list.back().second;
      kill_list.pop_back();
      if (temp[targetY][targetX] == 1) {
         temp[targetY][targetX] = 0;
         kill_cnt++;
         enemy_cnt--;
//         printf("%d%d", targetY, targetX);
//         printf("현재 킬: %d\n", kill_cnt);
//         printf("남은  킬: %d\n", enemy_cnt);
//        
      }
   }
}
// 해당 좌표부터 거리가 range인 녀석들이 있으면 true를 리턴하고 푸시한다. 
bool check_enemy(int posX, int range) {
	int posY = n;
	for (int y = n-1; y >= 0; y--) {
		for (int x = 0; x < m; x++) {
			if (abs(posY-y)+abs(posX-x) == range) {
				if (map[y][x] != 1) {
					continue;
				}
				kill_list.push_back(make_pair(y, x));
//				printf("거리가 %d인 적을 발견했다. posY: %d, posX: %d\n ", range, y, x);
				return true;
			}
		}
	}
	return false;
}

void enemy_down() {
//	printf("적이 공격한다.\n");
//	printf("현재 적의 상태\n");
//   for (int y = 0; y < n; y++) {
//   	printf("\n");
//      for (int x = 0; x < m; x++) {
//         printf("%d ", map[y][x]);
//      }
//   }
   // 첫 행은 0으로 채운다. 죽이지 못한 적을 빼준다. 
   for (int i = 0; i < m; i++) {
	  	if (temp[n-1][i] == 1) {
//	  		printf("남은 적이 있다!!!\n");
		    enemy_cnt--;
		}
      map[0][i] = 0;
   }
   // 2번째부째 n번째 행까지 내린다. 
   for (int y = 1; y < n; y++) {
      for (int x = 0; x < m; x++) {
         map[y][x] = temp[y-1][x];
      }
   }

   // temp를 갱신한다.
   for (int y = 0; y < n; y++) {
      for (int x = 0; x < m; x++) {
         temp[y][x] = map[y][x];   
      } 
   }
//   printf("\n적이 내려왔다");
//   for (int y = 0; y < n; y++) {
//   	printf("\n");
//      for (int x = 0; x < m; x++) {
//         printf("%d ", map[y][x]);
//      }
//   }
}
void make_union(int idx, int cnt) {
   if (cnt == 3) {
      struct archer temp;
      for (int i =0; i < m; i++) {
         if (selected[i] == true) {
            if (temp.one == 0) {
               temp.one = archers[i];
            } else if (temp.two == 0) {
               temp.two = archers[i];
            } else if (temp.three == 0) {
               temp.three = archers[i];
            } else {
               break;
            }
         }
      }
      archer_list.push_back(temp);
//      printf("%d %d %d\n", temp.one, temp.two, temp.three);
      return;
   }
   for (int i = idx; i < m; i++) {
      if (selected[i] == true)
         continue;
      selected[i] = true;
      make_union(i, cnt+1);
      selected[i] = false;
   }
}

 
