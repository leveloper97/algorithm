/*
** BOJ 14501
** 문제 유형 : 완전 탐색 
** 문제 제목 : 퇴사
** https://www.acmicpc.net/problem/14501
*/
#include <iostream>
#include <utility>

using namespace std;

pair <int, int> p[15];

int dfs(int);
int n;

int main()
{	
	int result = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p[i].first, &p[i].second); //first: day, second : pay
	}
	for (int i = 0; i < n; i++) { // 각 요소(i일차)에서 출발하고 그 중 맥스 값을 저장한다.
//		printf("%d번째로 출발했을 때의 최대 값 : %d\n", i, dfs(i));
		result = max(result, dfs(i));
	}
	printf("%d", result);
	return 0; 
}

int dfs(int start) {
	int temp = 0;
	int money; 
	int position = start + p[start].first; // 그동안 일한 일 + 일을 하기 위해 필요한 일수 
	if (position < n+1) { // 일할 수 있는지 검사한다. (배열의 인덱스는 0부터 시작하기때문에 +1)
		money = p[start].second; // 일을 했으니 돈을 더한다. 
		temp = money; // 비교를 위해 임시로 저장한다. 
		
		// 일한 곳에서 부터 더 일할 수 있는지 탐색한다. 
		for (int i = position; i < n; i++) {
			money = max(money, temp + dfs(i)); // 
		}
	} else { // 일을 못하면 그냥 0을 리턴한다. 
		return 0;
	}
	return money; 
}
