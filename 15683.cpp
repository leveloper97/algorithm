/* 
** BOJ 15683
** ���� ���� : �ùķ��̼� 
** ���� ���� : ���� 
** https://www.acmicpc.net/problem/15683
*/

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;
int result;
int n, m; // �繫�� ũ�� 
int k; // CCTV ���� 
queue <pair<int, int> > cctv; //cctv �����
int map[8][8]; // �� �迭 
bool visited[8][8] = {false}; // �湮 Ȯ�� �迭 
void search(); // �б�� �Լ� 
int bfs(int, int, int); //Ž�� �� 
int go_toward(int, int, int); //�������� Ž�� 
void check_visited(int, int, int); // �湮ó�� 

int main () {
   // �Է� 
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
   // ���� 
   search();
   // ��� 
   printf("%d", result);
   return 0;
}

void search() {
   while(cctv.empty() == false) { 
      int x = cctv.front().second;
      int y = cctv.front().first;
      cctv.pop();
      if (map[y][x] == 1) { // 1�� cctv (��, ��, ��, ��) 
         result -= bfs(1, y, x);
       //  printf("result ����, 1�̶�:%d\n", result);
      } else if (map[y][x] == 2) { // 2�� cctv (����, ����) 
         result -= bfs(2, y, x);
       //  printf("result ����, 2�̶�:%d\n", result);
      } else if (map[y][x] == 3) { // 3�� cctv (�ϵ�, ����, ����, ����) 
         result -= bfs(3, y, x);
    //     printf("result ����, 3�̶�:%d\n", result);
      } else if (map[y][x] == 4) { // 4�� cctv (�ϵ���, �ϵ���, ������, ������) 
         result -= bfs(4, y, x);
       //  printf("result ����, 4�̶�:%d\n", result);
      } else if (map[y][x] == 5) { // 5�� cctv (��������) 
         result -= bfs(5, y, x);
      //   printf("result ����, 5�̶�:%d\n", result);
      }
   }   
}
// �ʺ� Ž�� �� ���� ū ���� �����Ѵ�. 
int bfs(int index, int y, int x) {
//   printf("�˻��� y: %d, �˻��� x: %d\n", y ,x);
   int max = 0;
//   int visited_x, visited_y, direction;
	int direction = 0; 
   
   if (index == 1) {
      for (int i = 1; i < 5; i++) {
//         printf("%d Ž�� ����\n", index);
         int temp = go_toward(i, y, x);
         if (max < temp) {
            max = temp;
            direction = i;
         }
      }
      if (max != 0 && direction != 0) { // �湮 ó�� 
      	check_visited(direction, y, x);
      }
   } else if (index == 2) {
//      printf("%d Ž�� ����\n", index);
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
      if (max != 0 && direction != 0) { // �湮 ó�� 
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
	  if (max != 0 && direction != 0) { // �湮 ó�� 
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
    //  printf("%d Ž�� ����\n", index);
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
	  if (max != 0 && direction != 0) { // �湮 ó�� 
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
     // printf("%d Ž�� ����\n", index);
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
   if (dir == 1) { // ���� �� Ž�� 
//      printf("%d ����", dir);
      while (y - 1 >= 0) { 
         if (map[y-1][x] == 6) {
            break;
         }
         if (map[y-1][x] == 0 && visited[y-1][x] == false) {
            temp++; 
         }
         y--;
      }
   } else if (dir == 2) { // ������ �� Ž��
//   printf("%d ����", dir);
      while (x + 1 <= m - 1) { // �ε��� �ʰ��� ���� Ż��
         if (map[y][x+1] == 6) { // ���� ������ ���� Ż�� 
            break;
         }
         if (map[y][x+1] == 0 && visited[y][x+1] == false) {
            temp++;   
         }
         x++;
      }
   } else if (dir == 3) { // �Ʒ��� �� Ž��
//   printf("%d ����", dir);
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
   } else if (dir == 4) { // ���� �� Ž��
 //  printf("%d ����", dir);
      while (x - 1 >= 0) { // �ε��� �ʰ��� ���� Ż��
         if (map[y][x-1] == 6) { // ���� ������ ���� Ż�� 
            break;
         }
         if (map[y][x-1] == 0 && visited[y][x-1] == false) {
//            visited[y][x-1] = true;
            temp++;   
         }
         x--;
      }   
   }
   //printf("����,%d\n", temp);
   return temp;
}

void check_visited(int dir, int y, int x) {
   int temp = 0;
   if (dir == 1) { // ���� �� Ž�� 

      while (y - 1 >= 0) { 
         if (map[y-1][x] == 6) {
            break;
         }
         if (map[y-1][x] == 0 && visited[y-1][x] == false) {
            visited[y-1][x] = true;  
         }
         y--;
      }
   } else if (dir == 2) { // ������ �� Ž��
      while (x + 1 <= m - 1) { // �ε��� �ʰ��� ���� Ż��
         if (map[y][x+1] == 6) { // ���� ������ ���� Ż�� 
            break;
         }
         if (map[y][x+1] == 0 && visited[y][x+1] == false) {
            visited[y][x+1] = true;
            
         }
         x++;
      }
   } else if (dir == 3) { // �Ʒ��� �� Ž��
      while (y + 1 <= n - 1) { 
         if (map[y+1][x] == 6) {
            break;
         }
         if (map[y+1][x] == 0 && visited[y+1][x] == false) {
            visited[y+1][x] = true;
            
         }
         y++;
      }
   } else if (dir == 4) { // ���� �� Ž�� 
      while (x - 1 >= 0) { // �ε��� �ʰ��� ���� Ż��
         if (map[y][x-1] == 6) { // ���� ������ ���� Ż�� 
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
�����غ���
1. ���ʿ� visited ó���� bfs�Ҷ����� ���༭ Ʋ�ȴ�. 
2. ���������� �湮�� ������ visited�� true�� �־���Ѵ�. 
3. ���� § �ڵ�� ����Ʈ�� ó���� �Ź��ؾߵǼ� ���ŷӴ�... 
*/
