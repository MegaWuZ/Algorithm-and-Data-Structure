

## 选择排序 Selection Sort
算法思想
1. 第一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始位置
2. 然后再从剩余的未排序元素中寻找到最小（大）元素，然后放到已排序的序列的末尾
3. 直到全部待排序的数据元素的个数为零。选择排序是不稳定的排序方法。

        template<typename T>
        void selectionSort(T arr[], int n) {
    	for (int i = 0; i < n; i++) {
    		//寻找(i,n)区间里的最小值
    		int minIndex = i;
    		for (int j = i + 1; j < n; j++) {
    			if (arr[j] < arr[minIndex])
    				minIndex = j;
    		}
    		swap(arr[i], arr[minIndex]);
    	}
        }
缺点：选择排序是一种不稳定的排序算法。

改进后的选择排序算法  
**可以在每一轮循环中同时找到当前数据的最大值和最小值**
    
    template<typename T>
    void selectionSort2(T arr[], int n) {
    	int left = 0, right = n - 1;
    	while (left < right) {
    		int minIndex = left;
    		int maxIndex = right;
    		// 在每一轮查找时, 要保证arr[minIndex] <= arr[maxIndex]
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
  
## 插入排序 Insertion Sort
算法思想
每步将一个待排序的记录，按其关键码值的大小插入前面已经排序的记录中适当位置上，直到全部插入完为止。

插入排序算法

    template<typename T>
    void insertionSort(T arr[], int n) {
    	for (int i = 1; i < n; i++) {
    		//寻找元素arr[i]合适的插入位置//寻找元素arr[i]合适的插入位置
    		for (int j = i; j > 0 && arr[j-1]>a[j]; j--) {
    			swap(arr[j],arr[j-1]);
    		}
    	}
    }



改进后的插入排序算法
**改进后的相对于之前的减少了赋值次数，提高了算法的效率**


    template<typename T>
    void insertionSort(T arr[], int n) {
    	for (int i = 1; i < n; i++) {
    		//寻找元素arr[i]合适的插入位置//寻找元素arr[i]合适的插入位置
    		T e = arr[i];
    		int j;
    		for (j = i; j > 0 && arr[j - 1]>e; j--) {
    			arr[j] = arr[j - 1];
    		}
    		arr[j] = e;
    	}
    }
    
优点：插入排序算法对于有效数组的排序效率高，甚至比时间复杂度为O(NlogN)的排序算法的性能更好。是一种稳定的排序算法。


## 冒泡排序 Bubble Sort#
算法思想
两两比较相邻记录的值，如果反序则交换，直到没有反序的记录为止
    
    template<typename T>
    void bubbleSort(T arr[], int n) {
    	bool swapped;
    	do {
    		swapped = false;
    		for (int i = 1; i < n; i++)
    			if (arr[i - 1] > arr[i]) {
    				swap(arr[i - 1], arr[i]);
    				swapped = true;
    			}
    		// 优化, 每一趟Bubble Sort都将最大的元素放在了最后的位置
    		// 所以下一次排序, 最后的元素可以不再考虑
    		n--;
    	} while (swapped);
    }

改进后的冒泡排序算法

    template<typename T>
    void bubbleSort2(T arr[], int n) {
    	int exchange;
    	do {
    		exchange = 0;
    		for (int i = 1; i < n; i++)
    			if (arr[i - 1] > arr[i]) {
    				swap(arr[i - 1], arr[i]);
    				exchange = i;
    			}
    		n = exchange;
    	} while (exchange > 0);
    }

改进后的冒泡排序算法，会在每一次冒泡结束后**记录下最后一次数据交换的位置**。  
冒泡排序是一种稳定的排序算法。
## 希尔排序 Shell Sort#
算法思想
希尔排序是对直接插入排序的一种改进，改进的着眼点是：


-  若待排序记录按关键码基本有序，直接插入排序的效率很高
-  由于直接排序算法很简单，则在待排序记录个数较少时效率也很高

基本思想是：希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰被分成一组，算法便终止。
    
    template<typename T>
    void shellSort(T arr[], int n) {
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


希尔排序的另一种实现形式

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



