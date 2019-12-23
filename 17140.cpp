/* 
** BOJ 17140
** 문제 유형 : 시뮬레이션 
** 문제 제목 : 이차원 배열과 연산 
** https://www.acmicpc.net/problem/17140
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int r, c, k;
int map[100][100] = {0, };
int row = 3; // 열 
int col = 3; // 행 
int sec = 0;
void solve();
int do_row();
int do_col();
int make_row(int );
int make_col(int );
struct set {
	int cnt = 0;
	int num = 101;
};
bool operator<(const set & lhs, const set & rhs)
{
    if (lhs.cnt == rhs.cnt) {
    	return lhs.num < rhs.num;
	}
	return lhs.cnt < rhs.cnt;
}
vector<struct set> list;
vector<struct set> real_list;
vector<int> a; 
int abc = 0;
void clear_real_v();
int main() {
    cin >> r >> c >> k;
    for (int y = 0; y < row; y++) {
        for (int x = 0; x < col; x++) {
            cin >> map[y][x];
        }
    }
	for (int i = 0; i < 101; i++) {
		struct set a;
		a.num = i;
		a.cnt = 0;
		list.push_back(a);
	}
    
    solve();
	if (sec > 100) {
		cout << "-1";
	} else {
		cout << sec;	
	}
    
    return 0;
}

void solve() {
    // cout << endl;
	abc++;
    if (map[r-1][c-1] == k) {
		// printf("정답을 찾았습니다");
        return; // 정답을 찾은 경우
    }
	sec++; // 초를 올려준다.
	if (sec > 100) {
		return;
	}
    
    if (col >= row) { // 행 연산을 수행
        // printf("행연산을 수행합니다."); 
		row = do_col();
    } else { // 열 연산을 수행
    	// printf("열연산을 수행합니다.");
        col = do_row();
    }
    // printf("\n%d 초 경과, ", abc);
   //  printf("%d%d\n", col, row);
//	for (int y = 0; y < col; y++) {
//		cout << endl;
//        for (int x = 0; x < row; x++) {
//            cout << map[y][x];
//        }
//    }
    if (sec > 100) {
    	return;
	}
	if (map[r-1][c-1] != k) {
	// 	printf("답을 못찾았습니다 다시 수행합니다"); 
		solve();
    } 
}
int do_col() {
	int new_row = 0;
	for (int y = 0; y < col; y++) { // col의 수만큼 정렬을 한다.
		clear_real_v();
		int temp = make_col(y);
		if (temp > new_row)  {
			new_row = temp;
		}
	}
	if (new_row < row) {
		new_row = row;
	} 
	// printf("바뀐 col값 %d\n", col); 
	return new_row;
}
int make_col(int y) {
	int cnt = 0;
	for (int x = 0; x < row; x++) {
		if (list[map[y][x]].num == 0) {
			continue;
		}
		bool exist = false;
	// 	printf("검사할 녀석 %d\n", map[y][x]);
		if (list[map[y][x]].num == map[y][x]) {
			// 이미 리얼 배열에 추가되어 있는지 검사 
			for (int i = 0; i < real_list.size(); i++) {
				// 이미 존재하면 cnt만 올려준다. 
				if (real_list[i].num == map[y][x]) {
					// printf("존재합니다 cnt만 올려줍니다.\n");
					real_list[i].cnt++;
					map[y][x] = 0; 
					exist = true;
				} 
			}
			if (exist == false) {
				// printf("존재하지 않습니다 추가합니다\n"); 
				list[map[y][x]].cnt++; 
				real_list.push_back(list[map[y][x]]);
				map[y][x] = 0;		
			}
		}
	}
 	cnt = real_list.size() * 2;
	
	// 정렬
	stable_sort(real_list.begin(), real_list.end());
//	printf("1행의 로직 결과");
//	for (int i = 0; i < real_list.size(); i++) {
//		printf("%d %d\n", real_list[i].num, real_list[i].cnt);
//	} 
	
	// 새롭게 넣어주기
	for (int x = 0; x < cnt; x++) {
		int index = x / 2;
		if (x % 2 == 1) {
			map[y][x] = real_list[index].cnt;
		} else {
			map[y][x] = real_list[index].num;	
		}
	}
	// 결과  
//	for (int x = 0; x < cnt; x++) {
//		cout << map[y][x];
//	} 
	return cnt;
}
int do_row() {
	int new_col = 0;
	for (int x = 0; x < row; x++) { // row의 수 만큼 정렬을 한다.
		clear_real_v();// cout << "1" << endl;
		int temp =  make_row(x);
		if (temp > new_col) {
			new_col = temp;
		}
	}
	if (new_col < col) {
		new_col = col;
	}
	// cout << "3" << endl;
	return new_col;
}
int make_row(int x) {
	int cnt = 0; 
	for (int y = 0; y < col; y++) {
		if (list[map[y][x]].num == 0) {
			continue;
		}
		// printf("검사할 녀석 %d\n", map[y][x]);
		bool exist = false;
		if (list[map[y][x]].num == map[y][x]) {
			// 이미 리얼 배열에 추가되어 있는지 검사 
			for (int i = 0; i < real_list.size(); i++) {
				// 이미 존재하면 cnt만 올려준다. 
				if (real_list[i].num == map[y][x]) {
					// printf("존재합니다 cnt만 올려줍니다.\n");
					real_list[i].cnt++;
					exist = true;
					map[y][x] = 0;
				} 
			}
			if (exist == false) {
				// printf("존재하지 않습니다 추가합니다\n");
				list[map[y][x]].cnt++; 
				real_list.push_back(list[map[y][x]]);
				map[y][x] = 0;		
			}
		}
	}
 	cnt = real_list.size() * 2;
	
	// 정렬
	stable_sort(real_list.begin(), real_list.end());
	// printf("1행의 로직 결과");
//	for (int i = 0; i < real_list.size(); i++) {
//		printf("%d %d\n", real_list[i].num, real_list[i].cnt);
//	} 
	
	// 새롭게 넣어주기
	for (int y = 0; y < cnt; y++) {
		int index = y / 2;
		if (y % 2 == 1) {
			map[y][x] = real_list[index].cnt;
		} else {
			map[y][x] = real_list[index].num;	
		}
	}
//	// 결과 
//	for (int y = 0; y < cnt; y++) {
//		cout << map[y][x] << endl;
//	} 
	return cnt;

}
	
void clear_real_v() {
	// printf("배열을 청소합니다");
	while(real_list.empty() == false) {
		real_list.pop_back();
	}
	for (int i = 0; i < list.size(); i++) {
		if (list[i].cnt != 0) {
			list[i].cnt = 0;
		}
	}
	return;
}


