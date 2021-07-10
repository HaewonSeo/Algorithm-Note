#include <cstdio>
#include <vector>
using namespace std;

int main() {
	// n의 최대값은 10,000,000
	// 10,000,000의 제곱근(3162.xx)까지의 범위에서 소수를 체크
	// 여기서는 대략 3200으로 설정, 정확하게 하려면 3162로 설정해야함
	bool iscomposite[3200] = {0,};
	for (int i = 2 ; i < 3200 ; i++) {
		if (iscomposite[i]) continue;
		// int j = i + i ; 로 했었는데, 사실 이는 2의 배수이므로
		// 검사할 필요가 없고,
		// 이와 마찬가지로 제곱수 전까지의 i의 배수는 이미 걸러졌기 때문에
		// i*i를 초기값으로 결정함
		for (int j = i * i ; j < 3200 ; j += i) {
			iscomposite[j] = true;
		}
	}

	vector<int> prime;
	for (int i = 2 ; i < 3200 ; i++) {
		if (!iscomposite[i]) {
			prime.push_back(i);
		}
	}

	int n;
	scanf("%d", &n);
	for (int i = 0 ; i < prime.size() ; i++) {
		while (n % prime[i] == 0) {
			printf("%d\n", prime[i]);
			n /= prime[i];
		}
		if (n == 1)
			return 0;
	}
	if (n > 1) {
		printf("%d\n", n);
	}
}


// 다른 방법
/*
#include <cstdio>
int main() {
	int n;
	scanf("%d", &n);
	int i = 2;
	while(i*i <= n) {
		if (n%i == 0) {
			printf("%d\n", i);
			n /= i;
		}
		else i++;
	}
	if (n > 1) printf("%d", n);
	return 0;
}
*/
