#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
	int answer = 0;

	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 0; i < scoville.size(); i++)
		pq.push(scoville[i]);

	while (1) {
		if (pq.size() == 1 && pq.top() < K) {
			answer = -1;
			break;
		}

		int min = pq.top();
		if (min >= K)
			break;

		pq.pop();
		int mix = min + (pq.top() * 2);
		pq.pop();
		pq.push(mix);

		answer++;
	}

	return answer;
}
