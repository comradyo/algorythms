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



#define MAX_NUMBER_OF_BITS 64

//Извлечение из числа a бита с позицией bit
bool GetBit(const long long& a, int bit)
{
	return (a>>bit) & 1;
}

int BinaryPartition(long long* arr, int left, int right, int bit)
{
	int i = left;
	int j = right;
	while (i != j)
	{
		while (i < j && GetBit(arr[i], bit) == 0)
		{
			i++;
		}
		while (j > i && GetBit(arr[j], bit) == 1)
		{
			j--;
		}
		swap(arr[i], arr[j]);
	}
	//Поскольку в левой части после разделения должны быть нули, а в правой - единицы
	if (GetBit(arr[i], bit) == 1)
	{
		i--;
	}
	return i;
}

//bit - номер бита
void BinaryMsd(long long* arr, int left, int right, int bit)
{
	if (right <= left || bit < 0)
	{
		return;
	}

	int part = BinaryPartition(arr, left, right, bit);

		BinaryMsd(arr, left, part, bit - 1);
		BinaryMsd(arr, part + 1, right, bit - 1);
}

//Необходимо циклически сдвинуть массив, т.к. в конце будут отрицательные числа
/*
	1. Находим позицию первого отрицательного элемента
	2. swap[0, pos), swap[pos, size)
	3. swap[0, size)
*/
void RotateArray(long long* arr, int sizeOfArray)
{
	int posOfFirstNegative = sizeOfArray;
	while (arr[posOfFirstNegative - 1] < 0 && posOfFirstNegative > 0)
	{
		posOfFirstNegative--;
	}
	if (posOfFirstNegative != sizeOfArray && posOfFirstNegative != 0)
	{
		for (int i = 0; i <= (posOfFirstNegative - 1) / 2; ++i)
		{
			swap(arr[i], arr[posOfFirstNegative - i - 1]);
		}
		for (int i = posOfFirstNegative; i <= (posOfFirstNegative + sizeOfArray -1)/2; ++i)
		{
			swap(arr[i], arr[sizeOfArray - (i - posOfFirstNegative) - 1]);
		}
		for (int i = 0; i <= (sizeOfArray - 1)/2; ++i)
		{
			swap(arr[i], arr[sizeOfArray - i - 1]);
		}
	}
}

void test(std::istream& input, std::ostream& output)
{
	int n = 0;
	input >> n;

	long long* array = new long long[n];

	for (int i = 0; i < n; ++i)
	{
		input >> array[i];
	}

	BinaryMsd(array, 0, n - 1, MAX_NUMBER_OF_BITS - 1);
	RotateArray(array, n);

	for (int i = 0; i < n; ++i)
	{
		output << array[i] << " ";
	}
	delete[] array;
	return;
}

void testQueue()
{
	{
		std::stringstream input;
		std::stringstream output;
		input << "3 4 1000000 7";
		test(input, output);
		assert(output.str() == "4 7 1000000 ");
		cout << "TEST 0 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "1 1";
		test(input, output);
		assert(output.str() == "1 ");
		cout << "TEST 1 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "1 -4728312";
		test(input, output);
		assert(output.str() == "-4728312 ");
		cout << "TEST 2 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "4 223 -4728312 252 -52";
		test(input, output);
		assert(output.str() == "-4728312 -52 223 252 ");
		cout << "TEST 3 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "11 1024 512 256 128 64 32 16 8 4 2 1";
		test(input, output);
		assert(output.str() == "1 2 4 8 16 32 64 128 256 512 1024 ");
		cout << "TEST 4 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "11 1023 511 255 127 63 31 15 7 3 1 0";
		test(input, output);
		assert(output.str() == "0 1 3 7 15 31 63 127 255 511 1023 ");
		cout << "TEST 5 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "11 1023 -511 255 127 63 -31 15 7 -3 -1 0";
		test(input, output);
		assert(output.str() == "-511 -31 -3 -1 0 7 15 63 127 255 1023 ");
		cout << "TEST 6 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "10 128 512 127 511 256 1024 127 1023 128 255";
		test(input, output);
		assert(output.str() == "127 127 128 128 255 256 511 512 1023 1024 ");
		cout << "TEST 7 OK" << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "5 1 -2 -1 -3 -4";
		test(input, output);
		assert(output.str() == "-4 -3 -2 -1 1 ");
		cout << "TEST 8 OK" << endl;
	}
}

int main()
{
	testQueue();
	return 0;

	int n = 0;
	cin >> n;

	long long* array = new long long[n];

	for (int i = 0; i < n; ++i)
	{
		cin >> array[i];
	}

	BinaryMsd(array, 0, n - 1, MAX_NUMBER_OF_BITS - 1);
	RotateArray(array, n);

	for (int i = 0; i < n; ++i)
	{
		cout << array[i] << " ";
	}

	delete[] array;
	return 0;
}