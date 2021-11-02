#include <iostream>
#include <string>
using namespace std;

#define ALPHABETS_CNT 26	// 알파벳 소문자만
#define MAXN 10000

struct Trie {
	Trie* _child[ALPHABETS_CNT];

	// Trie에 문자열을 추가
	void add(const char* word) {
		if (*word != 0) {
			if (_child[*word - 'a'] == nullptr)
				_child[*word - 'a'] = myAlloc();
			_child[*word - 'a']->add(word + 1);
		}
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

	// Trie의 모든 자식노드를 초기화
	void clear() {
		for (int i = 0; i < ALPHABETS_CNT; i++)
			_child[i] = nullptr;
	}
};

Trie Node[MAXN];
int nodeCnt;

Trie* myAlloc() {
	Trie* ret = &Node[nodeCnt++];
	ret->clear();

	return ret;
}

int main() {
	nodeCnt = 0;

	Trie *root = myAlloc();

	root->add("hello");
	root->add("hi");
	root->add("high");
	root->add("goodnight");

	string answer = root->get("goodbye") ? "exist" : "not exist";
	cout << answer << endl;
	// not exist

	answer = root->get("high") ? "exist" : "not exist";
	cout << answer << endl;
	// exist

	answer = root->get("he")? "exist" : "not exist";
	cout << answer << endl;
	// exist --> 부분 문자열도 존재한다고 판단.
	// 완전한 문자열인지를 판단하기 위한 방법
	// add()에 문자열의 마지막임을 의미하는 bool 변수 추가
	// get()에 위 bool 변수를 체크
	// 또는 int 변수를 활용.

	// Trie의 시간복잡도(M : 문자열의 길이, N : 문자열 개수)
	// 문자열 추가 O(M)
	// 문자열 탐색 O(M)
	// 그러나 Trie는 공간복잡도 면에서 비효율적

	// 배열의 경우 탐색은 O(N*M)

}
