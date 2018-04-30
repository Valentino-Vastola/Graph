/* Check whether a given graph is Bipartite or not */

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
    int *level;				// Set the level for coloring
    struct node **adjList;
};

/* Queue operation */
struct Queue *CreateQueue();					/* Create a Queue */
void enQueue(struct Queue* q, int value);		/* Insert element into created queue */
int deQueue(struct Queue* q);					/* Remove the element from queue */
int isEmpty(struct Queue* q);					/* Check queue is empty */
void printQueue(struct Queue* q);				/* Print the queue element */

/* Graph Operations */
struct node *CreateNode(int value);				/* Create a vertex node */
struct Graph *CreateGraph(int numOfVertex);		/* Create a graph */
void addEdge(struct Graph *graph, int src, int dest);
void printGraph(struct Graph *graph);			/* Print the Graph */
int BfsBipartite(struct Graph* graph, int v);	/* Breadth First Search function */

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
        printf("\nQueue elements: ");
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
    graph->level = (int*) malloc (numOfVertex * sizeof(int));
	
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

int BfsBipartite(struct Graph* graph, int v)
{    
    graph->visited[v] = 1;			/* Set v in visited list as true */
    graph->level[v] = 0;				/* Set level as 0 */
    
    struct Queue* queue = CreateQueue();		/* Create a Queue */    
    enQueue(queue, v);				/* Insert visited vertex in queue */
	
    while(!isEmpty(queue))
    {
        //printQueue(queue);        
        int dequeueVertex = deQueue(queue);					/* Remove front element from the queue */
        printf("\nVisited vertex: %d", dequeueVertex);		/* Print visited node after dequeue */
        struct node* head = graph->adjList[dequeueVertex];	/* Get the address of adjacency list to traverse the vertex of graph */

        while(head) 
        {            
            int u = head->vertex;			/* Get value of vertex node */            
            if(graph->visited[u] == 0) 		/* Check the vertex is not visited */
			{
                graph->visited[u] = 1;		/* If vertex not visited then set as visited */
                graph->level[u] = graph->level[v] + 1;
                enQueue(queue, u);			/* Insert visited vertices in queue */
			}
			else
			{
				if(graph->level[v] == graph->level[u])
				{
					return 0;
				}
			}
            /* Traverse the next vertex in adjacency node */
            head = head->next;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    struct Graph *graph = CreateGraph(5);

    addEdge(graph, 0, 1);    //0->1
    addEdge(graph, 0, 2);    //0->2
    addEdge(graph, 1, 3);    //1->3
    addEdge(graph, 2, 4);    //2->4
    addEdge(graph, 3, 4);    //3->4

    /* Print DAG */    
    printGraph(graph);
    printf("\n");
    
    /* Check graph is Bipartite */
    if(BfsBipartite(graph, 0)) {
        printf("\n\nBipartite Graph");
    }
    else
    {
        printf("\n\nNot a Bipartite Graph");
    }
    return 0;
}
