#include <iostream>
#include <assert.h>
#include <string>
#include <sstream>
using std::cin;
using std::cout;
using std::endl;

/*
Дан массив целых чисел A[0..n), n не превосходит 100 000.
Так же задан размер некотрого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n.
Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне.
Скорость работы O(n log n), память O(n).
*/

template<class T>
class Array
{
public:
	Array();
	Array(T* _arr, int _sizeOfArr);
	Array(const Array& _arr) = delete;
	Array(int _sizeOfBuffer);
	~Array();

	Array& operator = (const Array&) = delete;
	T& operator[] (const int index);
	T Last();
	void DeleteLast();

	void PushBack(const T& value);
	//T PopFront();
	int Size() const { return tail + 1; };

private:

	int sizeOfBuff;
	int tail;
	T* buff;
	void ReallocBuff();
};

template<class T>
Array<T>::Array() : buff(nullptr), sizeOfBuff(0), tail(-1) {}

template<class T>
Array<T>::Array(T* _arr, int _sizeOfArr) : sizeOfBuff(_sizeOfArr)
{
	assert(_sizeOfArr > 0 && _arr != nullptr);
	buff = new T[sizeOfBuff];
	for (int i = 0; i < sizeOfBuff; ++i)
	{
		buff[i] = _arr[i];
	}
	tail = sizeOfBuff - 1;
}

template<class T>
Array<T>::Array(int _sizeOfBuffer) : sizeOfBuff(_sizeOfBuffer)
{
	assert(_sizeOfBuffer > 0);
	buff = new T[sizeOfBuff];
	tail = -1;
}

template<class T>
Array<T>::~Array()
{
	if (buff != nullptr)
	{
		delete[] buff;
		buff = nullptr;
	}
	sizeOfBuff = 0;
	tail = 0;
}

template<class T>
T& Array<T>::operator[](const int index)
{
	assert(index <= tail && index >= 0 && buff != nullptr);
	return buff[index];
}

template<class T>
T Array<T>::Last()
{
	assert(sizeOfBuff > 0 && tail >= 0);
	return buff[tail];
}

template<class T>
void Array<T>::DeleteLast()
{
	assert(sizeOfBuff > 0 && tail >= 0);
	buff[tail] = T();
	tail--;
}

template<class T>
void Array<T>::PushBack(const T& value)
{
	if (sizeOfBuff == 0)
	{
		ReallocBuff();
	}
	else if (tail == sizeOfBuff - 1)
	{
		ReallocBuff();
	}
	tail++;
	buff[tail] = value;
}

template<class T>
void Array<T>::ReallocBuff()
{
	if (sizeOfBuff == 0)
	{
		buff = new T[1];
		sizeOfBuff = 1;
	}
	else
	{
		T* tempBuff = new T[sizeOfBuff * 2];
		for (int i = 0; i < sizeOfBuff; ++i)
		{
			tempBuff[i] = buff[i];
		}
		sizeOfBuff *= 2;
		delete[] buff;
		buff = tempBuff;
	}
}


template<class T>
struct Pair
{
	T value;
	int index;

	Pair();
	Pair(T _val, int index);
	Pair(const Pair<T>& _pair);
	~Pair();

	Pair<T>& operator= (const Pair<T>& _pair);

	/*
	bool operator <(const Pair<T>& _pairToCompare) const;
	bool operator >(const Pair<T>& _pairToCompare) const;
	bool operator <=(const Pair<T>& _pairToCompare) const;
	bool operator >=(const Pair<T>& _pairToCompare) const;
	*/
};

template<class T>
Pair<T>::Pair() :value(T()), index(-1) {}

template<class T>
Pair<T>::Pair(T _val, int _ind) : value(_val), index(_ind) {}

template<class T>
Pair<T>::Pair(const Pair<T>& _pair)
{
	this->value = _pair.value;
	this->index = _pair.index;
}

template<class T>
Pair<T>::~Pair()
{
	value = T();
	index = -1;
}

//Пара "значение - индекс", где индекс характеризует положение объекта в введённом массиве
template<class T>
Pair<T>& Pair<T>::operator=(const Pair<T>& _pair)
{
	this->value = _pair.value;
	this->index = _pair.index;
	return *this;
}

