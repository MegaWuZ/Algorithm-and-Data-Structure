#pragma once
#include<iostream>
#include<string>
#include"SortTestHelper.h"
#include"SelectionSort.h"
#include"InsertionSort.h"
#include"BubbleSort.h"
using namespace std;

template<typename T>
void shellSort1(T arr[], int n) {
	for (int d = n / 2; d >= 1; d = d / 2) {
		for (int i = d + 1; i <= n; i++) {
			T e = arr[i];
			int j;
			for (j = i - d; j > 0 && e < arr[j]; j = j - d) {
				arr[j + d] = arr[j];
			}
			arr[j + d] = e;
		}
	}
}

template<typename T>
void shellSort2(T arr[], int n) {

	// 计算 increment sequence: 1, 4, 13, 40, 121, 364, 1093...
	int h = 1;
	while (h < n / 3)
		h = 3 * h + 1;

	while (h >= 1) {

		// h-sort the array
		for (int i = h; i < n; i++) {

			// 对 arr[i], arr[i-h], arr[i-2*h], arr[i-3*h]... 使用插入排序
			T e = arr[i];
			int j;
			for (j = i; j >= h && e < arr[j - h]; j -= h)
				arr[j] = arr[j - h];
			arr[j] = e;
		}

		h /= 3;
	}
}