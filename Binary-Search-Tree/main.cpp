#include<iostream>
#include<cassert>
#include<ctime>
#include<queue>
#include"FileOps.h"
#include"SequenceST.h"
using namespace std;
template<typename Key,typename Value>
class  BST
{
private:
	struct Node
	{
		Key key;
		Value value;
		Node *left;
		Node *right;
		Node(Key key,Value value) {
			this->key = key;
			this->value = value;
			this->left = this->right = NULL;
		}
		Node(Node *node) {
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}
	};
	Node *root;
	int count;
  
public:
	BST() {
		root = NULL;
		count = 0;
	}
	~BST() {
	//TODO
		destory(root);
	}
	int size() {
		return count;
	}
	bool isEmpty() {
		return count == 0;
	}
	void insert(Key key, Value value) {
		root = insert(root, key, value);
	}

	bool contain(Key key) {
		return  contain(root, key);
	}
	//Value*可以返回NULL
	Value* search(Key key) {
		return search(root, key);
	}

	void preOrder() {
		preOrder(root);
	}

	// 二分搜索树的中序遍历
	void inOrder() {
		inOrder(root);
	}

	// 二分搜索树的后序遍历
	void postOrder() {
		postOrder(root);
	}
	//二分搜索树的层序遍历
	void levelOrder() {
		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			Node *node = q.front();
			q.pop();

			cout << node->key << endl;
			if (node->left) {
				q.push(node->left);
			}
			if (node->right) {
				q.push(node->right);
			}
		}
	}

	// 寻找二分搜索树的最小的键值
	Key minimum() {
		assert(count != 0);
		Node* minNode = minimum(root);
		return minNode->key;
	}

	// 寻找二分搜索树的最大的键值
	Key maximum() {
		assert(count != 0);
		Node* maxNode = maximum(root);
		return maxNode->key;
	}

	// 从二分搜索树中删除最小值所在节点
	void removeMin() {
		if (root)
			root = removeMin(root);
	}

	// 从二分搜索树中删除最大值所在节点
	void removeMax() {
		if (root)
			root = removeMax(root);
	}

	//从二分搜索树中删除任意节点
	void remove(Key key) {
		if (root)
			root = remove(root,key);
	}

private:
    // 向以node为根的二分搜索树中, 插入节点(key, value), 使用递归算法
	// 返回插入新节点后的二分搜索树的根
		Node * insert(Node *node, Key key, Value value) {

		if (node == NULL) {
			count++;
			return new Node(key, value);
		}

		if (key == node->key)
			node->value = value;
		else if (key < node->key)
			node->left = insert(node->left, key, value);
		else    // key > node->key
			node->right = insert(node->right, key, value);

		return node;
	}

	bool contain(Node* node,Key key) {
		if (node == NULL) {
			return false;
		}

		if (node->key == key) {
			return true;
		}
		else if (node->key > key) {
			return contain(node->left, key);
		}
		else
		{
			return contain(node->right, key);
		}

	}
	Value* search(Node* node, Key key){

		if (node == NULL) {
			return NULL;
		}
		if (node->key == key) {
			return &(node->value);
		}
		else if (node->key > key) {
			return search(node->left, key);
		}
		else
		{
			return search(node->right, key);
		}
	}

	void preOrder(Node* node) {
		if (node != NULL) {
			cout << node->key << endl;
			preOrder(node->left);
			preOrder(node->right);
		
		}
	}


	void inOrder(Node* node) {
		if (node != NULL) {
			
			inOrder(node->left);
			cout << node->key << endl;
			inOrder(node->right);

		}
	}

	void postOrder(Node* node) {
		if (node != NULL) {
			postOrder(node->left);
			postOrder(node->right);
			cout << node->key << endl;
		}
	}

	void destory(Node *node) {
		if (node != NULL) {
			destory(node->left);
			destory(node->right);
			delete node;
			count--;
		}
	}

	Node* minimum(Node *node) {
		if (node->left == NULL) {
			return node;
		}
		minimum(node->left);
	}

	Node* maximum(Node *node) {
		if (node->right == NULL) {
			return node;
		}
		maximum(node->right);
	}

	Node* removeMin(Node* node) {
		if (node->left == NULL) {
			Node* rightNode = node->right;
			delete  node;
			count--;
			return rightNode;
		}
		node->left = removeMin(node->left);
		return node;
	}

	Node*  removeMax(Node* node) {
		if (node->right == NULL) {
			Node* leftNode = node->left;
			delete node;
			count--;
			return leftNode;
		}
		node->right = removeMax(node->right);
		return node;
	}

	Node* remove(Node* node, Key key) {
		if (node == NULL) {
			return NULL;
		}
		if (key < node->key) {
			node->left = remove(node->left, key);
			return node;
		}
		else if(key > node->key){
			node->right = remove(node->right, key);
			return node;
		}else{
			if (node->left == NULL) {
				Node* rightNode = node->right;
				delete node;
				count--;
				return rightNode;
			}
			if (node->right == NULL) {
				Node* leftNode = node->left;
				delete node;
				count--;
				return leftNode;
			}
			Node *successor = new Node(minimum(node->right));
			count++;
			
			successor->left = node->left;
			successor->right = removeMin(node->right);

			delete node;
			count--;
			return successor;
		}
	     
	}

};




