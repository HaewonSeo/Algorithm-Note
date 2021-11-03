#include <string>
#include <vector>

using namespace std;

#define MIN(a, b) ((a < b) ? (a) : (b))

bool used[50];
int ans = 100;

bool checkCov(string a, string b) {
	int difCnt = 0;

	for (int i = 0; i < a.size(); ++i) {
		if (a[i] != b[i])
			difCnt++;
	}

	if (difCnt == 1)
		return true;
	else
		return false;
}

void dfs(int cnt, string cur, string target, vector<string> words) {

	if (cur.compare(target) == 0) {
		ans = MIN(cnt, ans);
		return ;
	}

	for (int i = 0; i < words.size(); ++i) {
		if (used[i] || !checkCov(cur, words[i]))
			continue;

		used[i] = true;
		dfs(cnt + 1, words[i], target, words);
		used[i] = false;
	}
}

int solution(string begin, string target, vector<string> words) {
	int answer = 0;

	dfs(0, begin, target, words);

	answer = ans;
	if (answer == 100)
		answer = 0;

	return answer;
}
