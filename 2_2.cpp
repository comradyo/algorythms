/*
Дано число N и последовательность целых чисел длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root->Key <= K, то узел K добавляется в правое поддерево root; 
иначе в левое поддерево root.

Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

2_2. Выведите элементы в порядке pre-order (сверху вниз).
*/

#include <iostream>
#include <cstdint>
#include <cstring>

#include <assert.h>
#include <string>
#include <sstream>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::stack;

class CompareElements
{
public:
	CompareElements() {}
	const bool operator()(const int& a, const int& b);
};

template<class T, class Comparator>
class BinaryTree
{
public:

	BinaryTree();
	BinaryTree(const BinaryTree& _tree) = delete;
	BinaryTree operator=(const BinaryTree& _tree) = delete;
	~BinaryTree();
	void add(const T& _value);
	void preorderPrint(std::ostream& out);

private:
	class Node
	{
	public:
		Node* left;
		Node* right;
		T value;

		Node();
		Node(T _value);
		~Node();

		void setLeft(Node* _left);
		void setRight(Node* _right);

	};

	Node* root;
	Comparator compare;
};

const bool CompareElements::operator()(const int& a, const int& b)
{
	return a < b ? 1 : 0;
}

template<class T, class Comparator>
BinaryTree<T, Comparator>::BinaryTree() : root(nullptr) {};

template<class T, class Comparator>
BinaryTree<T, Comparator>::~BinaryTree()
{
	stack<Node*> st;
	Node* currentNode = root;

	while (currentNode != nullptr || st.empty() == false)
	{
		while (currentNode != nullptr)
		{
			st.push(currentNode);
			currentNode = currentNode->left;
		}

		currentNode = st.top()->right;
		delete st.top();
		st.top() = nullptr;
		st.pop();
	}

	root = nullptr;
}

template<class T, class Comparator>
void BinaryTree<T, Comparator>::add(const T& _value)
{
	if (root == nullptr)
	{
		root = new Node(_value);
		return;
	}
	Node* currentNode = root;
	Node* parentNode = currentNode;

	while (currentNode != nullptr)
	{
		//val1 < val2
		if (compare(_value, currentNode->value))
		{
			parentNode = currentNode;
			currentNode = currentNode->left;
			if (currentNode == nullptr)
			{
				parentNode->left = new Node(_value);
				return;
			}
		}
		else
		{
			parentNode = currentNode;
			currentNode = currentNode->right;
			if (currentNode == nullptr)
			{
				parentNode->right = new Node(_value);
				return;
			}
		}
	}
}

template<class T, class Comparator>
void BinaryTree<T, Comparator>::preorderPrint(std::ostream& out)
{
	if (root == nullptr)
	{
		return;
	}
	Node* currentNode = root;
	stack<Node*> st;

	while (!st.empty() || currentNode != nullptr)
	{
		while (currentNode != nullptr)
		{
			out << currentNode->value << " ";

			if (currentNode->right != nullptr)
				st.push(currentNode->right);

			currentNode = currentNode->left;
		}
		if (st.empty() == false) 
		{
			currentNode = st.top();
			st.pop();
		}
	}
}

template<class T, class Comparator>
BinaryTree<T, Comparator>::Node::Node() : left(nullptr), right(nullptr), value(T()) {}

template<class T, class Comparator>
BinaryTree<T, Comparator>::Node::Node(T _value) : left(nullptr), right(nullptr), value(_value) {}

template<class T, class Comparator>
BinaryTree<T, Comparator>::Node::~Node()
{
	left = nullptr;
	right = nullptr;
}

template<class T, class Comparator>
void BinaryTree<T, Comparator>::Node::setLeft(Node* _left)
{
	left = _left;
}

template<class T, class Comparator>
void BinaryTree<T, Comparator>::Node::setRight(Node* _right)
{
	right = _right;
}

/*
void test(std::istream& input, std::ostream& output)
{
}

void testQueue()
{
	{
		std::stringstream input;
		std::stringstream output;
		input << "10 7 0 0 0 3 0 0 0 0 2 1";
		test(input, output);
		cout << "TEST 4 print = " << output.str() << endl;
	}
}
*/

int main()
{
	int n = 0;
	cin >> n;
	int x;

	CompareElements compare;
	BinaryTree<int, CompareElements>tree;

	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		tree.add(x);
	}

	tree.preorderPrint(std::cout);

	return 0;
}
