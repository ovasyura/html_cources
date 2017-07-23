// GraphAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <functional>

using namespace std;

//Vertex typedef
//iPair ==>  Integer Pair where first item is the number of the vertex and second is the weight

typedef pair<int, int> vertex;

//priority vertex typedef
//item in priority queue has different meaning for the first and second items
//first is the weight and second the vertex
typedef pair<int, int> pVertex;
class ShortestPath;
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
	vector< vertex > *adjustment;

public:
	Graph(int vCount);
	Graph(int vCount, double density, vector<int>& edges);
	~Graph()
	{
		delete[]adjustment;
	}

	void addEdge(int u, int v, int w);

	void outputGraph();

	ShortestPath shortestPath(int s);
private:

	void createRandomGraph(double density, vector<int>& edges);

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
	int getRandomEdge(vector<int>& edges)
	{
		int i = (double)rand() / (RAND_MAX + 1) * (edges.size());
		return edges[i];
	}
};

/*
 * Class presents the result of Dijkstra algorith computation for the graph.
 * 
*/
class ShortestPath {
	//constructor
public:
	ShortestPath(int vCount, int source, vector<int> distnces, vector<int> predecessor);

public://operations
	void outputResult();

	int calculateAverage();

private:
	void printPath(int node);

private:
	//count of nodes in the graph
	int vCount;
	//start node in the graph which shortest path to another nodes is calculated
	//bu default it is 0(the first node)
	int source = 0;
	//result list of predecessor to help display the result path by nodes
	//The size is equivalent to vCount
	vector<int> predecessor;
	//result list of shortest distance from source node to all another.
	//If nodes cannot be reached from source the value will be Graph.INF
	vector<int> distances;
};

/*
 * Initialize all properties of the class using the result from computation.
 * Claass Graph is responsible to create this class.
 * Maybe it is better to mar this constructor as private and add builder class.
*/
ShortestPath::ShortestPath(int vCount, int source, vector<int> distances, vector<int> predecessor)
	:vCount(vCount), source(source), distances(distances), predecessor(predecessor)
{
}

/*
 * Print the path from the source to node.
*/
void ShortestPath::printPath(int node)
{
	if (node == source)
	{
		cout << node;
	}
	else if (predecessor[node] == -1)
	{
		cout << "No path from " << source << " to " << node << endl;
	}
	else
	{
		printPath(predecessor[node]);
		cout << ".." << node;
	}
}

/*
 * Output the result of short path computation to the standard output.
*/
void ShortestPath::outputResult()
{
	cout << "Path average: " << calculateAverage() << endl;
	cout << "Path \t Distance from Source" << endl;
	for (int i = 0; i < vCount; i++)
	{
		if (distances[i] != Graph::INF) {
			printPath(i);
			cout << '\t' << distances[i] << endl;
		}
		else
		{
			cout << "Vertex " << source << " doesn't have path to " << i << endl;
		}
	}
}

/*
 * Calculate the average path from the source to all nodes.
*/
int ShortestPath::calculateAverage()
{
	int pathAverage = 0;
	for (int i = 0; i<vCount; i++)
	{
		if (distances[i] != Graph::INF)
			pathAverage += distances[i];
	}
	pathAverage /= vCount;
	return pathAverage;
}

/*
 * Allocates memory for adjacency list
 * It doesn't create the graph itself
*/
Graph::Graph(int vCount):vCount(vCount)
{
	adjustment = new vector<vertex>[vCount];
}

/* 
 * Create the graph using density for the roud and potential value of the edges
*/
Graph::Graph(int vCount, double density, vector<int>& edges):Graph(vCount)
{
	createRandomGraph(density, edges);
}

/*
 * Create the random graph using density and available edges.
 * Edge is selected randomly.
*/
void Graph::createRandomGraph(double density, vector<int>& edges)
{
	for (int i = 0; i < vCount; i++)
	{
		for (int j = i + 1; j < vCount; j++) {
				if (isEdge(density))
				{
					//select the edge from the list of available edges and assign to the graph
					addEdge(i, j, getRandomEdge(edges));
				}
		}
	}
}

