#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(int a, int b) {
	return a > b;
}

int main() {

    vector<int> v = {5, 2, 1, 4, 3, 0};

    // default : 오름차순
	sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i)
    	printf("%d ", v[i]);
    printf("\n");

    // 내림차순
    sort(v.begin(), v.end(), comp);
    for (int i = 0; i < v.size(); ++i)
    	printf("%d ", v[i]);
    printf("\n");

    return 0;
}
/*
실행결과
0 1 2 3 4 5
5 4 3 2 1 0
*/
