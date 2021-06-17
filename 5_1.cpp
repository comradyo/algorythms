#include <iostream>
#include <cstdint>
#include <cstring>

/*
#include <assert.h>
#include <string>
#include <sstream>
*/

using std::cin;
using std::cout;
using std::endl;

/*
5_1. Реклама.

Необходимо реализовать и использовать сортировку слиянием.
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).

В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа).
Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени.
Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно.
Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
Требуется определить минимальное число показов рекламы.

*/

struct Customer
{
	int entranceTime;
	int exitTime;
};

class CompareCustomers
{
public:
	CompareCustomers(){}
	const bool operator()(const Customer& firstCust, const Customer& secondCust);
};

const bool CompareCustomers::operator()(const Customer& firstCust, const Customer& secondCust)
{
	if (firstCust.exitTime == secondCust.exitTime)
	{
		return firstCust.entranceTime > secondCust.entranceTime;
	}
	return firstCust.exitTime < secondCust.exitTime;
}


template<class T, class Comparator>
void Merge(T* array1, int sizeOfArray1, T* array2, int sizeOfArray2, T* resultArray, Comparator& compare)
{
	int i = 0;
	int j = 0;
	while (i + j < sizeOfArray1 + sizeOfArray2)
	{
		if (i == sizeOfArray1)
		{
			while (j < sizeOfArray2)
			{
				resultArray[i + j] = array2[j];
				j++;
			}
		}
		else if (j == sizeOfArray2)
		{
			while (i < sizeOfArray1)
			{
				resultArray[i + j] = array1[i];
				i++;
			}
		}
		else if (compare(array1[i], array2[j]))
			{
				resultArray[i + j] = array1[i];
				i++;
			}
		else
		{
			resultArray[i + j] = array2[j];
			j++;
		}
	}
}

template<class T, class Comparator>
void MergeSort(T* array, int sizeOfArray, Comparator compare)
{
	if (sizeOfArray <= 1) 
	{
		return;
	}
	int sizeOfLeftPart = sizeOfArray / 2;
	int sizeOfRightPart = sizeOfArray - sizeOfLeftPart;
	MergeSort<T, Comparator>(array, sizeOfLeftPart, compare);
	MergeSort<T, Comparator>(array + sizeOfLeftPart, sizeOfRightPart, compare);
	T* tempArray = new T[sizeOfArray];
	Merge<T, Comparator>(array, sizeOfLeftPart, array + sizeOfLeftPart, sizeOfRightPart, tempArray, compare);
	memcpy(array, tempArray, sizeof(T) * sizeOfArray);
	delete[] tempArray;
}

template<class T>
int GetNumberOfAds(T* arrayOfCustomers, int sizeOfArray)
{
	int firstAdShowTime = arrayOfCustomers[0].exitTime - 1;
	int secondAdShowTime = arrayOfCustomers[0].exitTime;
	int numOfAds = 2;
	bool canMoveTime = true;
	for (int i = 1; i < sizeOfArray; ++i)
	{
		if (arrayOfCustomers[i].entranceTime > secondAdShowTime)
		{
			firstAdShowTime = arrayOfCustomers[i].exitTime - 1;
			secondAdShowTime = arrayOfCustomers[i].exitTime;
			numOfAds += 2;
			canMoveTime = true;
		}
		else if (arrayOfCustomers[i].entranceTime == secondAdShowTime)
		{
			firstAdShowTime = secondAdShowTime;
			secondAdShowTime = arrayOfCustomers[i].exitTime;
			numOfAds++;
			canMoveTime = false;
		}
		else if (arrayOfCustomers[i].entranceTime > firstAdShowTime)
		{
				if (canMoveTime == false)
				{
					firstAdShowTime = secondAdShowTime;
					secondAdShowTime = arrayOfCustomers[i].exitTime;
					numOfAds++;
					//canMoveTime = true;
				}
				else
				{
					firstAdShowTime = arrayOfCustomers[i].entranceTime;
				}
		}
	}
	return numOfAds;
}

