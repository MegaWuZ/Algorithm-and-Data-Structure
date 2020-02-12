
#pragma once
using namespace std;

template <typename T>
void __quickSort3Ways(T arr[], int l, int r) {

	/*if (l >= r)
		return;*/
	if (r - l < 15) {
		insertionSort(arr, l, r);
		return;
	}
	//partition
	swap(arr[l], arr[rand() % (r - l + 1) + l]);
	T v = arr[l];
	int lt = l;
	int gt = r + 1;
	int i = l + 1;
	while (i < gt) {
		if (arr[i] > v) {
			swap(arr[i], arr[gt - 1]);
			i++;
			gt--;
		}
		else if (arr[i] < v) {
			swap(arr[i], arr[lt + 1]);
			i++;
			lt++;
		}
		else {
			i++;
		}
	}
	swap(arr[l], arr[lt]);
	__quickSort3Ways(arr, l, lt - 1);
	__quickSort3Ways(arr, gt, r);
}

template <typename T>
void QuickSort3Ways(T arr[], int n) {
	srand(time(NULL));
	__quickSort3Ways(arr, 0, n - 1);
}