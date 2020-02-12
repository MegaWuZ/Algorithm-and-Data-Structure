#pragma once
#pragma once
#include<iostream>
#include<string>
#include"InsertionSort.h"


using namespace std;



template<typename T>
void __merge(T arr[], int l, int mid, int r) {
	T *aux = new T[r - l + 1];

	for (int i = l; i <= r; i++) {
		aux[i - l] = arr[i];
	}
	// ��ʼ����iָ����벿�ֵ���ʼ����λ��l��jָ���Ұ벿����ʼ����λ��mid+1
	//int i = l, j = mid + 1;
	//for (int k = l; k <= r; k++) {

	//	if (i > mid) {  // �����벿��Ԫ���Ѿ�ȫ���������
	//		arr[k] = aux[j - l]; j++;
	//	}
	//	else if (j > r) {  // ����Ұ벿��Ԫ���Ѿ�ȫ���������
	//		arr[k] = aux[i - l]; i++;
	//	}
	//	else if (aux[i - l] < aux[j - l]) {  // ��벿����ָԪ�� < �Ұ벿����ָԪ��
	//		arr[k] = aux[i - l]; i++;
	//	}
	//	else {  // ��벿����ָԪ�� >= �Ұ벿����ָԪ��
	//		arr[k] = aux[j - l]; j++;
	//	}
	//}
	int i = l;
	int j = mid + 1;
	int k = l;
	while (i < mid && j < r) {
		arr[k++] = aux[i - l] < aux[j - l] ? aux[i - l] : aux[j - l];
		i++;
		j++;
	}
	while (i < j) {
		arr[k++] = aux[i - l];
		i++;
	}
	while (j < r) {
		arr[k++] = aux[j - l];
		j++;
	}
	delete[] aux;
}
//�ݹ�ʹ�ù鲢����,��arr[l...r]�ķ�Χ��������
template<typename T>
void __mergeSort(T arr[], int l, int r) {

	/*if (l >= r) {
		return;
	}*/

	if (r - l < 15) {
		insertionSort(arr, l, r);
		return;
	}
	int mid = (l + r) / 2;
	__mergeSort(arr, l, mid);
	__mergeSort(arr, mid + 1, r);
	if (arr[mid] > arr[mid + 1])
		__merge(arr, l, mid, r);


}

// Merge Sort BU Ҳ��һ��O(nlogn)���Ӷȵ��㷨����Ȼֻʹ������forѭ��
  // ���ԣ�Merge Sort BUҲ������1��֮�����ɴ���100��������������
  // ע�⣺��Ҫ���׸���ѭ���������ж��㷨�ĸ��Ӷȣ�Merge Sort BU����һ������
template<typename T>
void MergeSortBU(T arr[], int n) {
	/*for (int sz = 1; sz < n; sz += sz) {
		for (int i = 0; i+sz< n; i += sz + sz) {
			__merge(arr,i,i+sz-1,min((i+sz+sz-1),n-1));
		}
	}*/

	for (int i = 0; i < n; i += 16)
		insertionSort(arr, i, min(i + 15, n - 1));

	for (int sz = 16; sz < n; sz += sz)
		for (int i = 0; i < n - sz; i += sz + sz)
			// ����arr[mid] <= arr[mid+1]�����,������merge
			if (arr[i + sz - 1] > arr[i + sz])
				__merge(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1));
}

// �Ƚ�Merge Sort��Merge Sort Bottom Up���������㷨������Ч��
// �������, �����㷨��Ч���ǲ��ġ�

template<typename T>
void MergeSort(T arr[], int n) {
	__mergeSort(arr, 0, n - 1);
}
