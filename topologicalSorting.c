/* Topologival sort for Directed Acyclic Graph (DAG) graph using DFS algo */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define STACK_SIZE 20

/* Graph Structures */
struct node {
    int vertex;
    struct node *next;
};

struct Graph {
    int numVertex;			// Number of vertices in a graph`
    int *visited;			// array for visited vertices in a graph
    struct node **adjList;
};

struct Stack {
    int item[STACK_SIZE];
    int top;
};

struct Stack *CreateStack();
void push(struct Stack *stack, int value);
int pop(struct Stack *s);
int isEmpty(struct Stack *s);
int isFull(struct Stack *s);
void displayStack(struct Stack *s);

struct Stack *CreateStack()
{
    struct Stack *s = (struct Stack*) malloc (STACK_SIZE * sizeof(struct Stack));
    s->top = -1;
	return s;
}

int isEmpty(struct Stack* s)
{
    if(s->top == -1)
        return 1;
    else
        return 0;
}

int isFull(struct Stack* s)
{
    if(s->top >= STACK_SIZE-1)
        return 1;
    else
        return 0;
}

void push(struct Stack* s, int value)
{
    if(isFull(s))
    {
        printf("\nStack is full\n");
        return;
	}
    else {
        s->top++;
        s->item[s->top] = value;
    }
}

int pop(struct Stack* s)
{
    //int popValue;
    if(isEmpty(s)) {
        printf("\nStack is empty\n");
    }
    else
    {
        s->top--;
        return (s->item[s->top]);
    }
}

struct node *CreateNode(int value);
struct Graph *CreateGraph(int numOfVertex);
void addEdge(struct Graph *graph, int src, int dest);
void printGraph(struct Graph *graph);
int topologicalSortUsingDFS(struct Graph* graph, int v, struct Stack *s);

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
    for(i = 0; i < numOfVertex; i++) 
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;		// Set values in visited list as 0
    }
    return graph;	
}

/* Create a directed Graph */
void addEdge(struct Graph *graph, int src, int dest) {

    // Add edge from src to dest
    struct node *newNode = CreateNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
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

int topologicalSortUsingDFS(struct Graph* graph, int v, struct Stack *s)
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
        if(graph->visited[u] == 0)
            topologicalSortUsingDFS(graph, u, s);
        /* Traverse the next vertex in adjacency node */
        tempNode = tempNode->next;
    }
    push(s,v);

    return 0;
}


/* Print stack value for topologival sort */
void displayStack(struct Stack *s)
{
    int i;
    if (s->top == -1)
    {
        printf ("Stack is empty\n");
        return;
    }
    else
    {
        printf ("\n Topological Sort of the given graph \n");
        for (i = s->top; i >= 0; i--)
        {
            printf ("%d ", s->item[i]);
        }
    }
    printf ("\n");
}

int main(int argc, char **argv)
{
    printf("Graph1:\n");
    struct Graph *graph = CreateGraph(6);

    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);
    
    printGraph(graph);
    printf("\n");
    
    struct Stack *s = CreateStack();
    
    int i;
    for(i = 0; i < graph->numVertex; i++) {
        if(graph->visited[i] == 0)
            topologicalSortUsingDFS(graph, i, s);
    }

    /* print stack */
    displayStack(s);
    
    return 0;
}