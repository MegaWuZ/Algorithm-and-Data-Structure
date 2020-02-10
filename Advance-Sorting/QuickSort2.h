#pragma once
#include<iostream>
#include<string>
using namespace std;


template <typename T>
int __partition2(T arr[], int l, int r) {

	swap(arr[l], arr[rand() % (r - l + 1) + l]);
	T v = arr[l];

	int i = l + 1, j = r;
	while (true) {
		while (i <= r && arr[i] < v) i++;
		while (j >= l + 1 && arr[j] > v)j--;
		if (i > j) {
			break;
		}
		swap(arr[i], arr[j]);
		i++;
		j--;
	}
	swap(arr[l], arr[j]);
	return j;
}

// 对arr[l...r]部分进行快速排序
template <typename T>
void __quickSort2(T arr[], int l, int r) {

	/*if (l >= r)
		return;*/
	if (r - l < 15) {
		insertionSort(arr, l, r);
		return;
	}

	int p = __partition2(arr, l, r);
	__quickSort2(arr, l, p - 1);
	__quickSort2(arr, p + 1, r);
}

template <typename T>
void QuickSort2(T arr[], int n) {
	srand(time(NULL));
	__quickSort2(arr, 0, n - 1);
}