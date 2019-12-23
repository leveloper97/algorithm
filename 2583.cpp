/* 
** BOJ 2583
** 문제 유형 : DFS
** 문제 제목 : 영역 구하기 
** https://www.acmicpc.net/problem/2583
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 이동 좌표 
int dy[4]={1,-1,0,0};
int dx[4]={0,0,1,-1};
 
int M,N,K;
int map[102][102] = {false};
int visited[100][100]={0};
 
int dfs(int y,int x){
    int cnt=1;
    
    for(int i=0;i<4;i++){
        int nextY=y+dy[i];
        int nextX=x+dx[i];
        
        if(nextY < 0 || nextY >= M || nextX < 0 || nextX >= N) {
        	continue;
		}
        if(map[nextY][nextX] || visited[nextY][nextX] == true) {
        	continue;
		}
            
        visited[nextY][nextX]++;
        cnt+=dfs(nextY,nextX);
    }
    
    return cnt;
}
 
int main(){
	// 입력 
    cin >> M >> N >> K;
    
    int x1, y1, x2, y2;
    for(int i = 0; i < K; i++){
    	cin >> x1 >> y1 >> x2 >> y2;
        
        for(int x = x1; x < x2; x++){
        	for(int y = y1; y < y2; y++){
        		map[y][x]++;
			}
		}
    }
    
    vector<int> ans;
    for(int i=0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(!map[i][j] && !visited[i][j]){
                visited[i][j]++;
                ans.push_back(dfs(i,j));
            }
        }
    }
    
    cout<<ans.size()<<endl;
    
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++)
        cout<<ans[i]<<" ";
 
    return 0;
}

