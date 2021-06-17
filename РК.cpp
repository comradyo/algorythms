
/*
#include <iostream>
using std::cin;
using std::cout;

int SearchId(int* mas, int size)
{
	int leftId = 0;
	int rightId = size - 1;

	while (rightId - leftId > 1)
	{
		int midId = (leftId + rightId) / 2;
		if (mas[midId] <= mas[rightId]) 
		{
			rightId = midId;
		}
		else
		{
			leftId = midId;
		}
	}

	return rightId;
}



int main()
{
	int n = 0;
	cin >> n;

	int* mas = new int[n];

	for (int i = 0; i < n; ++i) 
	{
		cin >> mas[i];
	}

	cout << SearchId(mas, n);
	delete[] mas;
}

*/

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;
using std::endl;

struct Node
{
	char c;
	Node* next;
};

class Stack
{
public:

	Stack(): head(nullptr){};

	void Push(char c);
	char Pop();
	bool isEmpty() {
		return head == nullptr;
	}

	~Stack();
private:
	Node* head;
};

bool Check(string s)
{
	Stack St;
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == '(') St.Push(s[i]);
		if (s[i] == ')') {
			if (St.isEmpty()) return 0;
			else if (St.Pop() != '(') return 0;
		}
	}
	if (St.isEmpty())
	{
		return 1;
	}
	return 0;
}

int main()
{
	string s = "";
	cin >> s;
	if (Check(s)) cout << "YES"; else
		cout << "NO";
}

void Stack::Push(char c)
{
	if (head == nullptr)
	{
		head = new Node;
		head->c = c;
		head->next = nullptr;
	}
	else
	{
		Node* newHead = new Node;
		newHead->next = head;
		newHead->c = c;
		head = newHead;
	}
}

char Stack::Pop()
{
	if (head != nullptr) {
		char c = head->c;
		Node* nextHead = head->next;
		delete head;
		head = nextHead;
		return c;
	}
	return ' ';
}

Stack::~Stack()
{
	Node* temp = nullptr;
	while (head != nullptr)
	{
		temp = head;
		head = temp->next;
		delete temp;
	}
}
