/* 
** BOJ 6603
** 문제 유형 : 순열
** 문제 제목 : 로또
** https://www.acmicpc.net/problem/10974
*/

#include<iostream>

#define MIN 6
#define MAX 13

using namespace std;

int lotto[MAX];
int result[MAX];
int k;
 
void dfs(int start, int depth) {
    
	// 깊이 6 = 6개의 result 배열 완성 -> 탈출.
    if (depth == 6) {  
        for(int i = 0; i < 6; i++) {
            cout << result[i] << ' ';
        }
        cout << '\n';
        return;
    }
                                        
    for(int i = start; i < k; i++) {    //lotto배열 0부터 k-1까지 탐색함     
        result[depth] = lotto[i];    //depth는 깊이 -> 0~5번째 깊이까지 재귀를통해 새로 탐색한 숫자를 넣음.    
        dfs(i + 1, depth + 1);             
    }
    
}
 
int main() {
	
    while(cin >> k && k) {     
        for(int i = 0; i < k; i++) {
            cin >> lotto[i];
        }
        dfs(0,0);
    }
    return 0;
}