/*
** BOJ 16235
** ���� ���� : �ùķ��̼� 
** ���� ���� : ���� ����ũ
** https://www.acmicpc.net/problem/14501
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 10; // n�� �ִ�� 10�̴�. 
int map[MAX][MAX] = {0}; // ���� ����� ���� 
int winter_food[MAX][MAX] = {0}; // �� �ܿ︶�� �߰��Ǵ� ��� 
int n; // ������� ���� ��, �� 
int m; // ������ ���� 
int k; // k�� �� 
int tree_add; // �߰��� ���� ���� 
int answer = 0;

struct Tree {
	int y;
	int x;
	int year;
	bool death = false; 
};
struct Tree tree[1000]; // 1000���� ����ü �迭�� �����Ѵ�. 
void do_spring();
void do_summer();
void do_fall();
void do_winter();
void make_tree(int, int); 

int main() {
	
	scanf("%d%d%d", &n, &m, &k);
	// ����� ����(5)�� �Է��Ѵ�. 
	answer = m;
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			map[y][x] = 5;
		}
	}
	// �ܿ︶�� �߰��� ����� �Է¹޴´�. 
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			scanf("%d", &winter_food[y][x]);
		}
	}
	
	// ���� ������ ������ �Է� �޴´�. 
//	printf("���� ������ �Է¹޽��ϴ�. \n");
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &tree[i].y, &tree[i].x, &tree[i].year);
	}
	// �������� ���̸� ���� �����Ѵ�. (���� ����) 
//	printf("���̼����� �����մϴ�\n");
	for (int i = 0; i < m; i++) { // i��°�� ã�´�. 
		for (int j = 1; j < m - i; j++) {
			int index;
			// ���� �ִ� ���� �� ��� temp�� �ٲ۴�. 
			if (tree[j-1].year > tree[j].year) {
//				printf("���� ���� �� ���\n");
				Tree temp = tree[j-1];
				tree[j-1] = tree[j];
				tree[j] = temp;
			}
		}
	}
	
//	for (int i = 0; i < m; i++) {
//		printf("%d%d%d", tree[i].y, tree[i].x, tree[i].year);
//	}
	
	// k�⸸ŭ ������� ������. 
	for (int i = 0 ; i < k; i++) {
		do_spring();
		do_summer();
		do_fall();
		do_winter();	
//		printf("%d���� ������ ���� %d\n", i+1, answer);
	}
	
	if (answer < 0) {
		answer = 0;
	}
	printf("%d", answer);		
		
	return 0;
}
// ��, �ڽ��� ���̸�ŭ ����� �԰� ���̸� �Դ´�. �ϳ��� ĭ�� �������� ������ ������ � �������� ����� �Դ´�. ����� �����ϸ� ����Ѵ�. 
void do_spring() {
//	printf("���� �����մϴ�.\n");
	for (int i = 0; i < m; i++) {
		if (tree[i].death == true) {
//			printf("���� �����Դϴ�. ��и� ���� �ʽ��ϴ�.\n");
			break; 
		}
		int food = map[tree[i].y][tree[i].x]; // ���� ������ �ִ� ���� ����� ��
//	printf("���� ���� ��� : %d\n", food);
		if (food - tree[i].year < 0) {
//			printf("������ �׾����ϴ�.\n");
			answer--;
			tree[i].death = true;
		} else {
//			printf("����� �Ծ����ϴ�. \n");
			food -= tree[i].year; // ������ ���̸�ŭ ����� ó��
			tree[i].year++; // ���� �ѻ� ó�� 	
		}
		map[tree[i].y][tree[i].x] = food; // ���� ��� �ʿ� ������Ʈ 
	}
}
// ����, ���� ������ ������� ���Ѵ�. ���� ������ ���̸� 2�� ���� ���� ����� ���Ѵ�. (�Ҽ����� ������.) 
void do_summer() {
//	printf("������ �����մϴ�.\n");
	for (int i = 0; i < m; i++) {
		if (tree[i].death == true) {
//			printf("���� ������ ������� �ٲߴϴ�.\n");
			int food = tree[i].year / 2;
			map[tree[i].y][tree[i].x] += food;
		}
	}
}
// ����, ������ ���̰� 5�� ����̸� ������ 8���� ĭ�� �����Ѵ�. ���� ����� ������ ������ �ʴ´�. 
void do_fall() {
//	printf("������ �����մϴ�.\n");
	tree_add = 0;
	for (int i = 0; i < m; i++) {
		if (tree[i].year % 5 == 0 && tree[i].death == false) {
//			printf("������ ���̰� 5�� ����̴�. �����Ѵ�\n");
			int y = tree[i].y;
			int x = tree[i].x;
//			printf("������ �༮�� y ��ǥ %d\n", y);
//			printf("������ �༮�� x ��ǥ %d\n", x);
			if (0 < y-1 && y-1 < n + 1 && 0 < x-1 && x-1 < n + 1) {
//				printf("���� ���� %d%d\n", y-1, x-1);
				tree_add++;
				make_tree(y-1, x-1);	
			}
			if (0 < y-1 && y-1 < n + 1 && 0 < x && x < n + 1) {
//				printf("���� ���� %d%d\n", y-1, x);
				tree_add++;
				make_tree(y-1, x);	
			}
			if (0 < y-1 && y-1< n + 1 && 0 < x+1 && x+1< n + 1) {
//				printf("���� ���� %d%d\n", y-1, x+1);
				tree_add++;
				make_tree(y-1, x+1);	
				
			}
			if (0 < y && y < n + 1 && 0 < x-1 && x-1 < n + 1) {
//				printf("���� ���� %d%d\n", y, x-1);
				tree_add++;
				make_tree(y, x-1);	
				
			}
			if (0 < y && y < n + 1 && 0 < x+1 && x+1 < n + 1) {
//				printf("���� ���� %d%d\n", y, x+1);
				tree_add++;
				make_tree(y, x+1);	
				
			}
			if (0 < y+1 && y+1 < n + 1 && 0 < x-1 && x-1 < n + 1) {
//				printf("���� ���� %d%d\n", y+1, x-1);
				tree_add++;
				make_tree(y+1, x-1);	
				
			}
			if (0 < y+1 && y+1 < n + 1 && 0 < x && x < n + 1) {
//				printf("���� ���� %d%d\n", y+1, x);
				tree_add++;
				make_tree(y+1, x);	
				
			}
			if (0 < y+1 && y+1 < n + 1 && 0 < x+1 && x+1< n + 1) {
//				printf("���� ���� %d%d\n", y+1, x+1);
				tree_add++;
				make_tree(y+1, x+1);		
			} else {
//				printf("���� �������� : %d%d", y+1, x+1);
			}
			 
		}
	}
	m += tree_add;
	// ������ ������� ���̼� ������ �Ѵ�. 
	for (int i = 0; i < m; i++) { // i��°�� ã�´�. 
		for (int j = 1; j < m - i; j++) {
			int index;
			// ���� �ִ� ���� �� ��� temp�� �ٲ۴�. 
			if (tree[j-1].year > tree[j].year) {
//				/printf("���� ���� �� ���\n");
				Tree temp = tree[j-1];
				tree[j-1] = tree[j];
				tree[j] = temp;
			}
		}
	}
}
// �ܿ�, �κ��� ���� ���ƴٴϸ鼭 ����� �߰��Ѵ�. �Է����� �־���.. 
void do_winter() {
//	printf("�ܿ��� �����մϴ�.\n");
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			map[y][x] += winter_food[y][x];
		}
	}
}
// ���ڿ��� ������ 8���� ĭ�� ���̰� 1�� ������ �����Ѵ�. 
void make_tree(int y, int x) {
	// ���� �߰� 
	tree[m -1 + tree_add].y = y;
	tree[m -1 + tree_add].x = x;
	tree[m -1 + tree_add].year = 1;
	tree[m -1 + tree_add].death = false;
	
	answer++;	
}
/*
�ٽû����غ���
1. �Ϲ����� ������ �迭�� �ε����� 0,0���� �����ϴµ�,
�̰��� 1���� �����ϱ� ������ �̷��� ó���� ���� ������� �־���.
2. ����������� ������Ƽ���� ���� ����ü�� ���� �Ǿ���.  
 
*/
