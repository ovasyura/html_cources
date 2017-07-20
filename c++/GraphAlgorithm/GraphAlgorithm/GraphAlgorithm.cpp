// GraphAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <functional>


using namespace std;

//iPair ==>  Integer Pair where first item is the number of the vertex and second is
//is the weight
typedef pair<int, int> vertex;

//priority vertex typef
//item in priority queue has different meaning for the first and second items
//first is the weight and second the vertex
typedef pair<int, int> pVertex;


class Graph {
public:
	//predefined constants for inifinity
	static const int INF = 0x2f2f2f;

private:
	//count of nodes in the graph
	int vCount;

	//graph is presented as a list 
	//Size of this array is equivalent to count of vertex
	//every item of the array presents the list of adjusted vertex with the weight
	vector< vertex > *adjustment;

public:
	Graph(int V);
	~Graph()
	{
		delete []adjustment;
	}

	// function to add an edge to graph
	void addEdge(int u, int v, int w);

	// prints shortest path from s
	vector<int> shortestPath(int s);
};

void Graph::addEdge(int u, int v, int w)
{
	adjustment[u].push_back(make_pair(v,w));
	adjustment[v].push_back(make_pair(u, w));
}

/*
 Calculate the shortest path from some source vertex to all another.
 This method returns the list of shortest distances.
 Current implementation creates the duplicated vector but for test task it is enough.
*/
vector<int> Graph::shortestPath(int vSrc)
{
	vector<int> distance(vCount, INF);

	priority_queue< pVertex, vector<pVertex>, greater<pVertex> > vq;

	//put the initail vertex as top with weight 0
	vq.push(make_pair(0, vSrc));
	//instance to the initial vertex is always 0
	distance[vSrc] = 0;

	//loop until priority bque will not be empty and all vertexes verified
	while (!vq.empty())
	{
		//extract the firt vertex from the que with minimal distance
		int u = vq.top().second;
		vq.pop();
		//iterator is use to iterate by all adjacent vertexes
		vector<vertex>::iterator it;
		for (it = adjustment[u].begin(); it != adjustment[u].end(); it++)
		{
			int n = (*it).first;
			int weight = (*it).second;
			if (distance[n] > distance[u] + weight)
			{
				distance[n] = distance[u] + weight;
				vq.push(make_pair(distance[n], n));
			}
		}

	}
	return distance;
}

// Allocates memory for adjacency list
Graph::Graph(int V)
{
	this->vCount = V;
	adjustment = new vector<vertex>[V];
}

int main()
{
	Graph testGraph(9);
	testGraph.addEdge(0, 1, 4);
	testGraph.addEdge(1, 7, 11);
	testGraph.addEdge(2, 3, 7);
	testGraph.addEdge(2, 5, 4);
	testGraph.addEdge(3, 4, 9);
	testGraph.addEdge(3, 5, 14);
	testGraph.addEdge(4, 5, 10);
	testGraph.addEdge(5, 6, 2);
	testGraph.addEdge(6, 7, 1);

	vector<int> distances = testGraph.shortestPath(1);
	//print output
	for (int i = 0; i < 9; i++)
	{
		if (distances[i] != Graph::INF) {
			cout << i << '\t' << distances[i] << endl;
		}
		else
		{
			cout << "Vertex " << 1 << " doesn't have path to " << i << endl;
		}
	}
	return 0;
}

