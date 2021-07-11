#include <cstdio>
#include <vector>
using namespace std;

bool iscomposite[1001];
int n, a[100];
vector<int> prime;
int primeCount[100][168];  // 1000 이하 소수가 168개 존재
int totalCount[168];  // 전체 숫자에서 소수가 나타난 횟수
int gcdCount[168];    // gcd를 이루는 소수의 횟수

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	// 1000까지의 수 중 소수를 구함
	// 어떤 수 N은 N의 제곱근 이상의 소수로 나누어지지 않는다.
	// 따라서 1000까지의 소수를 찾는다.
	for (int i = 2; i <= 1000; i++) {
		if (iscomposite[i]) continue;
		prime.push_back(i);
		for (int j = i * i; j <= 1000; j += i) {
			iscomposite[j] = true;
		}
	}

	// 각 숫자별로 소수가 몇개씩 있을까????? ==> 소인수분해
	for (int i = 0; i < n; i++) {
		int num = a[i];
		for (int j = 0; j < prime.size(); j++) {
			while (num % prime[j] == 0) {
				primeCount[i][j]++;
				totalCount[j]++;
				num /= prime[j];
			}
		}
	}

	// gcd에 포함되는 소수의 개수를 계산...n개에 수에 소수를 골고루 나누어주어야 함
	for (int i = 0; i < prime.size(); i++) {
		gcdCount[i] = totalCount[i] / n;
	}

	int bestScore = 1, minTry = 0;   // 가장 큰 점수, 최소 횟수
	for (int i = 0; i < prime.size(); i++) {
		for (int j = 0; j < gcdCount[i]; j++) {
			bestScore *= prime[i];
		}
		// 각 숫자들에 대해서 GCD되기 위해서 소수가 얼마나 부족한지 확인해본다
		for (int j = 0; j < n; j++) {
			if (primeCount[j][i] < gcdCount[i]) {
				minTry += gcdCount[i] - primeCount[j][i];
			}
		}
	}

	printf("%d %d", bestScore, minTry);
}
