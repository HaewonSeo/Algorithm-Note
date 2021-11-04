#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isend;

void dfs(string cur, vector<vector<string>> tickets, vector<bool> &used, vector<string> &ans) {

	ans.push_back(cur);

	if (ans.size() == tickets.size() + 1) {
		isend = true;
		return ;
	}

	for (int i = 0; i < tickets.size(); ++i) {

		if (used[i] || tickets[i][0].compare(cur) != 0)
			continue;

		used[i] = true;
		dfs(tickets[i][1], tickets, used, ans);
		if (isend)
			return ;
		used[i] = false;
	}

	ans.pop_back();
}

vector<string> solution(vector<vector<string>> tickets) {
	vector<string> answer;
	vector<bool> used(tickets.size(), false);
	vector<string> route;

	sort(tickets.begin(), tickets.end());
	dfs("ICN", tickets, used, answer);

	return answer;
}
