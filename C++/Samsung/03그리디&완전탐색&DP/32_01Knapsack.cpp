#include <iostream>
#include <algorithm>
using namespace std;

int dp[101][1001];
int V[101], C[101];

int main() {
	ios_base::sync_with_stdio(false);
	cout.tie(NULL); cin.tie(NULL);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int N, K;
		cin >> N >> K;
		for (int n = 1; n <= N; n++)
			cin >> V[n] >> C[n];

		for (int i = 0; i <= N; i++)
			dp[i][0] = 0;
		for (int j = 0; j <= K; j++)
			dp[0][j] = 0;

		// dp[i][j] = max(dp[i-1][j], w + dp[i-1][j - w])
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= K; j++) {
				if (V[i] <= j)
					dp[i][j] = max(dp[i-1][j], C[i] + dp[i-1][j - V[i]]);
				else
					dp[i][j] = dp[i-1][j];
			}
		}

		cout << "#" << tc << " " << dp[N][K] << "\n";

#ifdef DEBUG
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= K; j++)
				cout << dp[i][j] << " ";
			cout << "\n";
		}
#endif
	}
}
