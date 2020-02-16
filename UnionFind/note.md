并查集  Union Find
- 对于一组数据，主要支持两个动作  
- union(p,q)并，连接  
- find(p)查
并查集的基本数据表示
![abc](https://i0.hdslb.com/bfs/album/ddbc5c6e29c9f29eabd9b01359261992f2483576.png@518w_1e_1c.png)   
在同一组的数据具有相同的id

    class UnionFind {
    	private:
    		int *id;
    		int count;
    
    	public:
    		//构造函数
    		UnionFind(int n) {
    			count = n;
    			id = new int[n];
    			for (int i = 0; i < n; i++)
    				id[i] = i;
    		}
    
    		~UnionFind()
    		{
    			delete[] id;
    		}
    		// 查找过程, 查找元素p所对应的集合编号
    		int find(int p) {
    			assert(p >= 0 && p < count);
    			return id[p];
    		}
    
    		// 查看元素p和元素q是否所属一个集合
    		// O(1)复杂度
    		bool isConnected(int p, int q) {
    			return find(p) == find(q);
    		}
    
    		// 合并元素p和元素q所属的集合
    		// O(n) 复杂度
    		void unionElements(int p, int q) {
    
    			int pID = find(p);
    			int qID = find(q);
    
    			if (pID == qID)
    				return;
    
    			// 合并过程需要遍历一遍所有元素, 将两个元素的所属集合编号合并
    			for (int i = 0; i < count; i++)
    				if (id[i] == pID)
    					id[i] = qID;
    		}
    	};
    

###并查集的另一种实现方式
将每一个元素 看作是一个节点
![](https://i0.hdslb.com/bfs/album/64cdfd31e7664b4eb2b9ca78a3f6e0b74953136c.png@518w_1e_1c.png)

    class UnionFind {
    	private:
    		int *parent;
    		int count;
    
    	public:
    		//构造函数
    		UnionFind(int n) {
    			count = n;
    			parent = new int[n];
    			for (int i = 0; i < n; i++)
    				parent[i] = i;
    		}
    
    		~UnionFind()
    		{
    			delete[] parent;
    		}
    		// 查找过程, 查找元素p所对应的集合编号
    		int find(int p) {
    			assert(p >= 0 && p < count);
    			// 不断去查询自己的父亲节点, 直到到达根节点
    			// 根节点的特点: parent[p] == p
    			while (p != parent[p]) {
    				p = parent[p];
    			}
    			return p;
    		}
    
    		// 查看元素p和元素q是否所属一个集合
    		// O(1)复杂度
    		bool isConnected(int p, int q) {
    			return find(p) == find(q);
    		}
    
    		// 合并元素p和元素q所属的集合
    		// O(n) 复杂度
    		void unionElements(int p, int q) {
    
    			int pRoot = find(p);
    			int qRoot = find(q);
    
    			if (pRoot == qRoot)
    				return;
    
    			
    			parent[pRoot] = qRoot;
    		}
    	};


###并查集的优化
####基于size的优化
    class UnionFind {
    	private:
    		int *parent;
    		int *sz;
    		int count;
    
    	public:
    		//构造函数
    		UnionFind(int n) {
    			count = n;
    			parent = new int[n];
    			sz = new int[n];
    			for (int i = 0; i < n; i++) {
    				parent[i] = i;
    				sz[i] = 1;
    			}
    				
    			
    		}
    
    		~UnionFind()
    		{
    			delete[] parent;
    			delete[] sz;
    		}
    		// 查找过程, 查找元素p所对应的集合编号
    		int find(int p) {
    			assert(p >= 0 && p < count);
    			// 不断去查询自己的父亲节点, 直到到达根节点
    			// 根节点的特点: parent[p] == p
    			while (p != parent[p]) {
    				p = parent[p];
    			}
    			return p;
    		}
    
    		// 查看元素p和元素q是否所属一个集合
    		// O(1)复杂度
    		bool isConnected(int p, int q) {
    			return find(p) == find(q);
    		}
    
    		// 合并元素p和元素q所属的集合
    		// O(n) 复杂度
    		void unionElements(int p, int q) {
    
    			int pRoot = find(p);
    			int qRoot = find(q);
    
    			if (pRoot == qRoot)
    				return;
    
    			if (sz[pRoot] > sz[qRoot]) {
    				parent[qRoot] = pRoot;
    				sz[pRoot] += sz[qRoot];
    			}else{
    				parent[pRoot] = qRoot;
    				sz[qRoot] += sz[pRoot];
    			}
    			
    		}
    	};

####基于rank的优化
根据每个树的层数决定要连接的两棵树谁指向谁的根节点

    class UnionFind {
    	private:
    		int *parent;
    		int *rank;
    		int count;
    
    	public:
    		//构造函数
    		UnionFind(int n) {
    			count = n;
    			parent = new int[n];
    			rank = new int[n];
    			for (int i = 0; i < n; i++) {
    				parent[i] = i;
    				rank[i] = 1;
    			}
    
    
    		}
    
    		~UnionFind()
    		{
    			delete[] parent;
    			delete[] rank;
    		}
    		// 查找过程, 查找元素p所对应的集合编号
    		int find(int p) {
    			assert(p >= 0 && p < count);
    			// 不断去查询自己的父亲节点, 直到到达根节点
    			// 根节点的特点: parent[p] == p
    			while (p != parent[p]) {
    				p = parent[p];
    			}
    			return p;
    		}
    
    		// 查看元素p和元素q是否所属一个集合
    		// O(1)复杂度
    		bool isConnected(int p, int q) {
    			return find(p) == find(q);
    		}
    
    		// 合并元素p和元素q所属的集合
    		// O(n) 复杂度
    		void unionElements(int p, int q) {
    
    			int pRoot = find(p);
    			int qRoot = find(q);
    
    			if (pRoot == qRoot)
    				return;
    
    			if (rank[pRoot] > rank[qRoot]) {
    				parent[qRoot] = pRoot;
    			}
    			else if(rank[pRoot] < rank[qRoot]){
    				parent[pRoot] = qRoot;
    			}else{//rank[pRoot] < rank[qRoot]
    				parent[qRoot] = pRoot;
    				rank[pRoot]+=1;
    			}
    
    		}
    	};
    
###路径压缩 path compression
![](https://i0.hdslb.com/bfs/album/90ab6f1f99e516691427d69de252815af7bb3ba5.png@518w_1e_1c.png)

要实现上图的效果，修改find()函数就可以


            int find(int p) {
    			assert(p >= 0 && p < count);
    			// 不断去查询自己的父亲节点, 直到到达根节点
    			// 根节点的特点: parent[p] == p
    			while (p != parent[p]) {
    				parent[p] = parent[parent[p]];
    				p = parent[p];
    			}
    			return p;
    		}



![](https://i0.hdslb.com/bfs/album/1c55f7b81e037988a9e0b450baab52b41f4e8184.png@518w_1e_1c.png)

要实现上图的效果，我们可以运用递归的方式

    // 查找过程, 查找元素p所对应的集合编号
    		int find(int p) {
    			assert(p >= 0 && p < count);
    			// 不断去查询自己的父亲节点, 直到到达根节点
    			// 根节点的特点: parent[p] == p
    			if (p != parent[p]) {
    				parent[p] = find(parent[p]);
    			}
    			return parent[p];
    		}

并查集的操作，时间复杂度近乎为O(1)
