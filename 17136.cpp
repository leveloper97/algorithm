/* 
** BOJ 17136
** ���� ���� : BFS
** ���� ���� : ������ ���̱� 
** https://www.acmicpc.net/problem/17136
*/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;
const int MAX = 10;
int map[MAX][MAX];
bool visited[MAX][MAX];
int square_cnt[5] = {5, 5, 5, 5, 5};

void dfs(int, int, int, int, int, int, int);
bool check_square(int, int, int);
void check_visited(int, int, int, bool);
int find_range(int, int);
int answer = 100;
int total_cnt = 0; 

vector <pair <int, int> > v;

int main() {
	for (int y = 0; y < MAX; y++) {
		for (int x = 0; x < MAX; x++) {
			scanf("%d", &map[y][x]);
			if (map[y][x] == 1) {
				total_cnt++; // 1�� �� ������ �����Ѵ�. 
				v.push_back(make_pair(y, x));
			}
		}
	}
	if (v.empty() == true) {
		printf("0");
		return 0;
	}	
	dfs(0, 0, 0, 0, 0, 0, 0);
	if (answer == 100) { 
		printf("-1");
		
	} else {
		printf("%d", answer);
	}

	return 0;
}

void dfs(int idx, int use_one, int use_two, int use_three, int use_four, int use_five, int cnt) {
	int use_cnt = use_one + use_two + use_three + use_four + use_five;
	if (answer < use_cnt) {
		//�̹� �ּ��� ��Ȳ�̹Ƿ� �����Ѵ�. 
		return; 
	}
	if (total_cnt == cnt && idx == total_cnt) { // �ϼ�
		if (answer > use_cnt) {
//			printf("%d %d %d %d %d %d \n", idx, use_one, use_two, use_three, use_four, use_five); 
			answer = use_cnt;
		}
		return;
	} 
	
	if (idx+1 > total_cnt) { 
//		printf("������ �ε����� ħ���ߴ�.\n");
		return;
	}
	// �̹� �湮�� �ε����̴�. 
	if (visited[v[idx].first][v[idx].second] == true) {
		// ���� �ε����� ��߽�Ų��.	
		dfs(idx+1, use_one, use_two, use_three, use_four, use_five, cnt);
		return; 
	} 
	
	int go_toward = find_range(v[idx].first, v[idx].second);
//	printf("%d ���� �ֽ��ϴ�\n", go_toward);
	if (go_toward == 1) { // 1*1�� ĥ�� �� �ִ� ��� 
		if (use_one < 5) { 
			check_visited(v[idx].first, v[idx].second, 1, true);	
			dfs(idx + 1, use_one+1, use_two, use_three, use_four, use_five, cnt + 1);
			check_visited(v[idx].first, v[idx].second, 1, false);
		}
	} else if(go_toward == 2) { 
		if (use_two < 5) {
			check_visited(v[idx].first, v[idx].second, 2, true);
			dfs(idx+1, use_one, use_two+1, use_three, use_four, use_five, cnt + 4);
			check_visited(v[idx].first, v[idx].second, 2, false);
		}
		if (use_one < 5) {
			check_visited(v[idx].first, v[idx].second, 1, true);	
			dfs(idx + 1, use_one+1, use_two, use_three, use_four, use_five, cnt + 1);
			check_visited(v[idx].first, v[idx].second, 1, false);
		}
	} else if(go_toward == 3) {
		if (use_three < 5) {
			check_visited(v[idx].first, v[idx].second, 3, true);
			dfs(idx+1, use_one, use_two, use_three+1, use_four, use_five, cnt + 9);
			check_visited(v[idx].first, v[idx].second, 3, false);
		}
		if (use_two < 5) {
			check_visited(v[idx].first, v[idx].second, 2, true); 
			dfs(idx+1, use_one, use_two+1, use_three, use_four, use_five, cnt + 4);
			check_visited(v[idx].first, v[idx].second, 2, false);
		}
		if (use_one < 5) {
			check_visited(v[idx].first, v[idx].second, 1, true);	
			dfs(idx + 1, use_one+1, use_two, use_three, use_four, use_five, cnt + 1);
			check_visited(v[idx].first, v[idx].second, 1, false);
		}
	} else if(go_toward == 4) {
		if (use_four < 5) {
			check_visited(v[idx].first, v[idx].second, 4, true);
			dfs(idx+1, use_one, use_two, use_three, use_four+1, use_five, cnt + 16);
			check_visited(v[idx].first, v[idx].second, 4, false);
		}
		if (use_three < 5) {
			check_visited(v[idx].first, v[idx].second, 3, true);
			dfs(idx+1, use_one, use_two, use_three+1, use_four, use_five, cnt + 9);
			check_visited(v[idx].first, v[idx].second, 3, false);
		}
		if (use_two < 5) {
			check_visited(v[idx].first, v[idx].second, 2, true);
			dfs(idx+1, use_one, use_two+1, use_three, use_four, use_five, cnt + 4);
			check_visited(v[idx].first, v[idx].second, 2, false);
		}
		if (use_one < 5) {
			check_visited(v[idx].first, v[idx].second, 1, true);	
			dfs(idx + 1, use_one+1, use_two, use_three, use_four, use_five, cnt + 1);
			check_visited(v[idx].first, v[idx].second, 1, false);
		}
	} else if (go_toward == 5) {
		if (use_five < 5) {
			check_visited(v[idx].first, v[idx].second, 5, true);	
			dfs(idx + 1, use_one, use_two, use_three, use_four, use_five+1, cnt + 25);
			check_visited(v[idx].first, v[idx].second, 5, false);
		}
		if (use_four < 5) {
			check_visited(v[idx].first, v[idx].second, 4, true);
			dfs(idx+1, use_one, use_two, use_three, use_four+1, use_five, cnt + 16);
			check_visited(v[idx].first, v[idx].second, 4, false);
		}
		if (use_three < 5) {
			check_visited(v[idx].first, v[idx].second, 3, true);
			dfs(idx+1, use_one, use_two, use_three+1, use_four, use_five, cnt + 9);
			check_visited(v[idx].first, v[idx].second, 3, false);
		}
		if (use_two < 5) {
			check_visited(v[idx].first, v[idx].second, 2, true);
			dfs(idx+1, use_one, use_two+1, use_three, use_four, use_five, cnt + 4);
			check_visited(v[idx].first, v[idx].second, 2, false);
		}
		if (use_one < 5) {
			check_visited(v[idx].first, v[idx].second, 1, true);	
			dfs(idx + 1, use_one+1, use_two, use_three, use_four, use_five, cnt + 1);
			check_visited(v[idx].first, v[idx].second, 1, false);
		}
	}
}

// �湮 Ȯ�� �迭�� flag�� on / off �մϴ�. 
void check_visited(int y, int x, int size, bool flag)
{	
	if (y+size>10 || x+size> 10) {
		return ;
	}
	for (int j = y; j < y + size; j++) {
        for (int i = x; i < x + size; i++) {
            visited[j][i] = flag;
        }
    }
}
// �ش� �ε������� �湮�� �� �ִ� ��ǥ�� �����Ѵ�. 
int find_range(int y, int x) {
	if (check_square(y, x, 2) == true) {
		if (check_square( y, x, 3) == true) {
			if (check_square(y, x, 4) == true) {
				if (check_square(y, x, 5) == true) {
					return 5;
				}
				return 4;
			}
			return 3;
		}
		return 2;
	}
	return 1;
}
	
// size * size �����̸� ���� �� �ִ��� �˻��Ѵ�. 
bool check_square(int y, int x, int size) {
	if (y+size>10 || x+size>10) {
		return false;
	}
	for (int j = y; j < y + size; j++) {
		for (int i = x; i < x + size; i++) {
			if (map[j][i] == 0 || visited[j][i] == true) {
				return false;
			} 
		}
	}
	return true; 
}
