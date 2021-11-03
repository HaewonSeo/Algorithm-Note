#include <string>
#include <vector>

using namespace std;

const int user[3][10] = {{1, 2, 3, 4, 5}, {2, 1, 2, 3, 2, 4, 2, 5}, {3, 3, 1, 1, 2, 2, 4, 4, 5, 5}};
const int userSize[3] = {5, 8, 10};

vector<int> solution(vector<int> answers) {
	vector<int> answer;
	int ansCnt[3] = {0,};

	for (int i = 0; i < answers.size(); i++) {
		for (int j = 0; j < 3; j++) {
			if (answers[i] == user[j][i % userSize[j]]) {
				ansCnt[j]++;
			}
		}
	}

	int max = 0;
	for (int i = 0; i < 3; i++) {
		if (ansCnt[i] > max)
			max = ansCnt[i];
	}

	for (int i = 0; i < 3; i++) {
		if (ansCnt[i] == max)
			answer.push_back(i+1);
	}

	return answer;
}
