#include <string>
#include <vector>
#define DEBUG

using namespace std;

int game[101][101];

int solution(int n, vector<vector<int>> results) {
	int answer = 0;

	for (vector<int> v : results) {
		game[v[0]][v[1]] = 1;
		game[v[1]][v[0]] = -1;
	}

	// floyd-warshall
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (game[i][k] == 1 && game[k][j] == 1) {
					game[i][j] = 1;
					game[j][i] = -1;
				}
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		int cnt = 0;
		for (int j = 1; j <= n; ++j)
			if (game[i][j])
				cnt++;
		if (cnt == n - 1)
			answer++;
	}

#ifdef DEBUG
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			printf("%4d ", game[i][j]);
		printf("\n");
	}
#endif

	return answer;
}
