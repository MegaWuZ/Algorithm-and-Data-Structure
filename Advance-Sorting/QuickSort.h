#pragma once
#include <iostream>
using namespace std;
template <typename T>
int __partition(T arr[], int l, int r) {

	swap(arr[l], arr[rand() % (r - l + 1) + l]);
	T v = arr[l];

	int j = l; // arr[l+1...j] < v ; arr[j+1...i) > v
	for (int i = l + 1; i <= r; i++)
		if (arr[i] < v) {
			j++;
			swap(arr[j], arr[i]);
		}

	swap(arr[l], arr[j]);

	return j;
}

// 对arr[l...r]部分进行快速排序
template <typename T>
void __quickSort(T arr[], int l, int r) {

	/*if (l >= r)
		return;*/
	if (r - l < 15) {
		insertionSort(arr, l, r);
		return;
	}

	int p = __partition(arr, l, r);
	__quickSort(arr, l, p - 1);
	__quickSort(arr, p + 1, r);
}

template <typename T>
void QuickSort(T arr[], int n) {
	srand(time(NULL));
	__quickSort(arr, 0, n - 1);
}
