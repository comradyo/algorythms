#include <iostream>
#include <assert.h>
using std::cin;
using std::cout;
using std::endl;

/*
Реализовать очередь с динамическим зацикленным буфером.

Обрабатывать команды push back и pop front.

Формат ввода
В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.

a = 2 - pop front
a = 3 - push back

Если дана команда pop front, то число b - ожидаемое значение. 
Если команда pop front вызвана для пустой структуры данных, 
то ожидается “-1”.

Формат вывода
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
*/

template<class T>
class Queue 
{
public:
	Queue();
	Queue(const Queue& q) = delete;
	~Queue();

	Queue& operator = (const Queue&) = delete;

	void PushBack(const T& value);
	T PopFront();
	int Size() const { return sizeOfBuff; };

private:
	int sizeOfBuff;
	int head;
	int tail;
	T* buff;
	void ReallocBuff();
};

template<class T>
Queue<T>::Queue() : buff(nullptr), sizeOfBuff(0), head(-1), tail(-1) {}

template<class T>
Queue<T>::~Queue()
{
	if (buff != nullptr)
	{
		delete[] buff;
	}
	sizeOfBuff = 0;
	head = -1;
	tail = -1;
}

template<class T>
void Queue<T>::PushBack(const T& value)
{
	if (sizeOfBuff == 0)
	{
		ReallocBuff();
	}
	else if (head == (tail + 1) % sizeOfBuff)
	{
		ReallocBuff();
	}
	tail = (tail + 1) % sizeOfBuff;
	buff[tail] = value;
}

template<class T>
T Queue<T>::PopFront()
{
	assert(sizeOfBuff != 0);
	T valueToReturn = buff[head];
	buff[head] = T();
	if (head == tail)
	{
		head = -1;
		tail = -1;
		delete[] buff;
		buff = nullptr;
		sizeOfBuff = 0;
	}
	else 
	{
		head = (head + 1) % sizeOfBuff;
	}
	return valueToReturn;
}

template<class T>
void Queue<T>::ReallocBuff()
{
	if (sizeOfBuff == 0)
	{
		buff = new T[1];
		sizeOfBuff = 1;

		head = 0;
		tail = 0;
	}
	else
	{
		T* tempBuff = new T[sizeOfBuff * 2];
		if (head <= tail) 
		{
			for (int i = head; i <= tail; ++i)
			{
				tempBuff[i - head] = buff[i];
			}
		}
		else
		{
			for (int i = head; i < sizeOfBuff; ++i)
			{
				tempBuff[i - head] = buff[i];
			}
			for (int i = 0; i <= tail; ++i)
			{
				tempBuff[i + sizeOfBuff - head] = buff[i];
			}
		}

		head = 0;
		tail = sizeOfBuff - 1;

		sizeOfBuff *= 2;
		delete[] buff;
		buff = tempBuff;
	}
}

int main()
{

	Queue<int> queue;
	int n = 0;
	cin >> n;
	bool result = true;

	int command = 0;
	int value = 0;

	for (int i = 0; i < n; ++i)
	{
		cin >> command;
		cin >> value;

		switch (command)
		{
		case 2:
		{
			if (queue.Size() == 0)
			{
				result = result && (value == -1);
			}
			else
			{
				result = result && (value == queue.PopFront());
			}
			break;
		}
		case 3:
		{
			queue.PushBack(value);
			break;
		}
		default:
		{
			assert(false);
			break;
		}
		}
	}

	result == true ? cout << "YES" : cout << "NO";

}
