#include<iostream>
#include<string>
#include"SortTestHelper.h"
#include"InsertionSort.h"
#include"MergeSort.h"
#include"QuickSort.h"
#include"QuickSort2.h"
using namespace std;




template <typename T>
void __quickSort3Ways(T arr[], int l, int r) {

	/*if (l >= r)
		return;*/
	if (r - l < 15) {
		insertionSort(arr, l, r);
		return;
	}
	//partition
	swap(arr[l],arr[rand()%(r-l+1)+l]);
	T v = arr[l];
	int lt = l;
	int gt = r + 1;
	int i = l + 1;
	while (i < gt) {
		if (arr[i] > v ) {
			swap(arr[i], arr[gt - 1]);
			i++;
			gt--;
		}
		else if(arr[i] < v){
			swap(arr[i], arr[lt+1]);
			i++;
			lt++;
		}
		else{
			i++;
		}
	}
	swap(arr[l], arr[lt]);
	__quickSort3Ways(arr,l,lt-1);
	__quickSort3Ways(arr, gt, r);
}

template <typename T>
void QuickSort3Ways(T arr[], int n) {
	srand(time(NULL));
	__quickSort3Ways(arr, 0, n - 1);
}

int main() {

	int n = 1000000;

	// ����1 һ�����
	cout << "Test for random array, size = " << n << ", random range [0, " << n << "]" << endl;

	int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int *arr2 = SortTestHelper::copyIntArray(arr1, n);
	int *arr3 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", MergeSort, arr1, n);
	SortTestHelper::testSort("Quick Sort2", QuickSort2, arr2, n);
	SortTestHelper::testSort("QuickSort3Ways", QuickSort3Ways, arr3, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	// ����2 ���Խ������������
	// ���ڽ������������, ����Խ����, InsertionSort��ʱ������Խ������O(n)
	// ���Կ��Գ���, ��swapTimes�Ƚϴ�ʱ, MergeSort����
	// ���ǵ�swapTimesС��һ���̶�, InsertionSort��ñ�MergeSort��
	int swapTimes = 100;

	cout << "Test for nearly ordered array, size = " << n << ", swap time = " << swapTimes << endl;
	arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	arr3 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Merge Sort", MergeSort, arr1, n);
	SortTestHelper::testSort("Quick Sort2", QuickSort2, arr2, n);
	SortTestHelper::testSort("QuickSort3Ways", QuickSort3Ways, arr3, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;

	// ����3 ���Դ��ڰ���������ͬԪ�ص�����
   // ����ʱ, ���ں��д�����ͬԪ�ص�����, ���ǵĿ��������㷨�ٴ��˻�����O(n^2)������㷨
   // ˼��һ��Ϊʲô�����������, �����˻�����O(n^2)���㷨? :)
    cout<<"Test for random array, size = "<<n<<", random range [0,10]"<<endl;
    arr1 = SortTestHelper::generateRandomArray(n,0,10);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
	arr3 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", MergeSort, arr1, n);
	SortTestHelper::testSort("Quick Sort2", QuickSort2, arr2, n);
	SortTestHelper::testSort("QuickSort3Ways", QuickSort3Ways, arr3, n);

    delete[] arr1;
    delete[] arr2;
	delete[] arr3;
	system("pause");
	return 0;
}