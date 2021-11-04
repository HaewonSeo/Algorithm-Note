#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
	int answer = 1;

	unordered_map<string, int> map;

	for (int i = 0; i < clothes.size(); ++i)
		map[clothes[i][1]]++;

	unordered_map<string, int>::iterator it;
	for (it = map.begin(); it != map.end(); ++it)
		answer *= (it->second + 1); // 안입는 선택지도 있으므로 + 1

	// 모두 안 입는 경우 제거
	answer--;

	return answer;
}
