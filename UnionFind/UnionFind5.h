#pragma once
#include <iostream>
#include <cassert>

using namespace std;
namespace UF5 {
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
			/*while (p != parent[p]) {
				parent[p] = parent[parent[p]];
				p = parent[p];
			}
			return p;*/
			if (p != parent[p]) {
				parent[p] = find(parent[p]);
			}
			return parent[p];
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
			else if (rank[pRoot] < rank[qRoot]) {
				parent[pRoot] = qRoot;
			}
			else {//rank[pRoot] < rank[qRoot]
				parent[qRoot] = pRoot;
				rank[pRoot] += 1;
			}

		}
	};

}