#pragma once
template<typename T>
void heapSort1(T arr[], int n) {

	MaxHeap<T> maxheap = MaxHeap<T>(n);
	for (int i = 0; i < n; i++)
		maxheap.insert(arr[i]);

	for (int i = n - 1; i >= 0; i--)
		arr[i] = maxheap.extractMax();

}
template<typename T>
void heapSort2(T arr[], int n) {

	MaxHeap<T> maxheap = MaxHeap<T>(arr, n);

	for (int i = n - 1; i >= 0; i--)
		arr[i] = maxheap.extractMax();

}
template<typename T>
void __shiftDown(T arr[], int k, int n) {

	while (2 * k + 1 < n) {
		int j = 2 * k + 1;
		if (j + 1 < n && arr[j + 1] > arr[j])
			j++;
		if (arr[k] >= arr[j])
			break;
		swap(arr[j], arr[k]);
		k = j;

	}
}
template<typename T>
void __shiftDown2(T arr[], int k, int n) {
	T e = arr[k];
	while (2 * k + 1 <= n) {
		int j = 2 * k;
		if (j + 1 <= n && arr[j + 1] > arr[j])
			j++;
		if (arr[k] >= arr[j])
			break;
		arr[k] = arr[j];
		k = j;

	}
	arr[k] = e;
}
template<typename T>
void heapSort(T arr[], int n) {

	for (int i = (n - 2) / 2; i >= 0; i--) {
		__shiftDown2(arr, i, n);
	}

	for (int i = n - 1; i > 0; i--) {
		swap(arr[i], arr[0]);
		__shiftDown2(arr, 0, i);
	}

}