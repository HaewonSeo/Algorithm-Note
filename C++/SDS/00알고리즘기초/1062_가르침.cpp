#include <cstdio>

using namespace std;

int main(){
	// Input
	// 지민이는 꼭 5개의 글자는 알려주어야 함 : a, n, t, i, c
	// k개를 알려줄수 있다고 하면, 실제로는 k-5개만큼은 자유롭게 선택 가능
	// 만약 입력이 k가 5보다 작으면 ?? 무조건 0...
	// 경우의 수
		// ex) k = 7 --> a n t i c 를 빼고 나머지 2개로 기회를 만들 수 있다.
		// b d
		// b e
		// b f
		// ......
		// y z
		// 26 - 5 = 21 개 중에서 2개를 고르는 경우의수
		// --> 21C2 = 210

	// 선택하는 알파벳을 고른 다음에 실제로 주어진 단어를 읽을 수 있느지 확인해봄
	// How?
	// a n t i c b d
	// a n t a rctica x
	// a n t a

	//
}
