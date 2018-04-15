/* Find the largest path in Directed Acyclic Graph (DAG) using DFS algo */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define STACK_SIZE 20
#define INF INT_MIN

/* Graph Structures */
struct node {
    int vertex;
    int weight;
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
        s->item[++(s->top)] = value;
    }
}

int pop(struct Stack* s)
{

    if(isEmpty(s)) {
        printf("\nStack is empty\n");
    }
    else {
        return (s->item[s->top--]);
    }
}

struct node *CreateNode(int value, int w);
struct Graph *CreateGraph(int numOfVertex);
void addEdge(struct Graph *graph, int src, int dest, int weight);
void printGraph(struct Graph *graph);
int topologicalSortUsingDFS(struct Graph* graph, int v, struct Stack *s);

struct node *CreateNode(int value, int w)
{
    /* Create a new node */
    struct node *newNode = (struct node*) malloc (sizeof(struct node));
    newNode->vertex = value;
    newNode->weight = w;
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
void addEdge(struct Graph *graph, int src, int dest, int w) {

    // Add edge from src to dest
    struct node *newNode = CreateNode(dest, w);
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


/* Print stack value for topological sort */
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
        printf ("\nTopological Sort for a given graph \n");
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

    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 3, 6);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 2, 4, 4);
    addEdge(graph, 2, 5, 2);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 3, 5, 1);
    addEdge(graph, 3, 4, -1);
    addEdge(graph, 4, 5, -2);
    
    printGraph(graph);
    printf("\n");
    
    struct Stack *s = CreateStack();
    
    int i;
    for(i = 0; i < graph->numVertex; i++) {
        if(graph->visited[i] == 0)
            topologicalSortUsingDFS(graph, i, s);
    }
    
    
    // Starting vertex is 1
    int startVertex = 1;
    // Create an array for weighted graph
    int dist[graph->numVertex];
    // Set weight as -(Infinity) for each vertex 
    int j;
    for(j = 0; j<graph->numVertex; j++) {
        dist[j] = INF;
    }
    // Set starting point weight as 0 on vertex
    dist[startVertex] = 0;
    
    displayStack(s);
    
    printf("\n");

    while(!isEmpty(s)) {
        int u = s->item[s->top];
        pop(s);
    	
        if(dist[u] != INF) {
            struct node *head = graph->adjList[u];
            struct node *temp = head;
            
            while(temp) {
                if(dist[temp->vertex] < dist[u] + temp->weight ) {
                    dist[temp->vertex] = dist[u] + temp->weight;
                    printf("dist[%d]: %d\n", temp->vertex, dist[u] + temp->weight);
                }
                temp = temp->next;
            }
        }        
    }
    printf("\n");

    // Print the calculated longest distances from starting node value 1
    int k;
    for (k = 0; k < graph->numVertex; k++) {
        if(dist[k] == INF) {
            printf("%s ", "INF");
        } 
        else {
            printf("%d ", dist[k]);
        }
    }
    
    return 0;
}