/* 
** BOJ 14499
** ���� ���� : BFS
** ���� ���� : �ֻ��� 
** https://www.acmicpc.net/problem/14499
*/

#include <iostream>
#include <queue>

using namespace std;

int dice[6] = {0, }; // �ֻ����� ���� 
int temp[6] = {0, }; // ����� �ӽ� �ֻ��� 
int y, x; // ���� ��ǥ 
int map[20][20] = {0, }; // ���� 
queue <int> q;
int dice_y, dice_x; // �ֻ����� ��ǥ 
 
void move_dice(int, int ,int);
int main() {
	scanf("%d%d", &y, &x);
	
	scanf("%d%d", &dice_y, &dice_x);
	int cnt;
	scanf("%d", &cnt);
	// ���� �Է� 
//	printf("������ �Է¹޴´�\n");
	for (int j = 0; j< y; j++) {
		for (int i = 0; i < x; i++) {
			scanf("%d", &map[j][i]);
		}
	}
	// ���� �Է�
//	printf("���⸦ �Է¹޴´�\n");
	int direction;
	for (int i = 0; i < cnt; i++) {
		scanf("%d", &direction);
		q.push(direction);
	} 
	
	// ����
	while(q.empty() == false) {
		int dir = q.front();
		q.pop();
		if (dir == 1) { // ���� 
			move_dice(dice_y, dice_x+1, dir);
		} else if (dir == 2) { // �� 
			move_dice(dice_y, dice_x-1, dir);
		} else if (dir == 3) { // �� 
			move_dice(dice_y-1, dice_x, dir);
		} else if (dir == 4) { // �� 
			move_dice(dice_y+1, dice_x, dir);
		}
	} 
   return 0;
}

void move_dice(int curY, int curX, int dir) {
//	printf("�ֻ����� (%d, %d)�� �̵���ŵ�ϴ�.\n", curY, curX);
//	printf("���� �ε��� %d%d\n", y, x);
	if (curY < 0 || curY > y-1 || curX < 0 || curX > x -1) {
//		printf("�ֻ����� �̵��� �� �����ϴ�.\n"); 
		return;
	}
	
	// �ӽ� ���� 
	for (int i = 0; i < 6; i++) {
		temp[i] = dice[i]; 
	}
//	printf("�ӽ÷� �ֻ����� ���� �����մϴ�.\n"); 
	for (int i = 0; i < 6; i++) {
//		 printf("%d\n", temp[i]);
	}
	
	if (dir == 1) {
		dice[0] = temp[3];
		dice[1] = temp[1];		
		dice[2] = temp[0];
		dice[3] = temp[5];
		dice[4] = temp[4]; 
		dice[5] = temp[2];
	} else if(dir == 2) {
		dice[0] = temp[2];		
		dice[1] = temp[1];		
		dice[2] = temp[5];
		dice[3] = temp[0];
		dice[4] = temp[4];		
		dice[5] = temp[3];
	} else if(dir == 3) {
		dice[0] = temp[4];		
		dice[1] = temp[0];
		dice[2] = temp[2];		
		dice[3] = temp[3];		
		dice[4] = temp[5];
		dice[5] = temp[1];
	} else if(dir == 4) {
//		printf("�������� �̵��մϴ�.\n");
		dice[0] = temp[1];		
		dice[1] = temp[5];
		dice[2] = temp[2];		
		dice[3] = temp[3];		
		dice[4] = temp[0];
		dice[5] = temp[4];
	}
	
	if (map[curY][curX] == 0) { // ������ 0�̸� �ֻ����� ������ ���� 
//		printf("�ֻ����� ��: %d�� ������ �����մϴ�.", dice[5]);
		map[curY][curX] = dice[5];
	} else { // ������ 0�� �ƴϸ� ĭ�� �ֻ����� ���� ĭ�� 0�̵ȴ�. 
//		printf("������ ��: %d�� �ֻ����� �����մϴ�.", map[curY][curX]);
		dice[5] = map[curY][curX];
		map[curY][curX] = 0;
	}
	dice_y = curY;
	dice_x = curX;
	// ���� ������Ʈ
//	printf("ȸ���� ����Դϴ�");
		for (int i = 0; i < 6; i++) {
//		printf("%d", dice[i]);
	}
	printf("%d\n", dice[0]);
}
/*
�����غ���
�ֻ������� �������� �ٲ�� ��ġ�鸸 �������߾��µ�
temp�� ��� ���ϱ� ������ �ε����� �ٲ��� �ʴ� �͵鵵 �ٲ���ߴ�. 
�ݺ��� ����ó�� ������ �� Ȯ���ϱ�./ 
*/

	

