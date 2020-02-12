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
	// 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
	//int i = l, j = mid + 1;
	//for (int k = l; k <= r; k++) {

	//	if (i > mid) {  // 如果左半部分元素已经全部处理完毕
	//		arr[k] = aux[j - l]; j++;
	//	}
	//	else if (j > r) {  // 如果右半部分元素已经全部处理完毕
	//		arr[k] = aux[i - l]; i++;
	//	}
	//	else if (aux[i - l] < aux[j - l]) {  // 左半部分所指元素 < 右半部分所指元素
	//		arr[k] = aux[i - l]; i++;
	//	}
	//	else {  // 左半部分所指元素 >= 右半部分所指元素
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
//递归使用归并排序,对arr[l...r]的范围进行排序
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

// Merge Sort BU 也是一个O(nlogn)复杂度的算法，虽然只使用两重for循环
  // 所以，Merge Sort BU也可以在1秒之内轻松处理100万数量级的数据
  // 注意：不要轻易根据循环层数来判断算法的复杂度，Merge Sort BU就是一个反例
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
			// 对于arr[mid] <= arr[mid+1]的情况,不进行merge
			if (arr[i + sz - 1] > arr[i + sz])
				__merge(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1));
}

// 比较Merge Sort和Merge Sort Bottom Up两种排序算法的性能效率
// 整体而言, 两种算法的效率是差不多的。

template<typename T>
void MergeSort(T arr[], int n) {
	__mergeSort(arr, 0, n - 1);
}
