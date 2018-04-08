/* Detect cycle in a directed graph using DFS algo */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* Graph Structures */
struct node {
    int vertex;
    struct node *next;
};

struct Graph {
    int numVertex;			// Number of vertices in a graph`
    int *visited;			// array for visited vertices in a graph
    int *recStack;			// Recursive stack
    struct node **adjList;
};

struct node *CreateNode(int value);
struct Graph *CreateGraph(int numOfVertex);
void addEdge(struct Graph *graph, int src, int dest);
void printGraph(struct Graph *graph);
int detectCycleUsingDFS(struct Graph* graph, int v);

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
    graph->recStack = (int*) malloc (numOfVertex * sizeof(int));
	
    graph->adjList = (struct node**) malloc (numOfVertex * sizeof(struct node*));
    int i;
    for(i = 0; i < numOfVertex; i++) 
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;		// Set values in visited list as 0
        graph->recStack[i] = 0;		// Set values in recursive stack list as 0
    }
    return graph;	
}

/* Create a directed Graph */
void addEdge(struct Graph *graph, int src, int dest) {

    // Add edge from src to dest
    struct node *newNode = CreateNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
	
    // Add edge from dest to edge
    //newNode = CreateNode(src);
    //newNode->next = graph->adjList[dest];
    //graph->adjList[dest] = newNode;
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

int detectCycleUsingDFS(struct Graph* graph, int v)
{
    if(graph->visited[v] == 0) 
    {
        struct node* head = graph->adjList[v];
        struct node* tempNode = head;
	
        graph->visited[v] = 1;
        graph->recStack[v] = 1;
        printf("Visited vertex: %d\n", v);
    
        while(tempNode!=NULL) 
        {
            /* Get value of vertex node */
            int u = tempNode->vertex;
            /* Check the vertex is not visited */
            if(graph->visited[u] == 0 && detectCycleUsingDFS(graph, u))
                return 1;         
            else if(graph->recStack[u] == 1)	/* vertex contains in recursive stack */
                return 1;

            /* Traverse the next vertex in adjacency node */
            tempNode = tempNode->next;
        }
    }
    graph->recStack[v] = 0;		// Remove a vertex from a recursive stack
    return 0;
}

int main(int argc, char **argv)
{
    printf("Graph1:\n");
    struct Graph *graph = CreateGraph(4);

    addEdge(graph, 0, 1);    //0->1
    addEdge(graph, 0, 2);    //0->2
    addEdge(graph, 1, 2);    //1->2
    addEdge(graph, 2, 3);    //2->3
    
    printGraph(graph);
    printf("\n");
    
    if (detectCycleUsingDFS(graph, 0) == 1)
    {
        printf("\nGraph contains a cycle");
    }
    else
    {
        printf("\nGraph does not contain any cycle");
    }

/*------------------------------------------------------------------*/    
    printf("\n");
    printf("\nGraph2:\n");
    struct Graph *graph1 = CreateGraph(4);

    addEdge(graph1, 0, 1);    //0->1
    addEdge(graph1, 0, 2);    //0->2
    addEdge(graph1, 1, 2);    //1->2
    addEdge(graph1, 2, 0);    //2->0
    addEdge(graph1, 2, 3);    //2->3
    addEdge(graph1, 3, 3);    //3->3
    
    printGraph(graph1);
    printf("\n");
    
    if (detectCycleUsingDFS(graph1, 0) == 1)
    {
        printf("\nGraph contains a cycle");
    }
    else
    {
        printf("\nGraph does not contain any cycle");
    }
    return 0;
}