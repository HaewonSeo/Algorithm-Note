#include <iostream>
#include <string>
using namespace std;

#define ALPHABETS_CNT 26
#define MAXN 100000

struct Trie {
	Trie* child[ALPHABETS_CNT];
	//bool vt;

} node[MAXN];

Trie* myAlloc();

int nodeCnt, K, cnt;
string str, ans;

void add(Trie *cur, const char *word) {
	if (*word) {
		if (cur->child[*word - 'a'] == nullptr)
			cur->child[*word - 'a'] = myAlloc();
		add(cur->child[*word - 'a'], word + 1);
	}
}

void clear(Trie *cur) {
	for (int i = 0; i < ALPHABETS_CNT; i++)
		cur->child[i] = nullptr;
}

Trie* myAlloc() {
	Trie* ret = &node[nodeCnt++];
	clear(ret);
	//ret->vt = false;

	return ret;
}

void dfs(Trie *cur) {

	if (cnt == K)
		return;

	for (int i = 0; i < ALPHABETS_CNT; i++) {
		if (!cur->child[i]) continue;

		ans.push_back('a' + i);
		// [노드 방문시마다 cnt++]
		cnt++;
		// if (dfs(cur->child[i]))
			// break;
		dfs(cur->child[i]);
		if (cnt == K)
			return ;
		ans.pop_back();
	}

	return ;
	// return 0;
}

int main() {

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {

		nodeCnt = 0;
		Trie* root = myAlloc();
		//root->vt = true;
		cnt = 0;
		ans.clear();
		// while (!ans.empty())
		// 	ans.pop_back();

		cin >> K >> str;

		for (int i = 0; i < str.size(); i++)
			add(root, &str[i]);

		dfs(root);

		cout << "#" << tc << " ";
		if (!ans.empty())
			cout << ans << "\n";
		else
			cout << "none\n";
	}
}
