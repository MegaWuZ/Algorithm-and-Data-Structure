#pragma once
#include<iostream>
#include<string>
#include"student.h"
#include"SortTestHelper.h"
using namespace std;

template<typename T>
void selectionSort1(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		//Ѱ��(i,n)���������Сֵ
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}
		swap(arr[i], arr[minIndex]);
	}
}

//������ÿһ��ѭ����ͬʱ�ҵ���ǰ���ݵ����ֵ����Сֵ
template<typename T>
void selectionSort2(T arr[], int n) {
	int left = 0, right = n - 1;
	while (left < right) {
		int minIndex = left;
		int maxIndex = right;
		// ��ÿһ�ֲ���ʱ, Ҫ��֤arr[minIndex] <= arr[maxIndex]
		if (arr[minIndex] > arr[maxIndex])
			swap(arr[minIndex], arr[maxIndex]);

		for (int i = left + 1; i < right; i++)
			if (arr[i] < arr[minIndex])
				minIndex = i;
			else if (arr[i] > arr[maxIndex])
				maxIndex = i;

		swap(arr[left], arr[minIndex]);
		swap(arr[right], arr[maxIndex]);

		left++;
		right--;
	}
	return;
}
//int main() {
//	int n = 1000;
//	int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//	/*selectionSort(arr, n);
//	SortTestHelper::printArray(arr,n);*/
//	SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
//
//	delete[] arr;
//
//	/*float b[4] = { 4.4,3.3,2.2,1.1 };
//	selectionSort(b, 4);
//	for (int i = 0; i < 4; i++)
//		cout << b[i] << " ";
//	cout << endl;
//
//	string c[4] = { "D","C","B","A" };
//	selectionSort(c, 4);
//	for (int i = 0; i < 4; i++)
//		cout << c[i] << " ";
//	cout << endl;
//
//	Student d[4] = { {"D",90},{"C",100},{"B",95},{"A",95} };
//	selectionSort(d, 4);
//	for (int i = 0; i < 4; i++)
//		cout << d[i];
//	cout << endl;*/
//	system("pause");
//	return 0;
//}