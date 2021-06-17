#include <iostream>
using namespace std;

/*
Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. 
Вначале вводится количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода по часовой стрелке.
n < 1000, координаты < 10000.

Указание. 
Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей трапеций под каждой стороной многоугольника.
*/

int main()
{
	int n = 0;
	cin >> n;
	int* x = new int[n + 1];
	int* y = new int[n + 1];

	for (int i = 0; i < n; ++i)
	{
		cin >> x[i];
		cin >> y[i];
	}
	x[n] = x[0];
	y[n] = y[0];

	double s = 0;
	int prev = 0;

		int i = 1;
		for(int i = 1; i<=n; ++i)
		{
			if (x[i] >= x[prev])
			{
				s += (x[i] - x[prev]) * (y[i] + y[prev]) / double(2);
				prev = i;
			}
			else
			{
				s -= (x[prev] - x[i]) * (y[prev] + y[i]) / double(2);
				prev = i;
			}
		}

		cout << s;

	delete[] x;
	delete[] y;
}