#include <string>
#include <vector>

using namespace std;

void dfs(int n, vector<vector<int>> com, int vt[]) {

	vt[n] = true;

	for (int nt = 0; nt < com.size(); ++nt) {
		if (!com[n][nt] || vt[nt])
			continue;

		dfs(nt, com, vt);
	}
}

int solution(int n, vector<vector<int>> computers) {
	int answer = 0;
	int vt[200] = {0, };

	for (int i = 0; i < n; ++i) {
		if (!vt[i]) {
			answer++;
			dfs(i, computers, vt);
		}
	}
	return answer;
}
