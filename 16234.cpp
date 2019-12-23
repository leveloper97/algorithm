/* 
** BOJ 16234
** 문제 유형 : BFS
** 문제 제목 : 인구 이동 
** https://www.acmicpc.net/problem/16234
*/

#include <iostream>
#include <queue>
#include <cmath>
#include <utility>
#include <memory.h>
using namespace std;
int map[52][52];
int visited[52][52] = {false,};
int N,L,R;
bool is_update = true;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
vector <pair <int, int> > country;
int answer = 0;
void make_union(int, int);
void move_people();
int main(){
    // 입력 
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> L >> R; 
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++)
            cin >> map[y][x];
    }
    while (is_update == true) {
    	is_update = false;
    	memset(visited, false, sizeof(visited));
  		answer++;
    	for (int y = 0; y < N; y++) {
	    	for (int x = 0; x < N; x++) {
	    		if (visited[y][x] == false) {
//	    			cout << "y와 x가 방문안했습니다." << y << x << endl; 
					make_union(y, x);
	    			move_people();
				}		
			}
		}	
	}
    
    cout << answer-1;
}
void make_union(int y, int x) {
	if (y < 0 || y >= N || x < 0 || x >= N) {
		return;
	}
	// 나라 배열들을 돌면서 연합을 구성한다.
//	cout << y << x << endl; 
	visited[y][x] = true;
	
	country.push_back(make_pair(y, x));	
	if (0 <= x && x < N) {
		if (map[y][x+1] != 0) {
			int temp = abs(map[y][x] - map[y][x+1]);
			if (L <= temp && temp <= R && visited[y][x+1] == false) {
//				printf("오른쪽 나라오 ㅏ연합니다.");
	//			country.push_back(make_pair(y, x+1));
	//			visited[y][x+1] = true;
				make_union(y, x+1);
				is_update = true;
			}	
		}
		if (map[y][x-1] != 0) {
			int temp = abs(map[y][x] - map[y][x-1]);
			if (L <= temp && temp <= R && visited[y][x-1] == false) {
//				printf("왼쪽 나라오 ㅏ연합니다.");
	//			country.push_back(make_pair(y, x+1));
	//			visited[y][x+1] = true;
				make_union(y, x-1);
				is_update = true;
			}	
		}
		
	}
		
	if (0 <= y && y < N) {
		if (map[y+1][x] != 0) {
			int temp = abs(map[y][x] - map[y+1][x]);
			if (L <= temp && temp <= R && visited[y+1][x] == false) {
//				printf("아래쪽 나라연합니다.");
	//			country.push_back(make_pair(y+1, x));
	//			visited[y+1][x] = true;
				make_union(y+1, x);
				is_update = true;
			}	
		}
		if (map[y-1][x] != 0) {
			int temp = abs(map[y][x] - map[y-1][x]);
			if (L <= temp && temp <= R && visited[y-1][x] == false) {
//				printf("위쪽 나라연합니다.");
	//			country.push_back(make_pair(y+1, x));
	//			visited[y+1][x] = true;
				make_union(y-1, x);
				is_update = true;
			}	
		}
	}
} 
void move_people() {
	int sum = 0;
	int size = country.size();
//	cout << "연합 사이즈: " << size << endl; 
	if (size == 1) {
//		cout << "연합 실패 리턴합니다" << endl; 
		country.pop_back();
		return; 
	}

//	printf("size%d", size);
	for (int i = 0; i < size; i++) {
		sum += map[country[i].first][country[i].second];
	}
	int new_people = sum / size;
	while(country.empty() == false) {
		int y = country.back().first;
		int x = country.back().second;
		map[y][x] = new_people;
		country.pop_back();
	}

}
    


