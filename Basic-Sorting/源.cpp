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

int main() {

	int n = 10000;

	// 测试1 一般测试
	cout << "Test for random array, size = " << n << ", random range [0, " << n << "]" << endl;

	int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int *arr2 = SortTestHelper::copyIntArray(arr1, n);
	int *arr3 = SortTestHelper::copyIntArray(arr1, n);
	int *arr4 = SortTestHelper::copyIntArray(arr1, n);
	int *arr10 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Selection Sort", selectionSort1, arr1, n);
	SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
	SortTestHelper::testSort("Bubble Sort", bubbleSort1, arr3, n);
	SortTestHelper::testSort("Shell Sort1", shellSort1, arr4, n);
	SortTestHelper::testSort("Shell Sort2", shellSort2, arr10, n);





	cout << endl;


	// 测试2 测试近乎有序的数组
	int swapTimes = 100;

	cout << "Test for nearly ordered array, size = " << n << ", swap time = " << swapTimes << endl;

	int *arr5 = SortTestHelper::generateNearlyOrderArray(n, swapTimes);
	int *arr6 = SortTestHelper::copyIntArray(arr5, n);
	int *arr7 = SortTestHelper::copyIntArray(arr5, n);
	int *arr8 = SortTestHelper::copyIntArray(arr5, n);
	int *arr9 = SortTestHelper::copyIntArray(arr5, n);

	SortTestHelper::testSort("Selection Sort", selectionSort1, arr5, n);
	SortTestHelper::testSort("Insertion Sort", insertionSort, arr6, n);
	SortTestHelper::testSort("Bubble Sort", bubbleSort1, arr7, n);
	SortTestHelper::testSort("Shell Sort1", shellSort1, arr8, n);
	SortTestHelper::testSort("Shell Sort2", shellSort2, arr9, n);
	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;

	delete[] arr5;
	delete[] arr6;
	delete[] arr7;
	delete[] arr8;
	delete[] arr9;
	delete[] arr10;

	system("pause");
	return 0;
}
