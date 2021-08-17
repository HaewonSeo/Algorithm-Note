// 4자리 비트로 참여 여부를 저장
// 연속된 비트가 존재하는지 체크
#include <iostream>
#include <string.h>
using namespace std;

int dp[10000][16]; // 1~15만 사용

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		string str;
		cin >> str;

		memset(dp, 0, sizeof(dp));

		for (int n = 0; n < str.size(); n++) {
			int admin = str[n] - 'A';

			for (int i = 1; i <= 15; i++) {

				// 관리자를 포함하지 않는 경우 pass
				if (!(i & (1 << admin)))
					continue;

				// 첫 번째 날, A가 열쇠를 갖고 있는 경우
				if (n == 0 && (i & 1))
					dp[n][i] = 1;

				// 두 번째 날 이후
				if (n >= 1) {
					// key를 연속으로 갖는지 확인
					for (int j = 1; j <= 15; j++) {
						if (i & j) {
							dp[n][i] += dp[n-1][j];
							dp[n][i] %= 1000000007;
						}
					}
				}
			}
		}

		//[mod 연산은 매 합마다 수행]
		int ans = 0;
		for (int i = 1; i <= 15; i++) {
			ans += dp[str.size()-1][i];
			ans %= 1000000007;
		}

		cout << "#" << tc << " " << ans << "\n";
	}
}

/*
[완전탐색으로 불가!!! -> DP로 해결]

// 4자리 비트로 참여 여부를 저장
// 책임자 제외한 비트중 연속된 비트가 존재하는지 체크
#include <iostream>
using namespace std;

string str;
int vt[10000];
long long ans;
/
//  "모든" 단계에서 열쇠가 넘겨지는지 확인 -> 사용 x
int checkKey() {
	for (int i = 1; i < str.size(); i++) {
		if (!(vt[i] & vt[i-1]))
			return 0;
	}
	return 1;
}


void dfs(int n) {
	if (n == str.size()) {
		ans++;
		return ;
	}

	for (int i = 1; i < 16; i++) {
		// 책임자의 비트가 0인 경우는 배제
		if (!(i & (1 << (str[n] - 'A')))) continue;
		// 첫번째 날에는 A가 열쇠를 가지고 있다!
		// -> 이 조건을 만족하지 못하는 경우 베제
		if (n == 0 && !(i & 1)) continue;

		vt[n] = i;
		// 열쇠가 넘겨지는지 체크
		if (n >= 1 && !(vt[n] & vt[n-1])) continue;
		dfs(n + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> str;
		for (int i = 0; i < str.size(); i++)
			vt[i] = 0;
		ans = 0;

		dfs(0);

		cout << "#" << tc << " " << ans % 1000000007 << "\n";
	}
}

*/
