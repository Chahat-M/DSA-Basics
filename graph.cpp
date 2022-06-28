// A non-linear data structure
// Undirected and directed graphs - can be implemented using Adjacency list and Adjacency matrix
// Adjacency matrix stores some redundant data, like vertices not connected so not preferred
// Adjacency list is better comparatively - implemented using dynamic sized array or linked list
/* Undirected - 0 <= Edges <= (v * (v-1))/2
   Directed - 0 <= Edges <= v * (v-1)
*/

// Biggest assumption - Value and index of source or any other node is same

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// Adjacency List Implementation for undirected graph
void addEdge_UD(vector<int> adj[], int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// To print the Graph 
void printGraph(vector<int> adj[], int v){
    for(int i = 0; i < v; i++){
        for(int x : adj[i]){
            cout << x << " ";
        }
        cout << endl;
    }
}

// Breadth First Search(BFS)
//------------------------------------------------------------------------------------------------------------------
/* Version 1 - Source given
Print the source, it's immediate connections, then connection's connections and so on
No vertex should be repeated
Time complexity - O(v + E), v = vertices, E = edges
"Edges" bcoz for every u there are x nodes in adjacency list, adding all x 
gives edges in directed graph and 2*edges in undirected graph
Space complexity - O(v)
*/
void BFS1(vector<int> adj[], int v, int source){
    bool visited[v];
    for(int i = 0; i < v; i++)
        visited[i] = false; // Initially no vertex is added to the queue
    queue<int> q;
    q.push(source);
    visited[source] = true; // When added to queue, visited becomes true
    while(q.empty() == false){
        int u = q.front();
        cout << u << " ";
        q.pop();
        for(int x : adj[u]){
            if(visited[x] == false){
                q.push(x);
                visited[x] = true;
            }
        }
    }
}

/* Version 2 - Source not given, graph maybe diconnected as well
Print all vertices in level order, considering any vertex as source
*/
void BFS2(vector<int> adj[], int source, bool visited[]){
    queue<int> q;
    q.push(source);
    visited[source] = true;
    
    while(q.empty() == false){
        int u = q.front();
        cout << u << " ";
        q.pop();
        for(int x : adj[u]){
            if(visited[x] == false){
                q.push(x);
                visited[x] = true;
            }
        }
    }  
}

void BFSDis(vector<int> adj[], int v){
    bool visited[v];
    for(int i = 0; i < v; i++){
        visited[i] = false;
    }
    for(int i = 0; i < v; i++){
        if(visited[i] == false)
            BFS2(adj, i, visited);  // Calling for nodes that are not visited as source 
    }
}
//-----------------------------------------------------------------------------------------------------------------------

// No. of islands in the grpah
/* = Count connected componenets in a graph (can be disconnected graph also)
Minor changes to BFS Version 2
*/
int islandBFS(vector<int> adj[], int v){
    bool visited[v];
    int count = 0;
    for(int i = 0; i < v; i++)
        visited[i] = false;
    for(int i = 0; i < v; i++){
        if(visited[i] == false){
            BFS2(adj, i, visited);  // Since we don't want to print the nodes, omit **cout << u << " "** in BFS2
            count++;
        }
    }
    return count;
}

// Depth First Search (DFS)
/* Version 1 - Source given
Recursively call for 1 adjacent and then for other
Time Complexity - O(V + E); explanation in BFS  
*/
void DFSRec(vector<int> adj[], int source, bool visited[]){
    visited[source] = true;
    cout << source << " ";
    for(int x : adj[source]){   // For next adjacent
        if(visited[x] == false)
            DFSRec(adj, x, visited);
    }
}

// For initialising visited and calling DFSRec()
void DFS(vector<int> adj[], int v, int source){
    bool visited[v];
    for(int i = 0; i < v; i++)
        visited[i] = false;
    DFSRec(adj, source, visited);
}

// Version 2 - For disconnected graph and source not given

void DFSDis(vector<int> adj[], int v){
    bool visited[v];
    for(int i = 0; i < v; i++)
        visited[i] = false;
    for(int i = 0; i < v; i++){
        if(visited[i] == false)
            DFSRec(adj, i, visited);
    }
}

// Count componenets in an undirected graph
// Changes in version 2 itself 
int islandDFS(vector<int> adj[], int v, bool visited[]){
    bool visited[v];
    for(int i = 0; i < v; i++)
        visited[i] = false;
    int count = 0;
    for(int i = 0; i < v; i++){
        if(visited[i] == false){
            DFSRec(adj, v, visited);    // Omit cout << source << " " to avoid printing the graph
            count++;    // Should be written later always
        }
    }
    return count;
}

// Shortest path in an unweighted graph - can be directed or undirected - imp
/* Shortest path from source to all other vertices
*/

void shortestPath(vector<int> adj[], int v, int source){
    int dist[v]; 
    for(int i = 0; i < v; i++)
        dist[i] = INT16_MAX;    // Initialising infinity
    dist[source] = 0;   // Distance of source from source is 0
    bool visited[v];    // if the node is visited or not
    for(int i = 0; i < v; i++)
        visited[i] = false;
    queue<int> q;
    q.push(source);
    visited[source] = true;
    while(q.empty() == false){
        int u = q.front();
        q.pop();
        for(int x : adj[u]){
            if(visited[x] == false){
                dist[x] = dist[u] + 1;  // DFS already takes shortest path
                visited[x] = true;
                q.push(x);
            }
        }
    }
    // Printing desired output
    for(int i = 0; i < v; i++)
        cout << dist[i] << " ";
}

// Detect cycle in an undirected graph
//-----------------------------------------------------------------------------------------------------------------------
/* Main function to detect a cycle, 
If the node is visited again and it's not the same as its origin(parent) 
then there is a cycle
Time complexity - O(v + e)
*/
bool DFS_Ucycle(vector<int> adj[], int i, bool visited[], int parent){
    visited[i] = true;
    for(int u : adj[i]){
        if(visited[u] == false){
            if(DFS_Ucycle(adj, u, visited, i) == true){
                return true;
            }
        }
        else if(u != parent)    // If not the same as its origin 
            return true;
    }
    return false;
}

// Wrapper function to call and detect cycle
bool Ucycle(vector<int> adj[], int v){
    bool visited[v];
    for(int i = 0; i < v; i++)
        visited[i] = false;
    for(int i = 0; i < v; i++){
        if(visited[i] == false){
            if(DFS_Ucycle(adj, i, visited , -1) == true){    // there is a cycle
                return true;
            }
        }
    }
    return false;
} 
//--------------------------------------------------------------------------------------------------------------------------------------

// Detect cycle in a directed graph - imp
//--------------------------------------------------------------------------------------------------------------------------------------
//Time complexity - O(v + e)
bool DFS_Dcycle(vector<int> adj[], int i, bool visited[], bool recStack[]){
    visited[i] = true;
    recStack[i] = true;
    for(int u : adj[i]){
        if(visited[u] == false && DFS_Dcycle(adj, u, visited, recStack))
            return true;
        else if(recStack[u] == true) // Already visited node - ancestor
            return true;
    }
    recStack[i] = false;    // When the recursion for one node/vertex is over, for new node/vertex - new fresh values
    return false;
}

// For covering all vertices
bool Dcycle(vector<int> adj[], int v){
    bool visited[v], recStack[v];
    for(int i = 0; i < v; i++){
        visited[i] = false;
        recStack[i] = false;
    }
    for(int i = 0; i < v ; i++){
        if(visited[i] == false){
            if(DFS_Dcycle(adj, i, visited, recStack) == true)
                return true;
        }
    }
    return false;
} 
//----------------------------------------------------------------------------------------------------------------------------------------

// Topological sorting 
//----------------------------------------------------------------------------------------------------------------------------------------
/* Vertices are jobs and edges are dependencies
Dependent Jobs should appear first followed by the dependencies 
*/
/*Method 1 - BFS approach
*/





int main(){
    int v = 4;
    vector<int> adj[v];
    addEdge_UD(adj, 4, 5);
    addEdge_UD(adj, 4, 2);
    addEdge_UD(adj, 5, 2);
    addEdge_UD(adj, 5, 3);
    addEdge_UD(adj, 2, 3);
    DFS(adj, v, 4);
}