#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define INT_MAX 32767

using namespace std;

class Graph
{
    public:
    map<int, map<int, int>> mc_matrix;
    map<int, bool> mc_gateways;
    
    // To be set when computing shortest path
    
    // The output array. dist[i] will hold
    // the shortest distance from src to i
    map<int, int> mc_dist;
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    map<int, bool> mc_sptSet;
    // Parent array to store shortest path tree
    map<int, int> mc_parent;
    
    int m4_vertexNb;
    int m4_edgeNb;
    int m4_gatewayNb;
    
    Graph(int p4_V, int p4_E, int p4_G)
    {
        m4_vertexNb = p4_V;
        m4_edgeNb = p4_E;
        m4_gatewayNb = p4_G;       
        for (int i = 0; i < p4_V; i++) {
            mc_gateways[i] = false;
            for (int j = 0; j < p4_V; j++) {
                mc_matrix[i][j] = 0;
            }
        }
    }
    
    // A utility function to find the vertex with minimum distance
    // value, from the set of vertices not yet included in shortest
    // path tree
    int minDistance()
    {
        // Initialize min value
        int min = INT_MAX, min_index;
     
        for (int v = 0; v < m4_vertexNb; v++)
            if (mc_sptSet[v] == false && mc_dist[v] <= min)
                min = mc_dist[v], min_index = v;
     
        return min_index;
    }
    
    // Function to print shortest path from source to j
    // using parent array
    void printPath(int j)
    {
        // Base Case : If j is source
        if (mc_parent[j]==-1)
            return;
     
        printPath(mc_parent[j]);
     
        cerr << j << " ";
    }
     
    // A utility function to print the constructed distance
    // array
    void printSolution(int src)
    {
        cerr << "Vertex\t  Distance\tPath" << endl;
        for (int i = 1; i < m4_vertexNb; i++)
        {
            cerr << endl << src << " -> " << i << " \t\t" << mc_dist[i] << "\t\t" << src << " ";
            //printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
            printPath(i);
        }
    }
    
    // Funtion that implements Dijkstra's single source shortest path
    // algorithm for a graph represented using adjacency matrix
    // representation
    void dijkstra (int src)
    {
        // Initialize all distances as INFINITE and stpSet[] as false
        
        for (int i = 0; i < m4_vertexNb; i++)
        {
            mc_parent[i] = -1;           
            mc_dist[i] = INT_MAX;
            mc_sptSet[i] = false;
        }        
        
        // Distance of source vertex from itself is always 0
        mc_dist[src] = 0;
        
        // Find shortest path for all vertices
        for (int count = 0; count < m4_vertexNb - 1; count++)
        {
            // Pick the minimum distance vertex from the set of
            // vertices not yet processed. u is always equal to src
            // in first iteration.
            int u = minDistance();
     
            // Mark the picked vertex as processed
            mc_sptSet[u] = true;
     
            // Update mc_dist value of the adjacent vertices of the
            // picked vertex.
            for (int v = 0; v < m4_vertexNb; v++)
            {
                // Update mc_dist[v] only if is not in mc_sptSet, there is
                // an edge from u to v, and total weight of path from
                // src to v through u is smaller than current value of
                // mc_dist[v]
                if (!mc_sptSet[v] && mc_matrix[u][v] &&
                    mc_dist[u] + mc_matrix[u][v] < mc_dist[v])
                {
                    mc_parent[v]  = u;
                    mc_dist[v] = mc_dist[u] + mc_matrix[u][v];
                }  
            }
                
        }   
    }
    
    int getClosestGateway()
    {
        int result = getFirstGateway();
        for (int v = 1; v < m4_vertexNb; v++)
        {
            if(mc_gateways[v] && mc_dist[v] < mc_dist[result])
            {
                cerr << "found " << v << " " << result << endl;
                result = v;
            }
        }
        return result;
    }
    
    int getFirstGateway()
    {
        for (int v = 0; v < m4_vertexNb; v++)
        {
            if(mc_gateways[v])
            {
                return v;
            }
        }
    }
   
};
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
    Graph* lc_graph = new Graph(N, L, E);
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        lc_graph->mc_matrix[N1][N2] = 1;
        lc_graph->mc_matrix[N2][N1] = 1;
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        lc_graph->mc_gateways[EI] = true;
    }

    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        lc_graph->dijkstra(SI);
        lc_graph->printSolution(SI);
        int gtwIdx = lc_graph->getClosestGateway();
        cerr << "gateway index : " << gtwIdx << endl;
        int vertexId1 = gtwIdx;
        int vertexId2 = lc_graph->mc_parent[gtwIdx];
        while (lc_graph->mc_parent[vertexId2] != -1)
        {
            vertexId1 = vertexId2;
            vertexId2 = lc_graph->mc_parent[vertexId2];
        }

        // Example: 0 1 are the indices of the nodes you wish to sever the link between
        cout << vertexId1 << " " << vertexId2 << endl;
        lc_graph->mc_matrix[vertexId1][vertexId2] = 0;
        lc_graph->mc_matrix[vertexId2][vertexId1] = 0;
    }
}
