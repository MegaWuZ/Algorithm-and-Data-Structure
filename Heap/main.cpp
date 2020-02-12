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
	// 索引堆中, 数据之间的比较根据data的大小进行比较, 但实际操作的是索引
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
	//	Item e = data[k];//e 赋值
	//	//左孩子不存在时跳出
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

	// 获取最大堆中的堆顶元素
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


	// 测试索引堆中的索引数组index
   // 注意:这个测试在向堆中插入元素以后, 不进行extract操作有效
	bool testIndexes() {

		int *copyIndexes = new int[count + 1];

		for (int i = 0; i <= count; i++)
			copyIndexes[i] = indexes[i];

		copyIndexes[0] = 0;
		std::sort(copyIndexes, copyIndexes + count + 1);

		// 在对索引堆中的索引进行排序后, 应该正好是1...count这count个索引
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
// 使用最大索引堆进行堆排序, 来验证我们的最大索引堆的正确性
// 最大索引堆的主要作用不是用于排序, 我们在这里使用排序只是为了验证我们的最大索引堆实现的正确性
// 在后续的图论中, 无论是最小生成树算法, 还是最短路径算法, 我们都需要使用索引堆进行优化:)
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