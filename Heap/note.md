## 堆排序 Heap Sort
算法思想
在堆的数据结构中，堆中的最大值总是位于根节点（在优先队列中使用堆的话堆中的最小值位于根节点）。堆中定义以下几种操作：

- 最大堆调整（Max Heapify）：将堆的末端子节点作调整，使得子节点永远小于父节点
- 创建最大堆（Build Max Heap）：将堆中的所有数据重新排序
- 堆排序（HeapSort）：移除位在第一个数据的根节点，并做最大堆调整的递归运算

首先要创建堆

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
第一种堆排序算法，先将将n个元素逐个插入到空堆里，时间复杂度为O(nlogn)

    template<typename T>
    void heapSort1(T arr[], int n) {
    	MaxHeap<T> maxheap = MaxHeap<T>(n);
    	for (int i = 0; i < n; i++)
    		maxheap.insert(arr[i]);
    	for (int i = n - 1; i >= 0; i--)
    		arr[i] = maxheap.extractMax();
    }

第二种堆排序算法
Heapify创建堆的过程时间复杂度为O(n)，相对来说对第一种速度要快  

    template<typename T>
    void heapSort2(T arr[], int n) {
    	MaxHeap<T> maxheap = MaxHeap<T>(arr,n);
    	for (int i = n - 1; i >= 0; i--)
    		arr[i] = maxheap.extractMax();
    }

###堆排序的优化
原地堆排序  
![](https://upload-images.jianshu.io/upload_images/414598-64a62bec7bb1d235.jpg)
原地堆排序算法不需要开辟额外的空间，也不需要对这些额外的空间进行操作，所以效率更高。  
经过我的实验证明，如果原地队排序用shiftDown1，也就是没有优化过shiftDown,它的效率反而没有前两个好，如果用shiftDown2则会提高了客观的性能。

    template<typename T>
    void __shiftDown(T arr[], int k, int n) {
    
    	while (2 * k +1 < n) {
    		int j = 2 * k+1;
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
    		__shiftDown2(arr,0,i);
    	}
    
    }



## 索引堆 Index Heap
算法思想
可是由于数组中元素位置的改变，我们将面临着几个局限性。  

1. 如果我们的元素是十分复杂的话，比如像每个位置上存的是一篇10万字的文章。那么交换它们之间的位置将产生大量的时间消耗。（不过这可以通过技术手段解决  
2. 由于我们的数组元素的位置在构建成堆之后发生了改变，那么我们之后就很难索引到它，很难去改变它。例如我们在构建成堆后，想去改变一个原来元素的优先级（值），将会变得非常困难。  
3. 可能我们在每一个元素上再加上一个属性来表示原来位置可以解决，但是这样的话，我们必须将这个数组遍历一下才能解决。（性能低效）

针对以上问题，我们就需要引入索引堆（Index Heap）的概念。

对于索引堆来说，我们将数据和索引这两部分分开存储。真正表征堆的这个数组是由索引这个数组构建成的。（像下图中那样，每个结点的位置写的是索引号）
![](https://images2018.cnblogs.com/blog/1307816/201803/1307816-20180315164001854-1182923332.jpg)
而在构建堆（以最大索引堆为例）的时候，比较的是data中的值（即原来数组中对应索引所存的值），构建成堆的却是index域
而构建完之后，data域并没有发生改变，位置改变的是index域。
![](https://images2018.cnblogs.com/blog/1307816/201803/1307816-20180315164217392-1979013270.jpg)

可以添加一个辅助的反向数组，可以更快地找到index索引的值

![](https://i0.hdslb.com/bfs/album/596b9ddd616daf7836b581757b127691203925fd.png@518w_1e_1c.png)

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
    };


###二叉堆 斐波那契堆  

###使用堆实现优先序列
在1000000个元素中选出前100名
