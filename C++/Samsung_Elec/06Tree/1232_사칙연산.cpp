#include <iostream>
#include <cstdio>
using namespace std;

#define ADD -1
#define SUB -2
#define MUL -3
#define DIV -4
#define MAX_NODE 1001

int N;
int tree[MAX_NODE][3];	// 숫자 or 기호 / left / right

int calc(int n) {
	if (tree[n][0] < 0) {
		int left = calc(tree[n][1]);
		int right = calc(tree[n][2]);
		if (tree[n][0] == ADD) return left+right;
		else if (tree[n][0] == SUB) return left-right;
		else if (tree[n][0] == MUL) return left*right;
		else if (tree[n][0] == DIV) return left/right;
	}
	else
		return tree[n][0];
}

int main() {

	for (int tc = 1; tc <= 10; tc++) {

		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			char ch;
			scanf("%d %c", &i, &ch);

			if (ch >= '0' && ch <= '9') {
				tree[i][0] = 0;
				while (ch >= '0' && ch <= '9') {
					tree[i][0] = (tree[i][0] * 10) + (ch - '0');
					scanf("%c", &ch);
					// ch = getchar();
				}
			}
			else {
				if (ch == '+') tree[i][0] = ADD;
				else if (ch == '-') tree[i][0] = SUB;
				else if (ch == '*') tree[i][0] = MUL;
				else if (ch == '/') tree[i][0] = DIV;
				scanf("%d %d", &tree[i][1], &tree[i][2]);
				//cin >> tree[i][1] >> tree[i][2];
			}
		}

		int ans = calc(1);
		printf("#%d %d\n", tc, ans);
		//cout << "#" << tc << " " << ans << "\n";
	}

	return 0;
}
