#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct cmp {
	bool operator() (vector<int> a, vector<int> b) {
		return a[1] > b[1];
	}
};

int solution(vector<vector<int>> jobs) {
	int answer = 0;
	int curEndTime = 0; //현재작업중인 job이 끝나는 시점
	int turnAroundTime = 0; //반환 시간(요청부터 완료까지의 시간)
	priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
	int i = 0;

	sort(jobs.begin(), jobs.end());

	// 아직 모든 job을 pq에 넣지 않았거나
	// pq에 원소가 존재하는 동안 반복
	while (i < jobs.size() || !pq.empty()) {
		// 현재 처리중인 job이 완료되기 전에 요청된 job들을 pq에 enqueue
		// 우선순위는 실행시간이 짧은 job이 높다.
		if (i < jobs.size() && curEndTime >= jobs[i][0]) {
			pq.push(jobs[i++]);
			continue;
		}

		// pq에서 실행시간이 가장 짧은 job을 실행시킨다.
		// 반환시간을 갱신한다.
		if (!pq.empty()) {
			curEndTime += pq.top()[1];
			turnAroundTime += (curEndTime - pq.top()[0]);
			pq.pop();
		}
		// pq가 비어있으면, 그 다음 job의 요청시간을 기준으로 삼음
		else
			curEndTime = jobs[i][0];
	}

	answer = turnAroundTime / jobs.size();

	return answer;
}
