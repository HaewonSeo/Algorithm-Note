#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string s1, s2;
int dp[1001][1001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> s1 >> s2;

		for (int i = 0; i <= s1.size(); i++) {
			for (int j = 0; j <= s2.size(); j++)
				dp[i][j] = 0;
		}

		for (int i = 1; i <= s1.size(); i++) {
			for (int j = 1; j <= s2.size(); j++) {
				if (s1[i-1] == s2[j-1])
					dp[i][j] = dp[i-1][j-1] + 1;
				else
					dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
		}

		int ans = dp[s1.size()][s2.size()];
		cout << "#" << tc << " " << ans << "\n";
	}
}



/*
[Time Out! -> 완전탐색이 아닌 DP로 해결해야 함]

#include <iostream>
#include <string>
using namespace std;

string s1, s2;
string LCS;
int ans;

// LCS : Longest Common Sequence
int checkLCS() {
	int pos = 0;
	for (int i = 0; i < s2.length(); i++) {
		if (LCS[pos] == s2[i])
			pos++;
		if (pos == LCS.length())
			return pos;
	}
	return -1;
}

void dfs(int pos) {
	if (pos == s1.length()) {
		if (LCS.length() <= ans)
			return ;
		int len = checkLCS();
		if (len > ans) {
		//	cout << "LCS= " << LCS << "\n";
			ans = len;
		}
		return ;
	}

	LCS.push_back(s1[pos]);
	//cout << "LCS=" << LCS << " ";
	dfs(pos+1);
	LCS.pop_back();
	//cout << "LCS=" << LCS << " ";
	dfs(pos+1);
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		s1.clear(); s2.clear(); LCS.clear();
		cin >> s1 >> s2;
		//cout << s1 << "\n" << s2 << "\n";
		ans = 0;
		dfs(0);

		cout << "#" << tc << " " << ans << "\n";
	}
}
*/