/*
template<class T>
bool Pair<T>::operator<=(const Pair<T>& _pairToCompare) const
{
	return this->value <= _pairToCompare.value;
}

template<class T>
bool Pair<T>::operator>=(const Pair<T>& _pairToCompare) const
{
	return this->value >= _pairToCompare.value;
}

template<class T>
bool Pair<T>::operator<(const Pair<T>& _pairToCompare) const
{
	return this->value < _pairToCompare.value;
}

template<class T>
bool Pair<T>::operator>(const Pair<T>& _pairToCompare) const
{
	return this->value > _pairToCompare.value;
}
*/

class ComparePairs
{
public:
	ComparePairs() {}
	const int operator()(const Pair<int>& a, const Pair<int>& b);
};

const int ComparePairs::operator()(const Pair<int>& a, const Pair<int>& b)
{
	return a.value <= b.value;
}

// Структура данных двоичная куча
template<class T, class Comparator>
class Heap 
{
public:
	Heap();
	Heap(T* _arr, int _sizeOfArr, const Comparator& _comparator = Comparator());
	void Insert(const T& value);
	T ExtractMax();
	T PeekMax();
private:
	Comparator compare;
	Array<T> arr;
	void buildHeap();
	void siftDown(int i);
	void siftUp(int i);
};

template<class T, class Comparator>
void Heap<T, Comparator>::buildHeap()
{
	for (int i = arr.Size() / 2 - 1; i >= 0; --i) 
	{
		siftDown(i);
	}
}

template<class T, class Comparator>
void Heap<T, Comparator>::siftDown(int i)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	int largest = i;
	if (left < arr.Size() && compare(arr[left], arr[i]) == false)
	{
		largest = left;
	}
	if (right < arr.Size() && compare(arr[right], arr[largest]) == false)
	{
		largest = right;
	}

	if (largest != i)
	{
		std::swap(arr[i], arr[largest]);
		siftDown(largest);
	}
}

template<class T, class Comparator>
void Heap<T, Comparator>::siftUp(int index)
{
	while (index > 0)
	{
		int parent = (index - 1) / 2;
		if (compare(arr[index], arr[parent]))
		{
			return;
		}
		std::swap(arr[index], arr[parent]);
		index = parent;
	}
}

template<class T, class Comparator>
Heap<T, Comparator>::Heap() : arr() {}

template<class T, class Comparator>
Heap<T, Comparator>::Heap(T* _arr, int _sizeOfArr, const Comparator& _compare) : arr(_arr, _sizeOfArr), compare(_compare)
{
	buildHeap();
}

template<class T, class Comparator>
void Heap<T, Comparator>::Insert(const T& value)
{
	arr.PushBack(value);
	siftUp(arr.Size() - 1);
}

template<class T, class Comparator>
T Heap<T, Comparator>::ExtractMax()
{
	assert(arr.Size() != 0);
	T result = arr[0];
	arr[0] = arr.Last();
	arr.DeleteLast();
	if (arr.Size() != 0) 
	{
		siftDown(0);
	}
	return result;
}

template<class T, class Comparator>
T Heap<T, Comparator>::PeekMax()
{
	assert(arr.Size() != 0);
	return arr[0];
}

int main()
{
	int n = 0;
	int k = 0;
	cin >> n;
	Pair<int>* array = new Pair<int>[n];

	for (int i = 0; i < n; ++i)
	{
		cin >> array[i].value;
		array[i].index = i;
	}

	cin >> k;

	Heap<Pair<int>, ComparePairs> heap(array, k, ComparePairs());
	/*
	for (int i = 0; i < k; ++i)
	{
		heap.Insert(array[i]);
	}
	*/

	cout << heap.PeekMax().value << " ";
	for (int i = k; i < n; ++i)
	{
		heap.Insert(array[i]);
		while (heap.PeekMax().index < i - k + 1)
		{
			heap.ExtractMax();
		}
		cout << heap.PeekMax().value << " ";
	}

	delete[] array;
	return 0;
}