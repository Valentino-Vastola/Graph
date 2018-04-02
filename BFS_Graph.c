/* BFS for graph */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define QUEUE_SIZE 20

/* Queue structure */
struct Queue {
    int items[QUEUE_SIZE];
    int front;
    int rear;
};

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

/* Queue operation */
/* Create a Queue */
struct Queue *CreateQueue();
/* Insert element into created queue */
void enQueue(struct Queue* q, int value);
/* Remove the element from queue */
int deQueue(struct Queue* q);
/* Check queue is empty */
int isEmpty(struct Queue* q);
/* Print the queue element */
void printQueue(struct Queue* q);

/* Graph Operations */
/* Create a vertex node */
struct node *CreateNode(int value);
/* Create a graph */
struct Graph *CreateGraph(int numOfVertex);
void addEdge(struct Graph *graph, int src, int dest);
void printGraph(struct Graph *graph);
/* Breadth First Search function */
void BFS(struct Graph* graph, int startVertex);

struct  Queue* CreateQueue() {
    struct Queue* q = (struct Queue*) malloc (sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct Queue* q) {
    if(q->rear == -1) {
        return 1;
    }
    else {	
        return 0;
    }
}

void enQueue(struct Queue* q, int value)
{
    if(q->rear == QUEUE_SIZE-1) {
        printf("\nQueue is full\n");
	}
    else {
        if(q->front == -1)
        {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }    
}

int deQueue(struct Queue* q)
{
    int itemValue;
    if(isEmpty(q))
    {
        printf("\nQueue is empty\n");
        itemValue = -1;
    }
    else
    {
        itemValue = q->items[q->front];
        q->front++;
        if(q->front > q->rear) {
            printf("\nReset the queue\n");
            q->front = q->rear = -1;
        }        
    }
    return itemValue;
}

void printQueue(struct Queue *q) {
    int i = q->front;

    if(isEmpty(q)) {
        printf("Queue is empty");
    } 
    else 
    {
        printf("\nQueue elements \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]);
        }
    }    
}

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

void BFS(struct Graph* graph, int startVertex)
{
    /* Create a Queue */
    struct Queue* queue = CreateQueue();
    /* Set startVertex in visited list as true */
    graph->visited[startVertex] = 1;
    /* Insert visited vertex in queue */
    enQueue(queue, startVertex);	
	
    while(!isEmpty(queue))
    {
        printQueue(queue);
        /* Remove front element from the queue */
        int dequeueVertex = deQueue(queue);
        printf("\nVisited vertex: %d\n", dequeueVertex);
        
        /* Get the address of adjacency list to traverse the vertex of graph */
        struct node* head = graph->adjList[dequeueVertex];

        while(head) 
        {
            /* Get value of vertex node */
            int adjVertexValue = head->vertex;
            /* Check the vertex is not visited */
            if(graph->visited[adjVertexValue] == 0) {
                /* If vertex not visited then set as visited */
                graph->visited[adjVertexValue] = 1;
                /* Insert visited vertices in queue */
                enQueue(queue, adjVertexValue);
			}
            /* Traverse the next vertex in adjacency node */
            head = head->next;
        }
    }
}

int main(int argc, char **argv)
{
    struct Graph *graph = CreateGraph(4);

    addEdge(graph, 0, 1);    //0->1
    addEdge(graph, 0, 2);    //0->2
    addEdge(graph, 0, 3);    //0->3
    addEdge(graph, 1, 2);    //1->2
    addEdge(graph, 2, 3);    //2->3
    
    printGraph(graph);
    printf("\n");
    
    BFS(graph, 0);	
    return 0;
}
