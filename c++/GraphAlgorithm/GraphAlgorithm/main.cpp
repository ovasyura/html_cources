#include "graph.h"

using namespace std;

void testDijkstraAlgorithm(int vCount, double density, vector<int>& edges)
{
	cout << "Graph with " << vCount << " nodes and density " << density << endl;   // Add some space to the output

	Graph testGraph(vCount, density, edges);
	//testGraph.outputGraph();

	ShortestPath shortPath = testGraph.shortestPath(0);
	//print output
	//shortPath.outputResult();
	cout << shortPath;
	cout << endl << endl;   // Add some space to the output
}

void mainDijkstraAlgorithm() {
	vector<int> edges(10);
	for (int i = 0; i < 10; i++)
	{
		edges[i] = i + 1;
	}
	testDijkstraAlgorithm(50, 0.2, edges);
	testDijkstraAlgorithm(50, 0.4, edges);
}

//count of vertex
const int V = 7;
const int INFINITE = 2147483647;

//find the index of vertex which is not yet in the MST and has minimum weight
int minKey(int key[], bool mtSet[])
{
	int min = INFINITE;
	int min_index;
	for (int i = 0; i < V; i++)
	{
		if (mtSet[i] == false && key[i] < min) {
			min_index = i;
			min = key[i];
		}
	}
	return min_index;
}

void printMST(int parent[], int count, int graph[V][V])
{
	cout << "Edge\tWeight" << endl;
	int mst = 0;
	for (int i = 1; i < count; i++)
	{
		cout << parent[i] << " - " << i << '\t' << graph[i][parent[i]] << endl;
		mst += graph[i][parent[i]];
	}
	cout << endl << "MST cost: " << mst << endl;
}

void mainPrimMST() {
	//matrix presentation of the graph
	/*int graph[V][V] = {
		{0, 2, 0, 6, 0},
		{2, 0, 3, 8, 5},
		{0, 3, 0, 0, 7},
		{6, 8, 0, 0, 9},
		{0, 5, 7, 9, 0}
	};*/
	int graph[V][V] = {
	{0, 3, 0, 2, 0, 0, 0},
	{3, 0, 5, 2, 0, 0, 0},
	{0, 5, 0, 4, 4, 0, 0},
	{2, 2, 4, 0, 6, 0, 4},
	{0, 0, 4, 6, 0, 5, 5},
	{0, 0, 0, 0, 5, 0, 3},
	{0, 0, 0, 4, 5, 3, 0}
	};

	int parent[V];//store constructed MST
	int key[V]; //store key value for the vertexes
	bool mtSet[V]; //indicate if vertex is included into MST

	//set all key values to INFINITE value
	for (int i = 0; i < V; i++)
	{
		key[i] = INFINITE;
		mtSet[i] = false;
	}

	//set first vertext as starting point
	key[0] = 0;
	parent[0] = -1; //firt is always root

	for (int count = 0; count < V - 1; count++)
	{
		//find vertex with minimum weight which is not yet in the MST
		int u = minKey(key, mtSet);
		mtSet[u] = true;
		//update adjacent vertexes weight which is not in the MST
		for (int v = 0; v < V; v++)
		{
			if (mtSet[v] == false && graph[u][v] && graph[u][v] < key[v])
			{
				parent[v] = u;
				key[v] = graph[u][v];
			}
		}
	}

	printMST(parent, V, graph);
}

//test method for PRIM MST implementation
void testGraphPrim()
{
	Graph g(9);
	//initiate the graph
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);
	g.primMST();
}

void testGraphPrimFromLecture()
{
	Graph g(7);
	//initiate the graph
	g.addEdge(0, 1, 3);
	g.addEdge(0, 3, 2);
	g.addEdge(1, 2, 5);
	g.addEdge(1, 3, 2);
	g.addEdge(2, 3, 4);
	g.addEdge(2, 4, 4);
	g.addEdge(3, 6, 4);
	g.addEdge(3, 4, 6);
	g.addEdge(4, 6, 5);
	g.addEdge(4, 5, 5);
	g.addEdge(6, 5, 3);
	g.primMST();
}

int main()
{

	//mainPrimMST();
	testGraphPrim();
	cout << "Test graph from lecture" << endl;
	testGraphPrimFromLecture();
	return 0;
}
