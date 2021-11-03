#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
	int answer = 0;

	int student[31] = {0, };

	for (int i = 1; i <= n; i++)
		student[i] = 1;

	for (int i : lost)
		student[i]--;

	for (int i : reserve)
		student[i]++;

	// 총 5명 중
	// lost 3 5
	// reserve 2 4
	// lost 학생들이 동시에
	// i-1 학생한테 먼저 빌리는 경우 : 체육복 가진 학생 1 2 3 4 5
	// i+1 학생으로부터 먼저 빌리는 경우 : 체육복 가진 학생 1 2(2벌) 3 4

	// lost 1 3
	// reserve 2 4
	// lost 학생들이 동시에
	// i-1 학생한테 먼저 빌리는 경우 : 체육복 가진 학생 2 3 4(2벌) 5
	// i+1 학생으로부터 먼저 빌리는 경우 : 체육복 가진 학생 1 2 3 4 5

	// 즉, lost 학생들이 동시에 빌린다면, 빌리는 순서에 따라 최대값이 달라진다. -> i-1학생한테 먼저 빌릴지, i+1학생한테 먼저 빌릴지..

	// 그러나, 오름차순 or 내림차순 순서의 학생대로 빌린다면
	// 오름차순일 경우, 왼쪽학생으로부터 먼저 빌리는 경우가.
	// 내림차순일 경우, 오른쪽학생으로부터 먼저 빌리는 경우가.
	// 체육복을 가진 학생 수의 최대값을 만들 수 있다.

	// 오름차순
/*
	for (int i = 1; i <= n; i++) {
		if (student[i] == 1) continue;
		if (student[i] == 0) {
			if (student[i-1] == 2) {
				student[i-1]--;
				student[i]++;
			}
			else if (student[i+1] == 2) {
				student[i+1]--;
				student[i]++;
			}
		}
	}
 */

	// 내림차순
	for (int i = n; i >= 0; i--) {
		if (student[i] == 1) continue;
		if (student[i] == 0) {
			if (student[i+1] == 2) {
				student[i+1]--;
				student[i]++;
			}
			else if (student[i-1] == 2) {
				student[i-1]--;
				student[i]++;
			}
		}
	}

	for (int i = 1; i <= n; i++)
		if (student[i])
		answer++;

	return answer;
}
