/* 
** BOJ 1697
** ???? ???? : BFS
** ???? ???? : ???????  
** https://www.acmicpc.net/problem/1697
*/
#include<iostream>
#include<queue>

using namespace std;
const int MAX =  100001;
int visited[MAX] = {0};

int bfs(int n, int k) {
	
	queue<int> q;
	q.push(n); // ??? ???? ???????? ????? ??????. 
	visited[n] = 1; // ???? ??? ???? ????? ??? ???? 1?? ??????. 
	while(q.empty() == false) {
		int p = q.front();
		q.pop();
		// ??? ?? k?? ??? ???????. 
		if (p == k) {
			return visited[p] - 1; 
		}
		// +1?? ???????. 
		if (p + 1 < MAX && visited[p+1] == 0) {
			visited[p+1] = visited[p] + 1;
			q.push(p+1);
		}
		// -1?? ???????. 
		if (p - 1 >= 0 && visited[p-1] == 0) {
			visited[p-1] = visited[p] + 1;
			q.push(p-1);
		}
		// *2?? ???????. 
		if (p * 2 < MAX && visited[2*p] == 0) {
			visited[p*2] = visited[p] + 1;
			q.push(p*2);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	int n, k;
	scanf("%d %d", &n, &k);
	int min = bfs(n, k);
	
	printf("%d", min);
	return 0;
}