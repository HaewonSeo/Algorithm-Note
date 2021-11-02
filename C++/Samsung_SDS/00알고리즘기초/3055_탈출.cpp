//#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> pii;		// 좌표를 담을 예정

int r, c;
char forest[50][51];

pii ddg;
vector<pii> water;
pii biber;
queue<pii> water_q, ddg_q; // 좌표를 저장하는 queue
// visited array... 메모리, 시간 절약
int water_vt[50][50] = {0, }, ddg_vt[50][50] = {0,};
int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};		//4방향 위치값
int ans;

bool check_rc(int param_r, int param_c) {
	return (0 <= param_r && param_r < r && 0 <= param_c && param_c < c);
}

int main() {
	//freopen("res/B3055.in", "r", stdin);

	// Input
	scanf("%d%d", &r, &c);
	for (int i = 0; i < r; i++) {
		scanf("%s", forest[i]);
	}

	// BFS
	// 두더지의 시작점이 어디인지 확인
	// 물은 어디에 있는지 확인
		// 물은 하나가 아닐 수 도 있다.
	// 비버굴도 확인
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++) {
			if (forest[i][j] == 'S')
				ddg = pii(i, j);
			else if (forest[i][j] == '*')
				water.push_back(pii(i, j));
			else if (forest[i][j] == 'D')
				biber = pii(i, j);
		}
	}

	// debug
	// 각 위치 출력
	#ifdef DEBUG
		printf("ddg : %d %d\n", ddg.first, ddg.second);
		printf("biber : %d %d\n", biber.first, biber.second);
		printf("water : %d %d\n", water[0].first, water[0].second);
	#endif

	// 탐색
		// 물 이동
			// 주변에 한칸씩 이동
			// 물은 처음에 1개 이상
			// 시작점이 여러개
		// 두더지를 이동시킴:주변에 1칸씩...bfs
			// 단, 돌이 있으면 안됨
			// 다음번에 물이 찰 예정이면 안됨
			// 굴까지 이동을 끝냈으면 끝
	for (int i = 0; i < water.size(); i++){
		pii cur_water = water[i];
		water_q.push(cur_water);
		water_vt[cur_water.first][cur_water.second] = 1;
	}
	ddg_q.push(ddg);
	ddg_vt[ddg.first][ddg.second] = 1;

	// 물과 두더지를 탐색하면서 갈 수 있는지 없는지 판단
	// 두더지가 비버의 굴을 탐색하면 거리를 출력하고 끝
	// 두더지가 더이상 탐색을 못하면 KAKTUS 를 출력하고 씉
	while (!ddg_q.empty()){
		// 물 이동
			// q에서 하나를 꺼내고 상하좌우로 이동
			// 비버의 목적지는 가지말고
			// 돌으로 가지말고
			// 두더지?? 가도 됨
		int water_qsz = water_q.size();
		for (int i = 0; i < water_qsz; i++){
			pii cur_water = water_q.front();
			water_q.pop();
			for (int j = 0; j < 4; j++){
				int new_r, new_c;
				// 상하좌우 탐색
				new_r = cur_water.first + dr[j];
				new_c = cur_water.second + dc[j];
				// 좌표가 영역을 벗어나는지 체크
				if (!check_rc(new_r, new_c)) continue;
				if (forest[new_r][new_c] == 'D' || forest[new_r][new_c] == 'X' || water_vt[new_r][new_c] != 0) continue;
				// 이동 처리
				water_vt[new_r][new_c] == water_vt[cur_water.first][cur_water.second] + 1;
				water_q.push(pii(new_r, new_c));
			}
		}

		// 두더지 이동
			// q에서 하나를 꺼내고 상하좌우로 이동
			// 물을 가지 말고
			// 돌도 가지말고
			// 목적지이면 찾은 것
		int ddg_qsz = ddg_q.size();
		for (int i = 0; i < ddg_qsz; i++){
			pii cur_ddg = ddg_q.front();
			ddg_q.pop();
			for (int j = 0; j < 4; j++){
				int new_r, new_c;
				new_r = cur_ddg.first + dr[j];
				new_c = cur_ddg.second + dc[j];
				if (!check_rc(new_r, new_c)) continue;
				if (forest[new_r][new_c] == 'X' || water_vt[new_r][new_c] != 0) continue;

				if (forest[new_r][new_c] == 'D'){
					// 찾았다.
					ans = ddg_vt[cur_ddg.first][cur_ddg.second] + 1;
					ans--; // 왜냐면 처음 시작을 1로 했으니까...
					printf("%d", ans);
					return 0;
				}
				else{
					// 이동처리
					ddg_vt[new_r][new_c] = ddg_vt[cur_ddg.first][cur_ddg.second] + 1;
					ddg_q.push(pii(new_r, new_c));
				}
			}
		}
	}
	printf("KAKTUS");

}
	// 고민할점
		// 두더지가 이동할 앞으로 물이 찰지 안찰지 어떻게 판단하지??
