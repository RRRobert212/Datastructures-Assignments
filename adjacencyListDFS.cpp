//adjacenyListDFS.cpp


//Implement a C++ function that uses DFS to check if a graph represented as an adjacency list contains a cycle. Please include your .cpp file in your submission. 


#include <stddef.h>
#include<bits/stdc++.h>
using namespace std;





//building the graph structure using adjaceny list
class Graph{

    //number of vertices in graph
    int n;

    //a pointer to an array of the adjacency lists
    list<int>* adjacenyLists;

public:
    //contstructor
    Graph(int numVertices){

        n = numVertices;
        adjacenyLists = new list<int>[n];
        
    }

    /**
     * function to add an edge to the graph
     * takes i and j, ints representing vertex numbers that the edge goes between
    */
   void addEdge(int i, int j){

    //goes to the list for vertex i, puts j into it, indicating an edge between i and j
    adjacenyLists[i].push_back(j);
   }


    /***
     * performs DFS and keeps a recursion stack which is useful for looking for cycles
     * I did not know what a recursion stack was before researching online
     * but its basically a list of bools that keep track of which vertices are in the current search before backtracking
    */
   bool DFSForCycles(int v, bool visited[], bool* recStack){

        //if a vertex hasn't been visited, mark it as visited, and do DFS
        if(visited[v] == false){
            visited[v] = true;
            //vertex is in current recursion
            recStack[v] = true;

            for(int vertex : adjacenyLists[v]){

                if(!visited[vertex] && DFSForCycles(vertex, visited, recStack))
                    //this recursively calls until the next part happens because we reach one that we HAVE visited
                    return true;

                //if we have visited the vertex already and it is in the recursion stack, this means a cycle is detected
                else if (recStack[vertex])
                    return true;

            }


        }

        //there wasn't a cycle detected, reset it by taking that vertex out of recStack
        recStack[v] = false;
        return false;


   }

   /**
    * cycle detector function
    * uses the DFSForCycles function to see if there are cycles anywhere in the graph
    * tries from each node, this is necessary cause graphs might not be connected
   */

   bool cycleDetector(){

    //set up rec stack and visited stack so its all false
    bool* visited = new bool[n]; //n is number of vertices in graph
    bool* recStack = new bool[n];

    for (int i = 0; i < n; i++){
        visited[i] = false;
        recStack[i] = false;
    }


    //do the DFS starting from each vertex
    for(int i = 0; i< n; i++){
        //if the vertex is unvisited
        if (!visited[i]){
            if (DFSForCycles(i, visited, recStack)){
                //found one!
                return true;
            }
        }

    //it didn't find any
    }
    return false;
   }


};
            
int main(){

    Graph g = Graph(5);

    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(3,4);


    cout << "Checking for cycles in graph g with vertices 0, 1, 2, 3, 4 and edges 0 ->1, 1->2, 3->4 (undirected graph, no cycles should be detected)\n";

    if(g.cycleDetector()){
        cout << "Found a cycle! \n";
    }

    else{cout << "No cycle found! \n";}

    cout << "Checking for cycles in graph m with vertices 0,1,2,3 and edges 0->1, 1->2, 2->0, 3->2 (undirected graph, a cycle should be found)\n";

    Graph m = Graph(4);
    m.addEdge(0,1);
    m.addEdge(1,2);
    m.addEdge(2,0);
    m.addEdge(3,2);

    if(m.cycleDetector()){
        cout << "Found a cycle! \n";
    }

    else{cout << "No cycle found! \n";}

      
                 
   return 0;
            
}