/*
 * Add edge(u,v) to the graph with distance w(edge)

*/
void Graph::addEdge(int u, int v, int w)
{
	adjustment[u].push_back(make_pair(v,w));
	adjustment[v].push_back(make_pair(u, w));
}

/*
 * Output tthe graph to standard output.
 * This method can be used for testing purpose.
*/
void Graph::outputGraph()
{
	for (int i = 0; i < vCount; i++)
	{
		cout << i << ": ";
		for (int j = 0; j < adjustment[i].size(); j++)
		{
			cout << "(" << adjustment[i][j].first << "," << adjustment[i][j].second <<")";
		}
		cout << endl;
	}
}

/*
 Calculate the shortest path from some source vertex to all another.
 This method returns the list of shortest distances.
 Current implementation creates the duplicated vector but for test task it is enough.
*/
ShortestPath Graph::shortestPath(int vSrc)
{

	int source = vSrc;
	vector<int> distance(vCount, INF);
	vector<int> predecessor(vCount, -1);


	priority_queue< pVertex, vector<pVertex>, greater<pVertex> > vq;

	//put the initail vertex as top with weight 0
	vq.push(make_pair(0, vSrc));
	//instance to the initial vertex is always 0
	distance[vSrc] = 0;

	//loop until priority queue until will not be empty and all vertexes verified
	while (!vq.empty())
	{
		//extract the firt vertex from the queue with minimal distance
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
				predecessor[n] = u;
				vq.push(make_pair(distance[n], n));
			}
		}
	}
	return ShortestPath(vCount, source, distance, predecessor);
}

//Method to test the algorithm
//Just test graph
void testMethod1()
{
	vector<int> edges(6);
	for (int i = 0; i < 6; i++)
	{
		edges[i] = i + 1;
	}
	Graph testGraph(6);
	testGraph.addEdge(0, 1, 2);
	testGraph.addEdge(1, 2, 5);
	testGraph.addEdge(1, 3, 1);
	testGraph.addEdge(1, 4, 5);
	testGraph.addEdge(3, 5, 6);
	testGraph.addEdge(3, 4, 2);
	testGraph.addEdge(3, 5, 2);
	ShortestPath shortPath = testGraph.shortestPath(0);
	//print output
	shortPath.outputResult();

}

//Method to test graph which has some node not connected to source node
void testMethod2()
{
	vector<int> edges(6);
	for (int i = 0; i < 6; i++)
	{
		edges[i] = i + 1;
	}
	Graph testGraph(6);
	testGraph.addEdge(0, 1, 2);
	testGraph.addEdge(1, 2, 5);
	testGraph.addEdge(1, 3, 1);
	testGraph.addEdge(1, 4, 5);
	testGraph.addEdge(3, 4, 2);
	ShortestPath shortPath = testGraph.shortestPath(0);
	//print output
	shortPath.outputResult();

}

void testAlgorithm(int vCount, double density, vector<int>& edges)
{
	cout << "Graph with " << vCount << " nodes and density " << density << endl;   // Add some space to the output

	Graph testGraph(vCount, density, edges);
	//testGraph.outputGraph();

	ShortestPath shortPath = testGraph.shortestPath(0);
	//print output
	shortPath.outputResult();
	cout << endl << endl;   // Add some space to the output
}

int main()
{
	vector<int> edges(10);
	for (int i = 0; i < 10; i++)
	{
		edges[i] = i + 1;
	}

	cout << "It is interesting assignment to be involed in significant graph algorithm." << endl <<
		"But unfortunately I cannot say that lector made enough materials to make assignment without reading additional matherials." << endl <<
		"Especially when we are thinking about priority queue implementation. " << endl <<
		"I have made implementation using STL priority queue and list presentation of the graph." << endl <<
		"It seems that it is the most efisient way to implement this algorithm." << endl <<
		"I have changed the class hierarhy and put algorith implementation to Grph class. "<< endl <<
		"ShortestPath presents the result of computation." <<  endl <<
		"I agree with other guy from the course tthet even this code is in just one file, it's possible to " << endl <<
		"separate it in files so Graph and ShortestPath classes are declared" <<
		" in different cpp and header files, making the project modular.";
	cout << endl << endl;   // Add some space to the output

	testAlgorithm(50, 0.2, edges);
	testAlgorithm(50, 0.4, edges);

	return 0;
}
