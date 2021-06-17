#include <iostream>
using namespace std;

/*
Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1]. 
Необходимо найти первую пару индексов i0 и j0, i0<=j0,
такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
*/

void arrayInitialization(int* arr, int sizeOfArr)
{
	for (int i = 0; i < sizeOfArr; ++i)
		cin >> arr[i];
}

void arrayOutput(int* Arr, int sizeOfArr)
{
	for (int i = 0; i < sizeOfArr; ++i)
		cout << Arr[i] << ' ';
	cout << endl;
}

void prog(int* firstArray, int* secondArray, int sizeOfArray)
{
	int firstArrMaxIndex = 0;
	int firstArrIndex = 0;
	int secondArrIndex = 0;
	int sum = firstArray[firstArrIndex] + secondArray[secondArrIndex];

	for (int i = 1; i < sizeOfArray; ++i)
	{
		if (firstArray[i] > firstArray[firstArrMaxIndex])
		{
			firstArrMaxIndex = i;
		}
		if (secondArray[i] + firstArray[firstArrMaxIndex] > sum)
		{
			firstArrIndex = firstArrMaxIndex;
			secondArrIndex = i;
			sum = firstArray[firstArrIndex] + secondArray[secondArrIndex];
		}
	}
	cout << firstArrIndex << " " << secondArrIndex;
}

int main()
{
	int n = 0;
	cin >> n;
	int* A = new int[n];
	int* B = new int[n];

	for (int i = 0; i < n; ++i)
	{
		A[i] = 0;
		B[i] = 0;
	}

	arrayInitialization(A, n);
	arrayInitialization(B, n);

	prog(A, B, n);

	delete[] A;
	delete[] B;
}