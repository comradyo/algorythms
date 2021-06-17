#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/*
 * Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
 * A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение.
 * Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A.
 * В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
 * n, k ≤ 10000.
 *
 *Требования: Время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.
 *В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
 * Внимание!
 * В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска,
 * а потом уже в нем делать бинарный поиск.
 */

void arrayInitialization(int* arr, int sizeOfArr)
{
    for (int i = 0; i < sizeOfArr; ++i)
    {
        cin >> arr[i];
    }
}

int binarySearch(int value, int* array, int leftIndex, int rightIndex)
{
    int leftId = leftIndex;
    int rightId = rightIndex;
    while (leftId <= rightId)
    {
        int midId = (leftId + rightId) / 2;
        if (array[midId] == value)
        {
            return midId;
        }
        if (array[midId] < value)
        {
            leftId = midId + 1;
        }
        else {
            rightId = midId - 1;
        }
    }
    return -1;
}

int exponentialSearch(int value, int* array, int arrSize, int leftIndex)
{
    if (array[leftIndex] == value)
    {
        return leftIndex;
    }
    int j = 1;
    while (j + leftIndex < arrSize && array[j + leftIndex] < value)
    {
        j *= 2;
    }
    if (j + leftIndex >= arrSize)
    {
        return binarySearch(value, array, leftIndex, arrSize - 1);
    }
    return binarySearch(value, array, leftIndex, j + leftIndex);
}

struct Array
{
    int* array;
    int sizeOfArray;
};

bool* searchForIntersection(int* firstArr, int sizeOfFirstArr, int* secondArr, int sizeOfSecondArr)
{
    int leftPos = 0;
    int prevLeftPos = 0;

    //По условию sizeOfFirstArr >= sizeOfSecondArr
    bool* arrayOfIntersections = new bool[sizeOfSecondArr];

    for (int i = 0; i < sizeOfSecondArr; ++i)
    {
        leftPos = exponentialSearch(secondArr[i], firstArr, sizeOfFirstArr, leftPos);
        if (leftPos >= 0)
        {
            prevLeftPos = leftPos;
            arrayOfIntersections[i] = true;
        }
        else
        {
            leftPos = prevLeftPos;
            arrayOfIntersections[i] = false;
        }
    }
    return arrayOfIntersections;
}

int main()
{
    int n = 0, m = 0;

    cin >> n;
    int* A = new int[n];
    for (int i = 0; i < n; ++i)
    {
        A[i] = 0;
    }

    cin >> m;
    int* B = new int[m];
    for (int j = 0; j < m; ++j)
    {
        B[j] = 0;
    }

    arrayInitialization(A, n);
    arrayInitialization(B, m);

    bool* isInIntersection = searchForIntersection(A, n, B, m);

    for (int j = 0; j < m; ++j)
    {
        if (isInIntersection[j])
        {
            cout << B[j] << " ";
        }
    }

    delete[] isInIntersection;
    delete[] A;
    delete[] B;

    return 0;
}

