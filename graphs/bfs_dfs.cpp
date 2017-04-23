




class Graph
{
    int V;
    list<int> *adj;
    
public:
    Graph(int V);  // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    void BFS(int s);  // prints BFS traversal from a given source
    void DFS(int v);    // DFS traversal of the vertices reachable from v
    void DFSUtil(int v, bool visited[]);
    void disconnected_DFS();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

Graph:: ~Graph()
{
 for (std::list< int >::iterator it = adj.begin() ; it != adj.end(); ++it)
 {
     delete (*it);
 } 
   adj.clear();   
}
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    
}

/*
 Bread first search for a graph is similar to
 level order traversal of a tree.
 The only difference is that a graph may contain
 cycles and hence we may visit the same vertex again.
 
 To avoid processing a node more than once, we
 will use a boolean visited array.
 */

void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
    
    // Create a queue for BFS
    list<int> queue;
    
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
    
    // 'i' will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;
    
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
        
        
        
        for(i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if(!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}



/*

 Depth first traversal of a graph is similar to
 the depth first traversals of a tree(preorder, inorder, postorder).
 
 The difference is that graph may contain cycles and hence
 we must avoid processing the same node again.
 
 We use a visited array to track vertices that we visited
 and ignore visited vertices when we encounter them again.

 
*/


void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    // Call the recursive helper function to print DFS traversal
    DFSUtil(v, visited);
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";
    
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

/*
 
 For graph figure, refer
 http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/
 */

void bfs()
{
    // Create a graph given in the above diagram
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.addEdge(3, 4);
    
    
    cout << "Following is Breadth First Traversal "
    << "(starting from vertex 2) \n";
    
    g.BFS(3);
    cout<<"\n";
    
    g.BFS(3);
    cout<<"\n";
    
    g.BFS(3);
    cout<<"\n";
}


/* DFS for disconnected graphs */

// The function to do DFS traversal. It uses recursive DFSUtil()
void Graph::disconnected_DFS()
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    // Call the recursive helper function to print DFS traversal
    // starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false) //Note this line.
            DFSUtil(i, visited);
}


void dfs()
{
    cout<<"\n Demonstrating DFS \n";
    
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    
    cout << "Following is Depth First Traversal\n";
    g.DFS(2);
    cout <<" what about a disconnected graph \n";
    g.disconnected_DFS();
    
}
