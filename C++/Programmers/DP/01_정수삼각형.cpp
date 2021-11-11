#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dp[501][501];

int solution(vector<vector<int>> triangle) {
	int answer = 0;
	int N = triangle.size();

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= i; ++j) {
			// 왼쪽 위와 오른족 위 중 큰 값을 가져온다.
			dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + triangle[i-1][j-1];
		}
	}

	for (int i = 1; i <= N; i++)
		answer = max(answer, dp[N][i]);

	return answer;
}
