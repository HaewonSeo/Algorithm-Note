#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool solution(vector<string> phone_book) {
	bool answer = true;

	// 사전순으로 정렬한 뒤, 근접한 단어끼리 비교
	sort(phone_book.begin(), phone_book.end());
	//for (int i = 0; i < phone_book.size(); ++i)
	//    cout << phone_book[i] << " ";

	for (int i = 0; i < phone_book.size() - 1; ++i) {
		if (phone_book[i] == phone_book[i+1].substr(0, phone_book[i].size()))
			answer = false;
	}

	return answer;
}

/*

// hash를 이용한 풀이
// hash를 이용한 풀이가 위 풀이보다 5배정도 느렸다.

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool solution(vector<string> phone_book) {

	unordered_map<string, int> dic;

	for (int i = 0; i < phone_book.size(); i++)
		dic[phone_book[i]]++;

	for (int i = 0; i < phone_book.size(); i++) {
		string substr = "";
		for (int j = 0; j < phone_book[i].size(); j++) {
			substr += phone_book[i][j];
			if (dic[substr] && substr != phone_book[i])
				return false;
		}
	}
	return true;
}
*/
