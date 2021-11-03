#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAX 1000000000
typedef long long ll;


ll solution(int n, vector<int> times) {
	ll answer = 0;

	sort(times.begin(), times.end());

	ll s = 1; // n=1, times=[1] 인 경우
	// [int -> long long 으로의 명시적 형변환이 필요했다]
	ll e = (ll)n * times.back(); // 제일 긴 심사대에서 모든 사람이 기다리는 경우

	while (s <= e) {
		ll mid = (s + e) / 2;

		// s~mid 구간에서의 심사 횟수를 count
		ll cnt = 0;
		for (int t : times)
			cnt += (mid / t);

		cout << "mid=" << mid << ", ans=" << answer << endl;
		// lower bound
		if (n <= cnt) {
			answer = mid;
			e = mid - 1;
		}
		else
			s = mid + 1;
	}

	return answer;
}