int main() {
	// 使用圣经作为我们的测试用例
	//string filename = "bible.txt";
	//vector<string> words;
	//if (FileOps::readFile(filename, words)) {

	//	cout << "There are totally " << words.size() << " words in " << filename << endl;
	//	cout << endl;


	//	// 测试 BST
	//	time_t startTime = clock();

	//	// 统计圣经中所有词的词频
	//	// 注: 这个词频统计法相对简陋, 没有考虑很多文本处理中的特殊问题
	//	// 在这里只做性能测试用
	//	BST<string, int> bst = BST<string, int>();
	//	for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
	//		int *res = bst.search(*iter);
	//		if (res == NULL)
	//			bst.insert(*iter, 1);
	//		else
	//			(*res)++;
	//	}

	//	// 输出圣经中god一词出现的频率
	//	if (bst.contain("god"))
	//		cout << "'god' : " << *bst.search("god") << endl;
	//	else
	//		cout << "No word 'god' in " << filename << endl;

	//	time_t endTime = clock();

	//	cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
	//	cout << endl;


	//	// 测试顺序查找表 SST
	//	startTime = clock();

	//	// 统计圣经中所有词的词频
	//	// 注: 这个词频统计法相对简陋, 没有考虑很多文本处理中的特殊问题
	//	// 在这里只做性能测试用
	//	SequenceST<string, int> sst = SequenceST<string, int>();
	//	for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
	//		int *res = sst.search(*iter);
	//		if (res == NULL)
	//			sst.insert(*iter, 1);
	//		else
	//			(*res)++;
	//	}

	//	// 输出圣经中god一词出现的频率
	//	if (sst.contain("god"))
	//		cout << "'god' : " << *sst.search("god") << endl;
	//	else
	//		cout << "No word 'god' in " << filename << endl;

	//	endTime = clock();

	//	cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
	//}

	BST<int, int> bst = BST<int, int>();

	// 取n个取值范围在[0...m)的随机整数放进二分搜索树中
	int N = 6;
	for (int i = 1; i <= N; i++) {
		int key = i;
		// 为了后续测试方便,这里value值取和key值一样
		int value = key;
		cout << key << " ";
		bst.insert(key, value);
	}
	cout << endl;

	// 测试二分搜索树的size()
	cout << "size: " << bst.size() << endl << endl;

	// 测试二分搜索树的前序遍历 preOrder
	cout << "preOrder: " << endl;
	bst.preOrder();
	cout << endl;

	// 测试二分搜索树的中序遍历 inOrder
	cout << "inOrder: " << endl;
	bst.inOrder();
	cout << endl;

	// 测试二分搜索树的后序遍历 postOrder
	cout << "postOrder: " << endl;
	bst.postOrder();
	cout << endl;

	// 测试二分搜索树的层序遍历 levelOrder
	cout << "levelOrder: " << endl;
	bst.levelOrder();
	cout << endl;

	bst.remove(3);
	cout << "After remove " << endl;
	bst.levelOrder();
	cout<< " size = " << bst.size() << endl;


	system("pause");
	return 0;
}