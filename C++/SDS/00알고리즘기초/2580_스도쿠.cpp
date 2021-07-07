#include <cstdio>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

vector<pii> empty_space;
int board[9][9];

// pos에 있는 empty_space를 어떤숫자로 채울지 판단
void recur(int pos)
{
	// final condition
	if (pos == empty_space.size())
	{
		// 출력하고
		// 끝냄
		return;
	}
	pii cur = empty_space[pos];
	for (int i = 1; i <= 9; i++)
	{
		int x = cur.first;
		int y = cur.second;
		// 앞으로 할 일은 empty_space를 0 ~ 9 로 채워보는 건데
		// 언제채울 수 있냐면
		// 1. empty_space가 있는 작은 사각형에 숫자가 중복이 안될때!  ==> 그 작은 사각형을 어떻게 판단할지
		// 구간 : 012/345/678

		// 2. empty_space가 있는 세로줄에 숫자가 중복이 안될때 ==> 세로줄을 어떻게 판단할지??
		for (int r = 0; r <= 9; r++) {
			if (board[r][y] == i) continue;
		}
		// 3. empty_spcae가 있는 가로줄에 숫자가 중복이 안될때 ==> 가로줄을 어떻게 판단할지???
		for (int c = 0; c <= 9; c++) {
			if (board[x][c] == i) continue;
		}
		// 1, 2, 3이 만족이 되면 일단 "그 숫자"로 채워보고
		board[cur.first][cur.second] = i;

		recur(pos + 1);
		// 만약에 정답을 찾았으면 끝내는 방향으로 가고
		// 못찾았으면 다른 숫자로 채워보고...
	}
}

int main()
{
	// 입력을 받은 다음에
	// 빈 공간들("0")을 모은다 (y, x) --> empty_space
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			scanf("%d", &board[i][j]);
			if (board[i][j] == 0)
				empty_space.push_back(pii(i, j));
		}
	}

	recur(0);

	// 모든 empty_space를 어떤 값으로 다 채웠다고 판단하면 그 상태가 정답이므로 출력을 한다.
}
