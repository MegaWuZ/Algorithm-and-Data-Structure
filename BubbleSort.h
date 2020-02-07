#pragma once
#include<iostream>
#include<string>
#include"SortTestHelper.h"
#include"SelectionSort.h"
#include"InsertionSort.h"
using namespace std;

template<typename T>
void bubbleSort1(T arr[], int n) {
	bool swapped;
	do {
		swapped = false;
		for (int i = 1; i < n; i++)
			if (arr[i - 1] > arr[i]) {
				swap(arr[i - 1], arr[i]);
				swapped = true;
			}
		// 优化, 每一趟Bubble Sort都将最大的元素放在了最后的位置
		// 所以下一次排序, 最后的元素可以不再考虑
		n--;
	} while (swapped);
}


template<typename T>
void bubbleSort2(T arr[], int n) {
	int exchange;
	do {
		exchange = 0;
		for (int i = 1; i < n; i++)
			if (arr[i - 1] > arr[i]) {
				swap(arr[i - 1], arr[i]);
				exchange = i;
			}
		n = exchange;
	} while (exchange > 0);
}