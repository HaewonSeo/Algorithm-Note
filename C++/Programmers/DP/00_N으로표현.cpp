#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int getNN(int N, int cnt) {
	int NN = 0;
	while (cnt--)
		NN = (NN * 10) + N;

	return NN;
}

int solution(int N, int number) {


	// dp[k] = dp[i] [op] dp[j] or Nk (op:*/+-, i+j = k, Nk : N k개로 이루어진 숫자)
	// dp[1] = N
	// dp[2] = dp[1] [op] dp[1] or NN
	// dp[3] = dp[2] [op] dp[1] or NNN
	// ...
	if (N == number)
		return 1;

	vector<unordered_set<int>> dp(9); // 1~8 사용

	dp[1].insert(N);

	for (int k = 2; k <= 8; k++) {
		// dp[i] [op] dp[j]
		for (int i = 1; i < k; i++) {
			for (int j = 1; j < k; j++) {
				if (i + j != k) continue;
				for (int a : dp[i]) {
					for (int b : dp[j]) {
						dp[k].insert(a + b);
						dp[k].insert(a * b);
						if (a - b > 0) dp[k].insert(a - b); // 0과 음수는 불필요함... 오히려 계산량을 늘린다.
						if (a / b > 0) dp[k].insert(a / b); // 0은 불필요함
					}
				}
			}
		}
		// NN
		dp[k].insert(getNN(N, k));

		// number가 있는지 확인
		if (dp[k].count(number))
			return k;
	}

	// 8번까지 안나오는 경우 -1 return
	return -1;
}
