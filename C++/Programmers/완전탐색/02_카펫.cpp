#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(int brown, int yellow) {
	vector<int> answer;

	int row, col;
	int sum = brown + yellow;

	for (int col = 3; col < 5000; col++) {
		for (int row = col; row < 2000000; row++) {
			if (row * col != sum) continue;
			if ((col-2) * (row-2) != yellow) continue;
			answer.push_back(row);
			answer.push_back(col);
			cout << row << " " << col << endl;
			break;
		}
	}

	return answer;
}
