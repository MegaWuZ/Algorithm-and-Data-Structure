#pragma once
#include <algorithm>
#include <cassert>
using namespace std;

template<typename Item>
class MaxHeap {
private:
	Item* data;
	int count;
	int capacity;
	void shiftUp(int k) {
		while (data[k] > data[k / 2] && k > 1) {
			swap(data[k], data[k / 2]);
			k = k / 2;
		}
	}
	void shiftDown(int k) {
		Item e = data[k];//e 赋值
		int tmp = 0;
		//左孩子不存在时跳出
		while (2 * k <= count) {
			int j = 2 * k;
			if (j + 1 <= count && data[j + 1] > data[j]) {
				j++;
			}
			if (e >= data[j]) {
				break;
			}
			data[k] = data[j];
			k = j;
		}
		data[k] = e;
	}
	/*void shiftDown(int k) {

		while (2*k<=count) {
			int j = 2 * k;
			if (j + 1 <= count && data[j + 1] > data[j])
				j++;
			if (data[k] >= data[j])
				break;
			swap(data[j], data[k]);
			k = j;

		}

	}*/
public:
	MaxHeap(int capacity) {
		data = new Item[capacity + 1];
		count = 0;
		this->capacity = capacity;
	}
	MaxHeap(Item arr[], int n) {
		data = new Item[n + 1];
		capacity = n;
		for (int i = 0; i < n; i++)
			data[i+1] = arr[i];
		count = n;
		for (int i = count / 2; i > 0; i--)
			shiftDown(i);
	}
	~MaxHeap() {
		delete[] data;
	}
	int size() {
		return count;
	}
	bool isEmpty() {
		return count == 0;
	}
	void insert(Item item) {
		assert(count + 1 <= capacity);

		data[count + 1] = item;
		count++;
		shiftUp(count);
	}

	Item extractMax() {
		assert(count > 0);
		Item ret = data[1];
		swap(data[1], data[count]);
		count--;
		shiftDown(1);
		return ret;
	}

	// 获取最大堆中的堆顶元素
	Item getMax() {
		assert(count > 0);
		return data[1];
	}
};