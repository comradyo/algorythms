#include <iostream>
using namespace std;

/*
Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k. 
Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m). 
n, m ≤ 100000.

Указание. Обходите массив B от конца к началу.

Формат ввода
В первой и второй строке вводятся количество элементов и сами элементы массива A.
В первой и второй строке вводятся количество элементов и сами элементы массива B.
В третьей строке — число k.
*/

int main()
{
	int n = 0;
	cin >> n;
	int* A = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> A[i];
	}

	int m = 0;
	cin >> m;
	int* B = new int[m];
	for (int i = 0; i < m; ++i)
	{
		cin >> B[i];
	}

	int k = 0;
	cin >> k;

	int numOfPairs = 0;

	int i = 0;
	int j = m - 1;
	while (A[i] + B[j] >= k)
	{
		while (B[j] > k && j >= 0)
		{
			j--;
		}
		while (A[i] + B[j] == k && i < n)
		{
			numOfPairs++;
			i++;
		}
		while (A[i] + B[j] > k)
		{
			j--;
		}
	}

	cout << s;

	delete[] A;
	delete[] B;
}