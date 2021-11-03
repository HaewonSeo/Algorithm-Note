#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;
	int cnt = 0;

	int j = 0;
	while (j < progresses.size()) {

		while (progresses[j] >= 100)
			j++;

		int remain = 100 - progresses[j];
		// day = (99 - progresses[j]) / speeds[j] + 1;
		int day = (remain % speeds[j] == 0) ? remain / speeds[j] : remain / speeds[j] + 1;

		for (int k = j; k < progresses.size(); k++)
			progresses[k] += (speeds[k] * day);

		for (; j < progresses.size(); j++) {
			if (progresses[j] >= 100)
				cnt++;
			else
				break;
		}

		if (cnt) {
			answer.push_back(cnt);
			cnt = 0;
		}
	}

	return answer;
}

/*

// best solution

#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;

	int day;
	int max_day = 0;
	for (int i = 0; i < progresses.size(); ++i)
	{
		day = (99 - progresses[i]) / speeds[i] + 1;

		if (answer.empty() || max_day < day)
			answer.push_back(1);
		else
			++answer.back();

		if (max_day < day)
			max_day = day;
	}

	return answer;
}
*/
