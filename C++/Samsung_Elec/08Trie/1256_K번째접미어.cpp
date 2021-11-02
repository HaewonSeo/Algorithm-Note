#include <iostream>
#include <string>
using namespace std;

#define ALPHABETS_CNT 26	// 알파벳 소문자만
// [MAXN의 크기를 10000으로 잡아 오류 발생함]
// 문자열이 모두 다른 문자로 이루어졌을 때 Trie의 노드수가 가장 많다.
// 이 경우 노드 수는 (1+n)n/2, 알파벳개수는 26
// 400*401/2 * 26 = 1045200
// 그러나 문자열의 길이가 26을 넘는 경우
// 무조건 겹치게 되어있다..(피존홀)

// 일단은 100000 으로 하니 괜찮았으나, MAXN에 대한 좀더 분석이 필요함...
#define MAXN 100000

// 구조체 및 함수 선언
struct Trie;
Trie* myAlloc();

struct Trie {
	Trie* _child[ALPHABETS_CNT];
	int endPos;

	// 접미사의 시작 위치 i를 저장
	void add(const char* word, int i) {
		if (*word != 0) {
			if (_child[*word - 'a'] == nullptr)
				_child[*word - 'a'] = myAlloc();
			_child[*word - 'a']->add(word + 1, i);
		}
		// 마지막 노드면 endPos = i;
		else
			endPos = i;
	}

	// 문자열의 마지막에 해당하는 Trie의 포인터를 return;
	Trie* get(const char* word) {
		if (*word != 0) {
			if (_child[*word - 'a'] != nullptr)
				return _child[*word - 'a']->get(word + 1);
			return nullptr;
		}
		return this;
	}

	void clear() {
		for (int i = 0; i < ALPHABETS_CNT; i++)
			_child[i] = nullptr;
	}
};

int nodeCnt;
Trie Node[MAXN];
int ans;
int cnt, K;
string str;

Trie* myAlloc() {
	Trie* ret = &Node[nodeCnt++];
	ret->clear();
	ret->endPos = -1;

	return ret;
}

// [dfs 설계에서 오류가 있었음...]
// [마지막 문자인 경우 무조건 return을 하게 했는데,
// a, aoa인 경우처럼 현재 문자열이 접미사일지라도
// dfs가 return 되어서는 안되고 다음 문자까지 이어가야 한다.]
int dfs(Trie *cur) {

	// 마지막 문자이면 cnt++
	if (cur->endPos != -1) {
		cnt++;
		//cout << "cnt=" << cnt << " " << str.substr(cur->isEnd) << endl;
		if (cnt == K) {
			ans = cur->endPos;
			return 1;
		}
		// [마지막 문자여도 리턴하면 안됨. 같은 문자열이 포함되는 문자열을 pass하게 됨]
	}

	for (int i = 0; i < ALPHABETS_CNT; i++) {
		if (cur->_child[i] == nullptr) continue;

		//answer.push_back('a' + i);
		if (dfs(cur->_child[i]))
			break;
		// [여기서 종료 여부를 한번더 확인해도 됨]
		// if (cnt == K)
		// 		return ;
		//answer.pop_back();
	}
	return 0;
}

int main() {

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {

		//[cin >> str >> K 순으로 잘못 입력받아 오류 발생함]
		cin >> K >> str;

		nodeCnt = 0;
		Trie *root = myAlloc();
		cnt = 0;
		ans = 0;

		for (int i = 0; i < str.size(); i++) {
			// 모든 접미어를 Trie에 추가
			root->add(&str[i], i);
			//cout << "i=" << i << " " << &str[i] << endl;
		}

		// dfs 로 탐색하면, 사전순으로 탐색가능하다.
		dfs(root);

		//cout << nodeCnt << endl;
		cout << "#" << tc << " " << str.substr(ans) << "\n";
	}
	return 0;
}
