// GraphAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graph.h"
using namespace std;

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
* Print the path from the source to node.
*/
void ShortestPath::printPath(int node, ostream& o) const
{
	if (node == source)
	{
		o << node;
	}
	else if (predecessor[node] == -1)
	{
		o << "No path from " << source << " to " << node << endl;
	}
	else
	{
		printPath(predecessor[node], o);
		o << ".." << node;
	}
}

/*
 * Calculate the average path from the source to all nodes.
*/
int ShortestPath::calculateAverage() const
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
 * Output the result of short path computation to the standard output.
*/
ostream& operator<<(ostream & o, const ShortestPath & path)
{
	o << "Path average: " << path.calculateAverage() << endl;
	o << "Path \t Distance from Source" << endl;
	for (int i = 0; i < path.vCount; i++)
	{
		if (path.distances[i] != Graph::INF) {
			path.printPath(i, o);
			o << '\t' << path.distances[i] << endl;
		}
		else
		{
			o << "Vertex " << path.source << " doesn't have path to " << i << endl;
		}
	}

	return o;
}


/*
 * Allocates memory for adjacency list
 * It doesn't create the graph itself
*/
Graph::Graph(int vCount):vCount(vCount)
{
	adjacent = new vector<vertex>[vCount];
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
	adjacent[u].push_back(make_pair(v,w));
	adjacent[v].push_back(make_pair(u, w));
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
		for (int j = 0; j < adjacent[i].size(); j++)
		{
			cout << "(" << adjacent[i][j].first << "," << adjacent[i][j].second <<")";
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
		for (it = adjacent[u].begin(); it != adjacent[u].end(); it++)
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

/*
 * Calculate minimim spanning tree using Prim algorithm and priority queue.
 * It is similar to the implementation of shortest path algorithm
 * This method also output the resull in following way:
 * - tree as the list of pair: <node> - <parent node>
 * - lenght of the tree
*/
void Graph::primMST()
{
	// Cretae a priority que for the vertex which are not yet in MST
	priority_queue< pVertex, vector<pVertex>, greater<pVertex> > vq;
	//preinitialised vector for keys
	vector<int> keys(vCount, INF);

	//vector of parents for the nodes
	vector<int> parents(vCount, -1);
	vector<bool> inMST(vCount, false);
	//put initial value to the priority queue
	//0 vertex is the starting point 
	vq.push(make_pair(0, 0));
	keys[0] = 0;
	int sum = 0;
	while( !vq.empty() ) 
	{
		//extract vertex with minimum weight from the queue
		int u = vq.top().second;
		if (!inMST[u])
		{
			//add sum only when item is not jet in the MST
			sum += keys[u];
		}
		inMST[u] = true;
		vq.pop();

		for (vector<vertex>::iterator it = adjacent[u].begin(); it != adjacent[u].end(); it++)
		{
			//current adjacent node
			int cur = (*it).first;
			//edge
			int weight = (*it).second;

			if (!inMST[cur] && keys[cur] > weight)
			{
				//update key(minimum weight) of adjacent vertex
				keys[cur] = weight;
				vq.push(make_pair(weight, cur));
				parents[cur] = u;
			}
		}
	}
	//print the tree and minimum sum
	for (int i = 1; i < vCount; i++)
	{
		cout << i << " - " << parents[i] << endl;
	}
	cout << endl << "Minimum MST length: " << sum << endl;
}

