/* Adjacency List representations of a un-directed graph */
 
/* Graph representation 
	(0)--------(1)
	 | |        |
	 |   |      |
	 |     |    |
	 |        | |
	(3)--------(2)
*/	

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h> 

struct node
{
    int vertex;
    struct node* next;
};

struct Graph
{
    int numVertices;            // Number of vertex in a graph
    struct node** adjLists;     // Adjacency List pointer
};

/* Create a new node for graph */
struct node* createNode(int);
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);

struct node* createNode(int v)
{
    // Allocate memory for single vertex
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    newNode->vertex = v;    // Set value in new node
    newNode->next = NULL;   // Set next value for newnode as NULL
    return newNode;
}
 
struct Graph* createGraph(int vertices)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices; 
    graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));
 
    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
 
    return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add edge from src to dest (Add at begining)
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
 
    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
 
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main()
{
	/* Create a graph with 4 vertices */
    struct Graph* graph = createGraph(4);
 
    addEdge(graph,0, 1);    //0->1
    addEdge(graph,0, 2);    //0->2
    addEdge(graph,0, 3);    //0->3
    addEdge(graph,1, 2);    //1->2
    addEdge(graph,2, 3);    //2->3
	
    /* Print the graph vertices and edges */
    printGraph(graph);
 
    return 0;
}
