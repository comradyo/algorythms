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

#define DEBUG 1

#if DEBUG == 1

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
	const bool operator()(const int& a, const int& b);
};

const bool CompareElements::operator()(const int& a, const int& b)
{
	return a < b;
}

template<class T, class Comparator>
void SetPivot(T* array, int left, int right, Comparator compare)
{
	T& first = array[left];
	T& middle = array[(left + right + 1) / 2];
	T& last = array[right];

	//if ( first <= mid <= last || last <= mid <= first ) => swap(mid, last);
	if (compare(first, middle) && compare(middle, last) || compare(last, middle) && compare(middle, first))
	{
		swap(middle, last);
		return;
	}

	//if (mid <= first <= last || last <= first <= mid) => swap(first, last);
	else if (compare(middle, first) && compare(first, last) || compare(last, first) && compare(first, middle))
	{
		swap(first, last);
		return;
	}

}

// Возвращает индекс, на который встанет пивот после разделения.
template<class T, class Comparator>
int Partition(T* array, int left, int right, Comparator compare)
{
	if ((right - left) <= 1)
	{
		return left;
	}
	SetPivot<T, Comparator>(array, left, right, compare);
	T& pivot = array[right];
	int i = left;
	int j = left;
	while (j < right)
	{
		//если array[j] < pivot, то swap(array[i], array[j]) и сдвигаем i и j
		if (compare(array[j], pivot))
		{
			swap(array[i++], array[j++]);
		}
		//если pivot <= array[j], сдвигаем j
		else
		{
			j++;
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
	while (pivotPos != k)
	{
		if (pivotPos < k)
		{
			left = pivotPos + 1;
		}
		else
		{
			right = pivotPos;
		}
		pivotPos = Partition<T, Comparator>(array, left, right, compare);
	}
	return array[pivotPos];
}

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

#endif

#if DEBUG == 2

#include <iostream>
#include <time.h>

int partition(int* array, int left, int right) {
	int pivot = rand() % (right - left + 1) + left;
	std::swap(array[pivot], array[right]);

	int i = left;
	int j = left;
	while (j != right) {
		if (array[j] > array[right]) {
			j++;
		}
		else {
			std::swap(array[i], array[j]);
			j++;
			i++;
		}
	}

	std::swap(array[i], array[right]);
	return i;
}

int KStatDC(int* array, int array_size, int key) {
	int left = 0;
	int right = array_size - 1;
	while (true) {
		int result = partition(array, left, right);
		if (result == key) {
			return array[result];
		}
		if (result >= key) {
			right = result;
		}
		else {
			left = result;
		}
	}
}

int main() {
	int n, key = 0;
	std::cin >> n >> key;
	int* array = new int[n];
	int* new_array = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> array[i];
		new_array[i] = array[i];
	}
	for (int i = 0; i < 1; i++) {
		std::cout << KStatDC(array, n, key);
	}
	delete[] array, new_array;
	return 0;
}


#endif