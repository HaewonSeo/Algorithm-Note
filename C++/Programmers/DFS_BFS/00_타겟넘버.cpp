#include <string>
#include <vector>
#include <cstdio>

using namespace std;

const int mul[2] = {-1, 1};
int answer;

void dfs(int n, int val, vector<int> num, int target) {
	if (n == num.size()) {
		if (val == target)
			answer++;
		return ;
	}

	int cur = num[n];

	for (int i = 0; i < 2; i++) {
		dfs(n+1, val + cur * mul[i], num, target);
	}
}

int solution(vector<int> numbers, int target) {

	answer = 0;
	dfs(0, 0, numbers, target);

	return answer;
}
