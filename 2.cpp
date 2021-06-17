#include <iostream>
#include<assert.h>
#include<vector>
#include <queue>
using std::vector;
using std::queue;
using std::cin;
using std::cout;
using std::endl;
using std::pair;

struct IGraph
{
	virtual ~IGraph() {}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

	virtual int VertexCount() const = 0;

	virtual vector<int> GetNextVertices(int vertex) const = 0;
	virtual vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph
{
public:
	ListGraph(int vertexCount);
	ListGraph(IGraph& graph);

	virtual void AddEdge(int from, int to) override;
	virtual int VertexCount() const override;
	virtual vector<int> GetNextVertices(int vertex) const override;
	virtual vector<int> GetPrevVertices(int vertex) const override;

private:
	vector<vector<int>> lists;
};

ListGraph::ListGraph(int vertexCount) : lists(vertexCount)
{
}

ListGraph::ListGraph(IGraph& graph) : lists(graph.VertexCount())
{
	for (int i = 0; i < lists.size(); ++i)
	{
		lists[i] = graph.GetNextVertices(i);
	}
}

void ListGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < lists.size());
	assert(to >= 0 && to < lists.size());

	lists[from].push_back(to);
}

int ListGraph::VertexCount() const
{
	return lists.size();
}

vector<int> ListGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < lists.size());
	return lists[vertex];
}

vector<int> ListGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < lists.size());
	vector<int> result;
	for (int from = 0; from < lists.size(); ++from)
	{
		for (int i = 0; i < lists[from].size(); ++i)
		{
			if (lists[from][i] == vertex)
			{
				result.push_back(from);
			}
		}
	}
	return result;
}

struct VertexInfo
{
	VertexInfo(int d, int w) : distance(d), ways(w) {};
	int distance;
	int ways;
};

int numOfMinWays(const IGraph& graph, int from, int to)
{
	assert(from >= 0 && from < graph.VertexCount() && to >= 0 && to < graph.VertexCount());

	vector<bool> visited(graph.VertexCount(), false);
	vector<VertexInfo> vertexes(graph.VertexCount(), VertexInfo(0, 0));

	queue<int> bfsQueue;
	bfsQueue.push(from);
	visited[from] = true;
	vertexes[from].distance = 0;
	vertexes[from].ways = 1;

	while (bfsQueue.size() > 0)
	{
		int current = bfsQueue.front();
		bfsQueue.pop();
		vector<int> list = graph.GetNextVertices(current);
		for (int i = 0; i < list.size(); ++i)
		{
			if (visited[list[i]])
			{
				if (vertexes[list[i]].distance == vertexes[current].distance + 1)
				{
					vertexes[list[i]].ways+= vertexes[current].ways;
				}
			}
			if (!visited[list[i]])
			{
				bfsQueue.push(list[i]);
				visited[list[i]] = true;
				vertexes[list[i]].distance = vertexes[current].distance + 1;
				vertexes[list[i]].ways = vertexes[current].ways;
			}
		}
	}

	return vertexes[to].ways;
}

int main()
{
	int v = 0;
	int n = 0;
	int u = 0;
	int w = 0;

	cin >> v;
	ListGraph graph(v);
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		cin >> u >> w;
		graph.AddEdge(u, w);
		//Поскольку неориентированный
		graph.AddEdge(w, u);
	}

	cin >> u >> w;
	cout << numOfMinWays(graph, u, w) << endl;

	return 0;
}
