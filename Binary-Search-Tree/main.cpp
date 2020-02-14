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
	//Value*���Է���NULL
	Value* search(Key key) {
		return search(root, key);
	}

	void preOrder() {
		preOrder(root);
	}

	// �������������������
	void inOrder() {
		inOrder(root);
	}

	// �����������ĺ������
	void postOrder() {
		postOrder(root);
	}
	//�����������Ĳ������
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

	// Ѱ�Ҷ�������������С�ļ�ֵ
	Key minimum() {
		assert(count != 0);
		Node* minNode = minimum(root);
		return minNode->key;
	}

	// Ѱ�Ҷ��������������ļ�ֵ
	Key maximum() {
		assert(count != 0);
		Node* maxNode = maximum(root);
		return maxNode->key;
	}

	// �Ӷ�����������ɾ����Сֵ���ڽڵ�
	void removeMin() {
		if (root)
			root = removeMin(root);
	}

	// �Ӷ�����������ɾ�����ֵ���ڽڵ�
	void removeMax() {
		if (root)
			root = removeMax(root);
	}

	//�Ӷ�����������ɾ������ڵ�
	void remove(Key key) {
		if (root)
			root = remove(root,key);
	}

private:
    // ����nodeΪ���Ķ�����������, ����ڵ�(key, value), ʹ�õݹ��㷨
	// ���ز����½ڵ��Ķ����������ĸ�
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
	// ʹ��ʥ����Ϊ���ǵĲ�������
	//string filename = "bible.txt";
	//vector<string> words;
	//if (FileOps::readFile(filename, words)) {

	//	cout << "There are totally " << words.size() << " words in " << filename << endl;
	//	cout << endl;


	//	// ���� BST
	//	time_t startTime = clock();

	//	// ͳ��ʥ�������дʵĴ�Ƶ
	//	// ע: �����Ƶͳ�Ʒ���Լ�ª, û�п��Ǻܶ��ı������е���������
	//	// ������ֻ�����ܲ�����
	//	BST<string, int> bst = BST<string, int>();
	//	for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
	//		int *res = bst.search(*iter);
	//		if (res == NULL)
	//			bst.insert(*iter, 1);
	//		else
	//			(*res)++;
	//	}

	//	// ���ʥ����godһ�ʳ��ֵ�Ƶ��
	//	if (bst.contain("god"))
	//		cout << "'god' : " << *bst.search("god") << endl;
	//	else
	//		cout << "No word 'god' in " << filename << endl;

	//	time_t endTime = clock();

	//	cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
	//	cout << endl;


	//	// ����˳����ұ� SST
	//	startTime = clock();

	//	// ͳ��ʥ�������дʵĴ�Ƶ
	//	// ע: �����Ƶͳ�Ʒ���Լ�ª, û�п��Ǻܶ��ı������е���������
	//	// ������ֻ�����ܲ�����
	//	SequenceST<string, int> sst = SequenceST<string, int>();
	//	for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
	//		int *res = sst.search(*iter);
	//		if (res == NULL)
	//			sst.insert(*iter, 1);
	//		else
	//			(*res)++;
	//	}

	//	// ���ʥ����godһ�ʳ��ֵ�Ƶ��
	//	if (sst.contain("god"))
	//		cout << "'god' : " << *sst.search("god") << endl;
	//	else
	//		cout << "No word 'god' in " << filename << endl;

	//	endTime = clock();

	//	cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
	//}

	BST<int, int> bst = BST<int, int>();

	// ȡn��ȡֵ��Χ��[0...m)����������Ž�������������
	int N = 6;
	for (int i = 1; i <= N; i++) {
		int key = i;
		// Ϊ�˺������Է���,����valueֵȡ��keyֵһ��
		int value = key;
		cout << key << " ";
		bst.insert(key, value);
	}
	cout << endl;

	// ���Զ�����������size()
	cout << "size: " << bst.size() << endl << endl;

	// ���Զ�����������ǰ����� preOrder
	cout << "preOrder: " << endl;
	bst.preOrder();
	cout << endl;

	// ���Զ������������������ inOrder
	cout << "inOrder: " << endl;
	bst.inOrder();
	cout << endl;

	// ���Զ����������ĺ������ postOrder
	cout << "postOrder: " << endl;
	bst.postOrder();
	cout << endl;

	// ���Զ����������Ĳ������ levelOrder
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