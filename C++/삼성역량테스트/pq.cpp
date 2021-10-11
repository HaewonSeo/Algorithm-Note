#include <cstdio>
#include <queue>
using namespace std;

struct s {
	int num;
	char ch;

	// constructor
	s(int _num, char _ch) : num(_num), ch(_ch) {}

	// 방법 1. pq의 default 비교연산자인 less<T>를 사용하는 경우
	bool operator < (const s s2) const {
		if (this->num == s2.num)
			return this->ch < s2.ch;
		else
			return this->num > s2.num;
	}
};

// 방법 2. 새로운 cmp를 정의하는 경우
// 1.num에 대해서 오름차순
// 2.ch에 대해서 내림차순
struct cmp {
	bool operator() (s s1, s s2) {
		if (s1.num == s2.num)
			return s1.ch < s2.ch;
		else
			return s1.num > s2.num;
	}
};

int main() {

	// 방법 1, 2 모두 같은 결과
	priority_queue<s> pq;
	// priority_queue<s, vector<s>, cmp> pq;

	pq.push(s(1, 'a'));
	pq.push(s(1, 'b'));
	pq.push(s(2, 'a'));
	pq.push(s(2, 'b'));
	pq.push(s(3, 'a'));
	pq.push(s(4, 'b'));

	while (!pq.empty()) {
		s cur = pq.top(); pq.pop();
		printf("%d %c\n", cur.num, cur.ch);
	}

	return 0;
}

	/*
	실행 결과
	1 b
	1 a
	2 b
	2 a
	3 a
	4 b
	*/
