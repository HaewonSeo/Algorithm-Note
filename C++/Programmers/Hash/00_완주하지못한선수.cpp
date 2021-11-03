#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
	string answer = "";
	unordered_map<string, int> dic;

	for (string name : participant)
		dic[name]++;

	for (string name : completion)
		dic[name]--;

	// for (auto data : dic)
	for (pair<string, int> data : dic) {
		if (data.second > 0) {
			answer = data.first;
			break;
		}
	}
	return answer;
}