/*
void test(std::istream& input, std::ostream& output)
{
	int n = 0;
	input >> n;

	Customer* customers = new Customer[n];

	for (int i = 0; i < n; ++i)
	{
		input >> customers[i].entranceTime;
		input >> customers[i].exitTime;
	}

	MergeSort<Customer, CompareCustomers>(customers, n, CompareCustomers());

	output << GetNumberOfAds(customers, n);

	delete[] customers;
	return;
}

void testQueue()
{
	{
		std::stringstream input;
		std::stringstream output;
		input << "1 1 2";
		test(input, output);
		assert(output.str() == "2");
		cout << "TEST 1 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "2 1 2 1 2";
		test(input, output);
		assert(output.str() == "2");
		cout << "TEST 2 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "2 1 4 2 3";
		test(input, output);
		assert(output.str() == "2");
		cout << "TEST 3 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "2 1 4 5 6";
		test(input, output);
		assert(output.str() == "4");
		cout << "TEST 4 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "2 1 4 3 6";
		test(input, output);
		assert(output.str() == "2");
		cout << "TEST 5 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "3 1 2 2 3 3 4";
		test(input, output);
		assert(output.str() == "4");
		cout << "TEST 6 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "7 2 5 3 7 6 9 2 9 1 10 8 11 5 11";
		test(input, output);
		assert(output.str() == "4");
		cout << "TEST 7 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "8 6 7 2 5 3 13 10 11 3 4 1 9 11 12 3 13";
		test(input, output);
		assert(output.str() == "7");
		cout << "TEST 8 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "5 1 10 10 12 1 10 1 10 23 24";
		test(input, output);
		assert(output.str() == "5");
		cout << "TEST 9 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "10 1 10 10 12 1 10 1 10 23 24 1 10 10 12 1 10 1 10 23 24";
		test(input, output);
		assert(output.str() == "5");
		cout << "TEST 10 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "4 1 5 4 10 4 5 2 8";
		test(input, output);
		assert(output.str() == "2");
		cout << "TEST 11 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "3 1 5 5 10 4 6";
		test(input, output);
		assert(output.str() == "3");
		cout << "TEST 12 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "3 1 5 6 10 4 7";
		test(input, output);
		assert(output.str() == "4");
		cout << "TEST 13 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "8 1 2 1 3 1 4 1 5 2 6 3 6 4 6 5 6";
		test(input, output);
		assert(output.str() == "4");
		cout << "TEST 14 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "4 1 3 2 4 2 5 2 6";
		test(input, output);
		assert(output.str() == "2");
		cout << "TEST 15 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "4 1 2 2 3 3 4 5 6";
		test(input, output);
		assert(output.str() == "6");
		cout << "TEST 16 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "5 1 2 2 3 2 4 2 5 2 6";
		test(input, output);
		assert(output.str() == "3");
		cout << "TEST 17 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "4 1 3 2 5 3 6 4 7";
		test(input, output);
		assert(output.str() == "4");
		cout << "TEST 18 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "4 1 4 2 5 3 6 4 7";
		test(input, output);
		assert(output.str() == "3");
		cout << "TEST 19 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "7 3 5 4 6 5 7 1 7 6 7 7 8 8 9";
		test(input, output);
		assert(output.str() == "6");
		cout << "TEST 20 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "5 1 4 3 5 2 6 4 7 6 8";
		test(input, output);
		assert(output.str() == "4");
		cout << "TEST 21 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "5 1 2 2 4 3 7 4 10 5 12";
		test(input, output);
		assert(output.str() == "5");
		cout << "TEST 22 OK" << endl;
	}
}

*/

int main()
{

	int n = 0;
	cin >> n;

	Customer* customers = new Customer[n];

	for (int i = 0; i < n; ++i)
	{
		cin >> customers[i].entranceTime;
		cin >> customers[i].exitTime;
	}

	MergeSort<Customer, CompareCustomers>(customers, n, CompareCustomers());

	cout << GetNumberOfAds(customers, n);

	delete[] customers;
	return 0;
}