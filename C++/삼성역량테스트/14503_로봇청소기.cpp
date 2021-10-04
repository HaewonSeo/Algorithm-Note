#include <cstdio>

#define MAXNM 50

int N, M;
int map[MAXNM][MAXNM];

int main() {
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	int r, c , d;
	scanf("%d%d", &N, &M);
	scanf("%d%d%d", &r, &c, &d);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			scanf("%d", &map[i][j]);

}
