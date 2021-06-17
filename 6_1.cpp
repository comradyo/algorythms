/*
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. 
Требуется найти k-ю порядковую статистику. 
т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.

Требования: 
к дополнительной памяти: O(n). 
Среднее время работы: O(n). 
Должна быть отдельно выделенная функция partition. 
Рекурсия запрещена.
Решение должно поддерживать передачу функции сравнения снаружи.

Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. 

6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”. 
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>
#include <cstdint>
#include <cstring>


#include <assert.h>
#include <string>
#include <sstream>


using std::cin;
using std::cout;
using std::endl;
using std::swap;

class CompareElements
{
public:
	CompareElements() {}
	const int operator()(const int& a, const int& b);
};

const int CompareElements::operator()(const int& a, const int& b)
{
	return a < b ? 1 : a == b ? 0 : -1;
}

template<class T, class Comparator>
void SetPivot(T* array, int left, int right, Comparator compare)
{
	T& first = array[left];
	T& middle = array[(left + right + 1) / 2];
	T& last = array[right];

	//if ( first <= mid <= last || last <= mid <= first ) => swap(mid, last);
	if (compare(first, middle) >= 0 && compare(middle, last) >= 0 || compare(last, middle) >= 0 && compare(middle, first) >= 0)
	{
		swap(middle, last);
		return;
	}

	//if (mid <= first <= last || last <= first <= mid) => swap(first, last);
	else if (compare(middle, first) >= 0 && compare(first, last) >= 0 || compare(last, first) >= 0 && compare(first, middle) >= 0)
	{
		swap(first, last);
		return;
	}
	
}

// Возвращает индекс, на который встанет пивот после разделения.
template<class T, class Comparator>
int Partition(T* array, int left, int right, Comparator compare) 
{
	if (right - left <= 1)
	{
		return right;
	}
	SetPivot<T, Comparator>(array, left, right, compare);
	T& pivot = array[right];
	int i = left; 
	int j = left;
	while (j < right) 
	{
		//если pivot < array[j], сдвигаем j
		if (compare(pivot, array[j]) > 0)
		{
			j++;
		}
		//если array[j] <= pivot, то swap(array[i], array[j]) и сдвигаем i и j
		else
		{
			swap(array[i++], array[j++]);
		}
	}

	swap(array[i], pivot);
	return i;
}

template<class T, class Comparator>
T FindKStat(T* array, int sizeOfArr, int k, Comparator compare) 
{
	int left = 0;
	int right = sizeOfArr - 1;
	int pivotPos = Partition<T, Comparator>(array, left, right, compare);
	cout << pivotPos << endl;
	/*
	while (pivotPos != k)
	{
		if (pivotPos < k)
		{
			left = pivotPos;
		}
		else
		{
			right = pivotPos;
		}
		pivotPos = Partition<T, Comparator>(array, left, right, compare);
	}
	*/
	return array[pivotPos];
}

/*
void test(std::istream& input, std::ostream& output)
{
	int n = 0;
	int k = 0;
	input >> n;
	input >> k;
	int* array = new int[n];
	for (int i = 0; i < n; ++i)
	{
		input >> array[i];
	}

	cout << "Array: " << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	output << FindKStat<int, CompareElements>(array, n, k, CompareElements());
	//Partition<int, CompareElements>(array, 0, n - 1, CompareElements());
	delete[] array;
	return;
}

void testQueue()
{
	{
		std::stringstream input;
		std::stringstream output;
		//input << "10 9 1 2 3 4 5 6 7 8 9 10";
		input << "10 7 0 0 0 3 0 0 0 0 2 1";
		//input << "7 5 6 5 3 4 1 2 7";
		//input << "3 1 5 4 3";
		test(input, output);
		cout << "TEST 4 Stat = " << output.str() << endl;
	}
}
*/

int main()
{
	int n = 0;
	int k = 0;
	cin >> n;
	cin >> k;

	int* mas = new int[n];

	for (int i = 0; i < n; ++i)
	{
		cin >> mas[i];
	}

	cout << FindKStat<int, CompareElements>(mas, n, k, CompareElements());

	delete[] mas;
	return 0;
}