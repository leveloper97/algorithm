/* 
** BOJ 15686
** 문제 유형 : BFS
** 문제 제목 : 치킨 배달 
** https://www.acmicpc.net/problem/15686
*/
/*
단순하게 dfs로 조합을 만들어서 
풀면되지만 시간 초과 때문에 많은 어려움을 겪었다.
 
*/
#include <iostream> 
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

int N, M;
int map[50][50];
bool is_selected[14];

vector <pair <int, int> > ch;
vector <pair <int, int> > home;

void make_union(int, int);
void cal_dist();
int answer = 999999;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	// 입력 
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
			if (map[y][x] == 1) { // 집 
				home.push_back(make_pair(y,x));
			}
			else if(map[y][x] == 2) { // 치킨집 
				ch.push_back(make_pair(y,x));
			}
		}
	}
	make_union(0, 0);
	cout << answer;
	return 0;
}
// cur_num : 현재 치킨 인덱스 , cur_cnt : 현재 선택한 치킨 개숫 
void make_union(int cur_num, int cur_cnt) {
	if (cur_num > ch.size()) { // 인덱싱 예외처리 
		return;
	}
	if (cur_cnt == M) { // 치킨 갯수가 정해지면 계산한다. 
		cal_dist();
	}
	is_selected[cur_num] = true; // 치킨집을 선택한다.
	make_union(cur_num+1, cur_cnt+1); // 조합을 만들 다음 치킨집을 선택한다. 
	// 현재 치킨집을 사용하지 않는다.
	is_selected[cur_num] = false;
	make_union(cur_num +1, cur_cnt); // 현재 치킨집은 사용안할걸로 가정하고 다음 치킨집을 선택한다. 
}
void cal_dist() {
	// 치킨 거리를 계산한다. 
	int sum = 0;
	for (int i = 0; i < home.size(); i++) { // 집주소를 빼넨다. 
		int home_y = home[i].first;
		int home_x = home[i].second;
		int dist = 999999;
		for (int j = 0; j < ch.size(); j++) { // 치킨 주소를 빼넨다. 
			if (is_selected[j] == true) { // 선택 받은 치킨 주소만 거리를 비교한다. 
				int ch_y = ch[j].first;
				int ch_x = ch[j].second;
				int temp_dist = abs(home_y-ch_y) + abs(home_x-ch_x); // 치킨 거리를 계산한다.	
				
				dist = min(temp_dist, dist);
//				cout << "계산된 치킨 거리" << dist << endl;
			}
		}
		sum += dist;
//		cout << "계산된 총 치킨 거리" << sum << endl; 
	}
	if (answer > sum) { // 최소이면 갱신한다. 
		answer = sum;
	}
}
