#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/*

Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.

Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми.

Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.

1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

*/

class StringHasher
{
public:
	unsigned int operator()(const string& str) const
	{
		unsigned int hash = 0;
		for (unsigned int i = 0; i < str.size(); ++i)
		{
			hash = hash * 7 + str[i];
		}
		return hash;
	}
};

class Equal
{
public:
	Equal() {}
	const bool operator()(const string& a, const string& b);
};

const bool Equal::operator()(const string& a, const string& b)
{
	return a == b;
}

template<class T, class H, class Equality>
class HashTable
{
public:
	explicit HashTable(const H& _hasher);
	HashTable(const HashTable&) = delete;
	HashTable& operator=(const HashTable&) = delete;
	//Динамического ничего нет
	~HashTable() {};

	bool Add(const T& data);
	bool Has(const T& data);
	bool Delete(const T& data);

private:
	struct HashTableCell
	{
		enum class Status
		{
			EMPTY,
			KEY,
			DELETED
		};

		T data;
		Status state;

		HashTableCell() : state(Status::EMPTY) {}
		~HashTableCell() {}
	};

	void growTable();

	H hasher;
	Equality equal;
	vector<HashTableCell> table;
	unsigned int keysCount;
};

template<class T, class H, class Equality>
HashTable<T, H, Equality>::HashTable(const H& _hasher) : hasher(_hasher), table(8, HashTableCell()), keysCount(0) {}

template<class T, class H, class Equality>
bool HashTable<T, H, Equality>::Add(const T& data)
{
	if ((double)keysCount / (double)table.size() >= 0.75)
	{
		growTable();
	}

	unsigned int absoluteHash = hasher(data);
	unsigned int hash = hasher(data) % table.size();
	//Позиция, на которой ячейка удалена, но в которую можно вставить значение
	int firstDeletedPos = -1;

	for (unsigned int i = 0; i < table.size(); ++i)
	{
		switch (table[hash].state)
		{
		case HashTableCell::Status::DELETED:
			if (firstDeletedPos < 0)
			{
				firstDeletedPos = hash;
			}
			break;
		case HashTableCell::Status::KEY:
			if (equal(table[hash].data, data))
			{
				return false;
			}
			break;
		case HashTableCell::Status::EMPTY:
			if (firstDeletedPos >= 0)
			{
				table[firstDeletedPos].data = data;
				table[firstDeletedPos].state = HashTableCell::Status::KEY;
				keysCount++;
				return true;
			}
			table[hash].data = data;
			table[hash].state = HashTableCell::Status::KEY;
			keysCount++;
			return true;
			break;
		}

		hash = (hash + i + 1) % table.size();
	}

	assert(firstDeletedPos >= 0);
	table[firstDeletedPos].data = data;
	table[firstDeletedPos].state = HashTableCell::Status::KEY;
	keysCount++;
	return true;
}

template<class T, class H, class Equality>
bool HashTable<T, H, Equality>::Has(const T& data)
{
	unsigned int hash = hasher(data) % table.size();
	for (unsigned int i = 0; i < table.size(); i++)
	{

		switch (table[hash].state)
		{
		case HashTableCell::Status::DELETED:
			break;
		case HashTableCell::Status::KEY:
			if (equal(table[hash].data, data))
			{
				return true;
			}
			break;
		case HashTableCell::Status::EMPTY:
			return false;
			break;
		}

		hash = (hash + i + 1) % table.size();
	}
	return false;
}

template<class T, class H, class Equality>
bool HashTable<T, H, Equality>::Delete(const T& data)
{
	unsigned int hash = hasher(data) % table.size();
	for (unsigned int i = 0; i < table.size(); i++)
	{
		switch (table[hash].state)
		{
		case HashTableCell::Status::DELETED:

			break;
		case HashTableCell::Status::KEY:
			if (equal(table[hash].data, data))
			{
				table[hash].state = HashTableCell::Status::DELETED;
				keysCount--;
				return true;
			}
			break;
		case HashTableCell::Status::EMPTY:
			return false;
			break;
		}

		hash = (hash + i + 1) % table.size();
	}
	return false;
}

template<class T, class H, class Equality>
void HashTable<T, H, Equality>::growTable()
{
	vector<HashTableCell> newTable(table.size() * 2, HashTableCell());

	for (unsigned int i = 0; i < table.size(); i++)
	{
		if (table[i].state == HashTableCell::Status::KEY)
		{
			unsigned int hash = hasher(table[i].data) % newTable.size();
			for (unsigned int j = 0; newTable[hash].state == HashTableCell::Status::KEY; j++)
			{
				hash = (hash + j + 1) % newTable.size();
			}
			newTable[hash].data = table[i].data;
			newTable[hash].state = HashTableCell::Status::KEY;
		}
	}
	table = std::move(newTable);
}

int main()
{
	StringHasher hasher;
	HashTable<string, StringHasher, Equal> table(hasher);
	char operation = 0;
	string data;
	while (cin >> operation >> data)
	{
		switch (operation)
		{
		case '+':
			cout << (table.Add(data) ? "OK" : "FAIL") << endl;
			break;
		case '-':
			cout << (table.Delete(data) ? "OK" : "FAIL") << endl;
			break;
		case '?':
			cout << (table.Has(data) ? "OK" : "FAIL") << endl;
			break;
		default:
			assert(false);
		}
	}

	return 0;
}

