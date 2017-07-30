#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <functional>
#include <string>

//Vertex typedef
//iPair ==>  Integer Pair where first item is the number of the vertex and second is the weight

typedef std::pair<int, int> vertex;

//priority vertex typedef
//item in priority queue has different meaning for the first and second items
//first is the weight and second the vertex
typedef std::pair<int, int> pVertex;
/*
* Class presents the result of Dijkstra algorith computation for the graph.
*
*/
class ShortestPath {
	//constructor
public:
	ShortestPath():vCount(0)
	{
	}
	ShortestPath(int vCount, int source, std::vector<int> distnces, std::vector<int> predecessor);

public://operations
	int calculateAverage() const;
	friend std::ostream& operator <<(std::ostream& o, const ShortestPath& path);
private:
	void printPath(int node);
	void printPath(int node, std::ostream& o) const;

private:
	//count of nodes in the graph
	int vCount;
	//start node in the graph which shortest path to another nodes is calculated
	//bu default it is 0(the first node)
	int source = 0;
	//result list of predecessor to help display the result path by nodes
	//The size is equivalent to vCount
	std::vector<int> predecessor;
	//result list of shortest distance from source node to all another.
	//If nodes cannot be reached from source the value will be Graph.INF
	std::vector<int> distances;
};

/*
* Class to present the graph.
* nodes are presented as edge lists.
* Nodes don't have any symbolic presentation and just numbered from 0 to n-1
*/
class Graph {
public:
	//predefined constant for inifinity
	static const int INF = 0x2f2f2f;

private:
	//count of nodes in the graph
	int vCount;

	//graph is presented as a list 
	//Size of this array is equivalent to count of vertex
	//every item of the array presents the list of adjusted vertex with the weight(edge)
	std::vector< vertex > *adjacent;

public:
	Graph(int vCount);
	Graph(int vCount, double density, std::vector<int>& edges);
	Graph(const std::string& input_file);

	~Graph()
	{
		if (adjacent != nullptr)
			delete[]adjacent;
	}

	void addEdge(int u, int v, int w);

	void outputGraph();

	ShortestPath shortestPath(int s);
	void primMST();
private:

	void createRandomGraph(double density, std::vector<int>& edges);

	//inline function for checking if edge should be added for some vertexes
	bool isEdge(double density)
	{
		if (density == 0.0)
		{
			return false;
		}
		if (density == 1.0)
		{
			return true;
		}

		double probability = (rand() / (double)(RAND_MAX));
		if (probability >= density)
		{
			return true;
		}
		return false;
	}

	//inline function to get random edge from the available edges
	int getRandomEdge(std::vector<int>& edges)
	{
		int i = rand() / (RAND_MAX) * (edges.size());
		return edges[i];
	}
};


