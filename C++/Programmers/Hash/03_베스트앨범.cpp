#include <string>
#include <vector>
#include <map>
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

#define f	first
#define s	second
typedef pair<int, int> pii;
typedef pair<string, int> psi;

bool cmp(psi a, psi b) {
	return (a.s > b.s);
}

// 우선순위1 : count 내림차순
// 우선순위2 : id 오름차순
struct cmp2 {
	bool operator() (pii a, pii b) {
		if (a.f == b.f)
			return (a.s > b.s);
		else
			return (a.f < b.f);
	}
};

// 장르별 총 재생횟수 저장 map<장르, 총count>
// 위 map을 vector로 복사 후 내림차순 정렬-> vector<장르, 총 count>
// 장르내 많이 재생된 2개 노래 탐색 -> map<key(장르),value(pq(pii<count, id>))>
// 장르내 많이 재생된 2개의 노래 id를 answer에 저장

vector<int> solution(vector<string> genres, vector<int> plays) {
	vector<int> answer;
	map<string, int> genre_map;
	map<string, priority_queue<pii, vector<pii>, cmp2>> genre_queue;
	// pq를 내림차순으로 하는 경우
	// map<string, priority_queue<pii, vector<pii>, greater<pii>>> map_queue;

	for (int id = 0; id < genres.size(); ++id) {
		string genre = genres[id];
		int play = plays[id];

		genre_map[genre] += play;
		genre_queue[genre].push(pii(play, id));
	}

	vector<psi> genre_vec(genre_map.begin(), genre_map.end());
	sort(genre_vec.begin(), genre_vec.end(), cmp);

//     for (psi p : genre_vec)
//         printf("%s %d\n", p.f.c_str(), p.s);

	for (psi p : genre_vec) {
		string genre = p.f;
		printf("%s %d\n", p.f.c_str(), p.s);

		int n = 0;
		while (!genre_queue[genre].empty()) {
			pii cur = genre_queue[genre].top();
			genre_queue[genre].pop();
			printf("%d %d\n", cur.first, cur.second);
			answer.push_back(cur.second);
			n++;
			if (n == 2)
				break;
		}

	}

	return answer;
}
