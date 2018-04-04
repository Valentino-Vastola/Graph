/* FFS for a graph */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* Graph Structures */
struct node 
{
    int vertex;
    struct node *next;
};

struct Graph {
    int numVertex;			// Number of vertices in a graph`
    int *visited;			// array for visited vertices in a graph
    struct node **adjList;
};

/* Graph Operations */
/* Create a vertex node */
struct node *CreateNode(int value);
/* Create a graph */
struct Graph *CreateGraph(int numOfVertex);
void addEdge(struct Graph *graph, int src, int dest);
void printGraph(struct Graph *graph);
/* Breadth First Search function */
int cycleSearchDFS(struct Graph* graph, int v, int parent);

/* Graph Operations */
struct node *CreateNode(int value)
{
    /* Create a new node */
    struct node *newNode = (struct node*) malloc (sizeof(struct node));
    newNode->vertex = value;
    newNode->next = NULL;	
    return newNode;
}

struct Graph *CreateGraph(int numOfVertex) {
    struct Graph *graph = (struct Graph*) malloc (sizeof(struct Graph));
    graph->numVertex = numOfVertex;
    graph->visited = (int*) malloc (numOfVertex * sizeof(int));
	
    graph->adjList = (struct node**) malloc (numOfVertex * sizeof(struct node*));
    int i;
    for(i = 0; i < numOfVertex; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;		// Set values in visited list as 0
    }
    return graph;	
}

void addEdge(struct Graph *graph, int src, int dest) {
    // Add edge from src to dest
    struct node *newNode = CreateNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
	
    // Add edge from dest to edge
    newNode = CreateNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void printGraph(struct Graph* graph) {
    int v;
    for(v = 0; v < graph->numVertex; v++)
    {
        struct node* temp = graph->adjList[v];
        printf("\n Adjacency list of vertex: %d-> ", v);
        while(temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}


/* 
   Condition: Check if cycle exist in a undirected graph using DFS Algo
   --------------------------------------------------------------------
   For every vertex 'v', if there is an adjacent 'u' such that 'u'
   is already visited and 'u' is not parent of 'v', then there is
   a cycle in graph. 
*/
int cycleSearchDFS(struct Graph* graph, int v, int parent)
{
    struct node* head = graph->adjList[v];
    struct node* tempNode = head;
	
    graph->visited[v] = 1;
    printf("Visited vertex: %d\n", v);
    
    while(tempNode!=NULL) 
    {
        /* Get value of vertex node */
        int u = tempNode->vertex;
        /* Check the vertex is not visited */
        if(graph->visited[u] == 0) {
            if (cycleSearchDFS(graph, u, v))
                return 1;
        }
        else
        {
            if(u != parent)
                return 1;
		}
        /* Traverse the next vertex in adjacency node */
        tempNode = tempNode->next;
    }
    return 0;
}

int main(int argc, char **argv)
{
    printf("Graph1:\n")
    struct Graph *graph = CreateGraph(4);

    addEdge(graph, 0, 1);    //0->1
    addEdge(graph, 0, 2);    //0->2
    addEdge(graph, 0, 3);    //0->3
    addEdge(graph, 1, 2);    //1->2
    addEdge(graph, 2, 3);    //2->3
    
    printGraph(graph);
    printf("\n");
    
    if (cycleSearchDFS(graph, 0, -1) == 1)
    {
        printf("\nGraph contains a cycle");
    }
    else
    {
        printf("\nGraph does not contain any cycle");
    }
    
    printf("\n");
    printf("Graph2:\n")
    struct Graph *g1 = CreateGraph(5);
    addEdge(g1,1, 0);
    addEdge(g1,0, 2);
    addEdge(g1,2, 1);
    addEdge(g1,0, 3);
    addEdge(g1,3, 4);
    
    printGraph(g1);
    printf("\n");
    
    if (cycleSearchDFS(g1, 3, -1) == 1)
    {
        printf("\nGraph contains a cycle");
    }
    else
    {
        printf("\nGraph does not contain any cycle");
    }
    return 0;
}