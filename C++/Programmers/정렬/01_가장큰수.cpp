#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp (const string a, const string b) {
	return (a + b > b + a);
}

string solution(vector<int> numbers) {
	string answer = "";

	vector<string> v;

	for (int i = 0; i < numbers.size(); ++i)
		v.push_back(to_string(numbers[i]));

	sort(v.begin(), v.end(), cmp);

	for (int i = 0; i < numbers.size(); ++i)
		answer += v[i];

	if (answer[0] == '0')
		answer = "0";

	return answer;
}
