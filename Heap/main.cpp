#include <iostream>
#include<string>
#include <algorithm>
#include "Heap.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "QuickSort2Ways.h"
#include "QuickSort3Ways.h"
#include "SortTestHelper.h"
#include"HeapSort.h"

using namespace std;

template<typename Item>
class IndexMaxHeap {
private:
	Item* data;
	int count;
	int *indexes;
	int *reverse;
	int capacity;
	// ��������, ����֮��ıȽϸ���data�Ĵ�С���бȽ�, ��ʵ�ʲ�����������
	void shiftUp(int k) {

		while (k > 1 && data[indexes[k / 2]] < data[indexes[k]]) {
			swap(indexes[k / 2], indexes[k]);
			reverse[indexes[k / 2]] = k / 2;
			reverse[indexes[k]] = k;
			k /= 2;
		}
	}
	//void shiftDown(int k) {
	//	int temp = k;
	//	Item e = data[k];//e ��ֵ
	//	//���Ӳ�����ʱ����
	//	while (2 * k <= count) {
	//		int j = 2 * k;
	//		if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]]) {
	//			j++;
	//		}
	//		if (e >= data[indexes[j]]) {
	//			break;
	//		}
	//		indexes[k] = indexes[j];
	//		k = j;
	//	}
	//	indexes[k] = temp;
	//}
	void shiftDown(int k) {

		while (2 * k <= count) {
			int j = 2 * k;
			if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]])
				j += 1;

			if (data[indexes[k]] >= data[indexes[j]])
				break;

			swap(indexes[k], indexes[j]);
			reverse[indexes[k]] = k;
			reverse[indexes[j]] = j;
			k = j;
		}
	}
public:
	IndexMaxHeap(int capacity) {
		data = new Item[capacity + 1];
		indexes = new Item[capacity+1];
		reverse = new Item[capacity + 1];
		for (int i = 0; i <= capacity; i++) {
			reverse[i] = 0;
		}
		count = 0;
		this->capacity = capacity;
	}
	
	~IndexMaxHeap() {
		delete[] data;
		delete[] indexes;
		delete[] reverse;
	}
	int size() {
		return count;
	}
	bool isEmpty() {
		return count == 0;
	}
	void insert(int i,Item item) {
		assert(count + 1 <= capacity);
		assert(i+1>=1 && i+1<=capacity);
		i++;
		data[i] = item;
		indexes[count + 1] = i;
		reverse[i] = count + 1;
		count++;
		shiftUp(count);
	}

	Item extractMax() {
		assert(count > 0);
		Item ret = data[indexes[1]];
		swap(indexes[1], indexes[count]);
		reverse[indexes[1]] = 1;
		reverse[indexes[count]] = 0;
		count--;
		shiftDown(1);
		return ret;
	}

	int extractMaxIndex() {
		assert(count > 0);
		int ret = indexes[1] - 1;
		swap(indexes[1], indexes[count]);
		reverse[indexes[1]] = 1;
		reverse[indexes[count]] = 0;
		count--;
		shiftDown(1);
		return ret;
	}

	// ��ȡ�����еĶѶ�Ԫ��
	Item getMax() {
		assert(count > 0);
		return data[1];
	}
	bool contain(int i) {
		assert(i + 1 >= 1 && i + 1 <= capacity);
		return reverse[i + 1] != 0;
	}
	Item getItem(int i) {
		assert(contain(i));
		return data[i+1];
	}

	void change(int i, Item newItem) {
		assert(contain(i));
		i++;
		data[i] = newItem;

		/*for (int j = 1; j <= count; j++) {
			if (indexes[j] == i) {
				shiftUp(j);
				shiftDown(j);
				return;
			}
		}*/

		int j = reverse[i];
		shiftUp(j);
		shiftDown(j);
	}


	// �����������е���������index
   // ע��:�������������в���Ԫ���Ժ�, ������extract������Ч
	bool testIndexes() {

		int *copyIndexes = new int[count + 1];

		for (int i = 0; i <= count; i++)
			copyIndexes[i] = indexes[i];

		copyIndexes[0] = 0;
		std::sort(copyIndexes, copyIndexes + count + 1);

		// �ڶ��������е��������������, Ӧ��������1...count��count������
		bool res = true;
		for (int i = 1; i <= count; i++)
			if (copyIndexes[i - 1] + 1 != copyIndexes[i]) {
				res = false;
				break;
			}

		delete[] copyIndexes;

		if (!res) {
			cout << "Error!" << endl;
			return false;
		}

		return true;
	}
};
// ʹ����������ѽ��ж�����, ����֤���ǵ���������ѵ���ȷ��
// ��������ѵ���Ҫ���ò�����������, ����������ʹ������ֻ��Ϊ����֤���ǵ����������ʵ�ֵ���ȷ��
// �ں�����ͼ����, ��������С�������㷨, �������·���㷨, ���Ƕ���Ҫʹ�������ѽ����Ż�:)
template<typename T>
void heapSortUsingIndexMaxHeap(T arr[], int n) {

	IndexMaxHeap<T> indexMaxHeap = IndexMaxHeap<T>(n);
	for (int i = 0; i < n; i++)
		indexMaxHeap.insert(i, arr[i]);
	assert(indexMaxHeap.testIndexes());

	for (int i = n - 1; i >= 0; i--)
		arr[i] = indexMaxHeap.extractMax();
}
int main() {

	int n = 1000000;

	int* arr = SortTestHelper::generateRandomArray(n, 0, n);
	SortTestHelper::testSort("Heap Sort Using Index-Max-Heap", heapSortUsingIndexMaxHeap, arr, n);
	delete[] arr;



	system("pause");
	return 0;
}