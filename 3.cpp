#include <iostream>
#include<assert.h>
#include<vector>
#include <queue>
#include <climits>
using std::vector;
using std::queue;
using std::cin;
using std::cout;
using std::endl;
using std::pair;

#include <string>
#include <sstream>


struct Arc
{
	Arc(int _to, int w) : to(_to), weight(w) {};
	int to;
	int weight;
};

class ListGraphWeighted
{
public:
	ListGraphWeighted(int vertexCount);

	virtual void AddEdge(int from, int to, int weight);
	virtual int VertexCount() const;
	virtual vector<Arc> GetNextVertices(int vertex) const;

private:
	vector<vector<Arc>> lists;
};

ListGraphWeighted::ListGraphWeighted(int vertexCount) : lists(vertexCount)
{
}

void ListGraphWeighted::AddEdge(int from, int to, int weight)
{
	assert(from >= 0 && from < lists.size());
	assert(to >= 0 && to < lists.size());

	lists[from].push_back(Arc(to, weight));
}

int ListGraphWeighted::VertexCount() const
{
	return lists.size();
}

vector<Arc> ListGraphWeighted::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < lists.size());
	return lists[vertex];
}

void relax(const int& fromDist, int& toDist, const int& weight)
{
	if (toDist > fromDist + weight)
	{
		toDist = fromDist + weight;
	}
}

int minWay(const ListGraphWeighted& graph, int from, int to)
{
	assert(from >= 0 && from < graph.VertexCount() && to >= 0 && to < graph.VertexCount());

	vector<bool> visited(graph.VertexCount(), false);
	vector<int> distances(graph.VertexCount(), INT_MAX);
	queue<int> bfsQueue;

	bfsQueue.push(from);
	visited[from] = true;
	distances[from] = 0;

	while (bfsQueue.size() > 0)
	{
		int current = bfsQueue.front();
		visited[current] = true;
		bfsQueue.pop();
		vector<Arc> list = graph.GetNextVertices(current);
		for (int i = 0; i < list.size(); ++i)
		{
			relax(distances[current], distances[list[i].to], list[i].weight);
			if (!visited[list[i].to])
			{
				bfsQueue.push(list[i].to);
			}
		}
	}

	return distances[to];
}

void test(std::istream& input, std::ostream& output)
{
	int n = 0;
	//Количество вершин
	input >> n;
	//Количество ребер
	int m = 0;
	input >> m;

	ListGraphWeighted graph(n);

	int from, to, weight;
	for (int i = 0; i < m; ++i)
	{
		input >> from >> to >> weight;
		graph.AddEdge(from, to, weight);
		graph.AddEdge(to, from, weight);
	}

	input >> from >> to;
	output << minWay(graph, from, to);

	return;
}

void testQueue()
{
	{
		std::stringstream input;
		std::stringstream output;
		input << "6 9 ";
		input << "0 3 1 0 4 2 1 2 7 1 3 2 1 4 3 1 5 3 2 5 3 3 4 4 3 5 6 ";
		input << "0 2 ";
		test(input, output);
		cout << "TEST 1 Res = " << output.str() << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "5 6 ";
		input << "0 1 3 ";
		input << "0 4 10 ";
		input << "1 2 1 ";
		input << "1 3 3 ";
		input << "2 3 1 ";
		input << "3 4 2 ";
		input << "0 4 ";
		test(input, output);
		cout << "TEST 2 Res = " << output.str() << endl;
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "8 13 ";
		input << "0 1 1 ";
		input << "0 7 4 ";
		input << "1 7 2 ";
		input << "1 2 6 ";
		input << "2 7 3 ";
		input << "2 6 4 ";
		input << "2 3 10 ";
		input << "3 6 5 ";
		input << "3 5 6 ";
		input << "3 4 14 ";
		input << "4 5 7 ";
		input << "5 6 12 ";
		input << "6 7 8 ";
		input << "0 4 ";
		test(input, output);
		cout << "TEST 3 Res = " << output.str() << endl;
	}
}

int main()
{

	//testQueue();
	//return 0;

	int n = 0;
	//Количество вершин
	cin >> n;
	//Количество ребер
	int m = 0;
	cin >> m;

	ListGraphWeighted graph(n);

	int from, to, weight;
	for (int i = 0; i < m; ++i)
	{
		cin >> from >> to >> weight;
		graph.AddEdge(from, to, weight);
		graph.AddEdge(to, from, weight);
	}

	cin >> from >> to;
	cout << minWay(graph, from, to) << endl;

	return 0;
}