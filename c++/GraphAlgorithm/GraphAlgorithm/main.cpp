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

void testGraphPrimFromLecture(string& file) {
	Graph g(file);
	g.primMST();
}

int main()
{
	cout << "Test graph from lecture" << endl;
	testGraphPrimFromLecture();
	return 0;
}
