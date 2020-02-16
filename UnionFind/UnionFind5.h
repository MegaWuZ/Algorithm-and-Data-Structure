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
		//���캯��
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
		// ���ҹ���, ����Ԫ��p����Ӧ�ļ��ϱ��
		int find(int p) {
			assert(p >= 0 && p < count);
			// ����ȥ��ѯ�Լ��ĸ��׽ڵ�, ֱ��������ڵ�
			// ���ڵ���ص�: parent[p] == p
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

		// �鿴Ԫ��p��Ԫ��q�Ƿ�����һ������
		// O(1)���Ӷ�
		bool isConnected(int p, int q) {
			return find(p) == find(q);
		}

		// �ϲ�Ԫ��p��Ԫ��q�����ļ���
		// O(n) ���Ӷ�
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