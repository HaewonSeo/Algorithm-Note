#include <string>
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

#define MAX 10000000

bool prime[MAX];
bool isDup[MAX];
bool vt[7];
int ans;

void makePrime() {

	memset(prime, 1, sizeof(prime));
	prime[0] = prime[1] = false;

	for (int i = 2; i < MAX; i++) {
		if (prime[i]) {
			for (int j = i*i; j < MAX; j += i) {
				prime[j] = false;
			}
		}
	}
}

void dfs(int n, string num, int value) {
	if (n == num.size()) {
		if (prime[value] && !isDup[value])
		{
			cout << value << endl;
			ans++;
			isDup[value] = true;
		}
	}

	for (int i = 0; i < num.size(); i++) {
		if (vt[i]) continue;
		int digit = num[i] - '0';
		vt[i] = true;
		dfs(n+1, num, value * 10 + digit);
		dfs(n+1, num, value);
		vt[i] = false;
	}

}

int solution(string numbers) {

	makePrime();

	ans = 0;
	dfs(0, numbers, 0);

	return ans;
}
