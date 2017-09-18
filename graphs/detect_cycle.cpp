// Class for an undirected graph
class Graph
{
	int V; // No. of vertices
	vector<list<int>> adj; // Pointer to an array containing adjacency lists
	bool isCyclicUtil(int v, bool visited[], int parent);
public:
	Graph(int V); // Constructor
	void addEdge(int v, int w); // to add an edge to graph
	bool isCyclic(); // returns true if there is a cycle
};

Graph::Graph(int V)
{
	this->V = V;
	adj.resize(V);
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
	
}

// A recursive function that uses visited[] and parent to detect
// cycle in subgraph reachable from vertex v.
bool Graph::isCyclicUtil(int v, bool visited[], int parent)
{
	// Mark the current node as visited
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		// If an adjacent is not visited, then recur for that adjacent
		if (!visited[*i])
		{
		if (isCyclicUtil(*i, visited, v))
			return true;
		}

		// If an adjacent is visited and not parent of current vertex,
		// then there is a cycle.
		else if (*i != parent)
		return true;
	}
	return false;
}

// Returns true if the graph contains a cycle, else false.
bool Graph::isCyclic()
{
        bool visited[V] = {false}; 
	// Call the recursive helper function to detect cycle in different
	// DFS trees
	for (int u = 0; u < V; u++)
		if (!visited[u]) // Don't recur for u if it is already visited
		if (isCyclicUtil(u, visited, -1))
			return true;

	return false;
}

// Driver program to test above functions
int main()
{
	Graph g1(5);
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 0);
	g1.addEdge(0, 3);
	g1.addEdge(3, 4);
	g1.isCyclic()? cout << "Graph contains cycle\n":
				cout << "Graph doesn't contain cycle\n";

	Graph g2(3);
	g2.addEdge(0, 1);
	g2.addEdge(1, 2);
	g2.isCyclic()? cout << "Graph contains cycle\n":
				cout << "Graph doesn't contain cycle\n";

	return 0;
}
