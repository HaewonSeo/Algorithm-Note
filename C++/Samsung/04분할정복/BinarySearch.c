int binarySearch(int arr[], int s, int e, int target) {
	while (s <= e) {
		int m = (s + e) / 2;

		if (arr[m] == target) return m;
		else if (arr[m] < target) s = m + 1;
		else e = m - 1;
	}

	return -1;
}


int main() {
	int arr[4] = { 0, 1, 2, 3 };

	int ans = binarySearch(arr, 0, 3, 2);

	return 0;
}

int upperBound(int arr[], int s, int e, int target) {
	int ans = e + 1;	// while loop 내부에서 ans가 갱신 되지 않았을 경우를 고려해 적절한 값으로 초기화

	while (s <= e) {
		int m = (s + e) / 2;

		if (arr[m] > target) {
			ans = m;
			e = m - 1;
		}
		else s = m + 1;
	}

	return ans;
}

int lowerBound(int arr[], int s, int e, int target) {
	int ans = e + 1;	// while loop 내부에서 ans가 갱신 되지 않았을 경우를 고려해 적절한 값으로 초기화

	while (s <= e) {
		int m = (s + e) / 2;

		if (arr[m] >= target) {
			ans = m;
			e = m - 1;
		}
		else s = m + 1;
	}

	return ans;
}
