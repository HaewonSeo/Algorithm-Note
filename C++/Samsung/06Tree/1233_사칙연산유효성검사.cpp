#include <iostream>
using namespace std;

// 계산이 유효한 경우의 조건
	// 1. 모든 리프노드가 숫자
	// 2. 그 외의 노드는 연산자

int main() {

	for (int tc = 1; tc <= 10; tc++) {
		int ans = 1;

		int N;
		cin >> N;
		for (int i = 1; i <= N; i++) {
			char ch;
			cin >> i >> ch;

			// N/2 초과의 노드는 리프노드
			if (i > (N/2)) {
				if (!(ch >= '0' && ch <= '9'))
					ans = 0;
			}
			// 그 외의 노드
			else {
				if (ch >= '0' && ch <= '9')
					ans = 0;

				// 나머지 입력 처리
				int left, right;
				if (N >= (2*i) + 1)
					cin >> left >> right;
				else if (N == (2*i))
					cin >> left;
			}
		}

		cout << "#" << tc << " " << ans << "\n";

	}
}



/*
[생각해보니 이렇게 노드의 값을 다 구할 필요가 없었음]
#include <cstdio>

#define ADD -1
#define SUB -2
#define MUL -3
#define DIV -4
#define MAX_NODE 201

struct TreeNode {
	int data;
	int left;
	int right;
} tree[MAX_NODE];

//int nodeCnt;

void init(int NodeCnt) {
	//nodeCnt = 0;
	for (register int i = 0; i <= MAX_NODE; i++) {
		tree[i].data = 0; // data가 숫자인 경우 양의 정수만 존재
		tree[i].left = tree[i].right = -1;
	}
}

//[Error]
int isCalc(int n) {
	if (tree[n].data == 0)
		return 0;
	else if (tree[n].data < 0) {
		int left = isCalc(tree[n].left);
		int right = isCalc(tree[n].right);
		if (left <= 0 || right <= 0)
			return 0;
		else
			return 1;
	}
	else
		return 1;
}

int main() {

	for (int tc = 1; tc <= 10; tc++) {

		int N;
		scanf("%d", &N);

		init(N);

		for (int i = 1; i <= N; i++) {

			char ch;
			scanf("%d %c", &i, &ch);
			if (ch >= '0' && ch <= '9') {
				int data = 0;
				while (ch >= '0' && ch <= '9') {
					data = (data * 10) + (ch - '0');
					scanf("%c", &ch);
				}
				tree[i].data = data;
			}
			else {
				if (ch == '+') tree[i].data = ADD;
				else if (ch == '-') tree[i].data = SUB;
				else if (ch == '*') tree[i].data = MUL;
				else if (ch == '/') tree[i].data = DIV;
			}

			if (N >= (2*i) + 1)
				scanf("%d %d", &tree[i].left, &tree[i].right);
			else if (N == (2*i))
				scanf("%d", &tree[i].left);
			//else if (N < (2*i)) continue;
		}

		printf("#%d %d\n", tc, isCalc(1));

	}
}

*/
