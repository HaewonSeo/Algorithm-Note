#include <cstdio>
#include <vector>
using namespace std;

bool che[1000001];
int n, a[100];
vector<int> prime;
int count[100][80000];  // 대략 100만 이하 소수가 7xxxx개 있는데.....

int main() {
	for (int i = 2 ; i <= 1000000 ; i++) {
		if (che[i]) continue;
		// i is prime
		for (int j = i * i ; j <= 1000000 ; j += i) {
			che[j] = true;
		}
	}
	for (int i = 2 ; i <= 1000000 ; i++) {
		if (!che[i]) {
			prime.push_back(i);
		}
	}

	scanf("%d", &n);
	for (int i = 0 ; i < n ; i++) {
		scanf("%d", &a[i]);
	}

	// 각 숫자별로 소수가 몇개씩 있을까????? ==> 소인수분해
	for (int i = 0 ; i < n ; i++) {
		int num = a[i];
		for (int j = 0 ; j < prime.size() ; j++) {
			while (num % prime[j] == 0) {
				count[i][j]++;
				num /= prime[j];
			}
		}
	}
	// debug
	for (int i = 0 ; i < n ; i++) {
		printf("[%d] : ", a[i]);
		for (int j = 0 ; j < prime.size() ; j++) {
			if (count[i][j] != 0) {
				printf("prime %d %d, ", prime[j], count[i][j]);
			}
		}
		printf("\n");
	}
}
