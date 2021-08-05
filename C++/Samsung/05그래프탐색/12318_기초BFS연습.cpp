struct pos {
	int x, y;
};

const int dx[4] = {0, 0, -1, 1}; // 상 하 좌 우
const int dy[4] = {-1, 1, 0, 0};
int curN;
int curMap[10][10];

void bfs_init(int N, int map[10][10]) {
	curN = N;
	for (int i = 0; i < curN; i++) {
		for (int j = 0; j < curN; j++) {
			curMap[i][j] = map[i][j];
		}
	}
}


int bfs(int x1, int y1, int x2, int y2) {

	int front = -1, rear = -1;
	pos Queue[100] = {{0,0}};
	bool visited[10][10] = {false, };
	int dist[10][10] = {0, };

	Queue[++rear] = {x1-1, y1-1};
	visited[y1-1][x1-1] = true;

	while (front != rear) {
		pos cur = Queue[++front];	//dequeue

		// check
		if (cur.x == x2-1 && cur.y == y2-1)
			return dist[cur.y][cur.x];

		for (int i = 0; i < 4; i++) {
			pos next = {cur.x + dx[i], cur.y + dy[i]};
			if (next.x < 0 || next.x >= curN || next.y < 0 || next.y >= curN) continue;
			if (!visited[next.y][next.x] && curMap[next.y][next.x] == 0) {
				visited[next.y][next.x] = true;
				dist[next.y][next.x] = dist[cur.y][cur.x] + 1;
				Queue[++rear] = next; //enqueue
			}
		}
	}
	return -1;
}
