// Dijkstra API implementation
// COMP2521 Assignment 2
// By z5361547

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dijkstra.h"
#include "Graph.h"
#include "PQ.h"

#define ZERO 0

static PredNode *insertPredNode(PredNode *list, Vertex v);
static void freeList(PredNode *list);

NodeData *dijkstra(Graph g, Vertex src) {

    // Makes a number of nodes
    int Node_num = GraphNumVertices(g);

    NodeData *smallestPath = malloc(sizeof(NodeData)*Node_num);
    PQ q = PQNew();

    // Places the source vertex in the struct
    smallestPath[src].dist = ZERO;

    // Initialises distance, boolean and pred list arrays then
    // sets each vertex into a priority queue.
    for (int i = ZERO; i < Node_num; i++) {	    

        if (src != i) {
            smallestPath[i].dist = INT_MAX; 
        }    

        smallestPath[i].pred = NULL;
        PQInsert(q, i, smallestPath[i].dist);

    }
    
    // Loops through vertexes present within the graph.
    while (!PQIsEmpty(q)) {

        Vertex v = PQDequeue(q);

        // Generates a list containing the edges going out from Vertex v.
        AdjList OutList = GraphOutIncident(g, v);

        for (AdjList current = OutList; current != NULL; current = current->next) {

            int newDist;
            
            if (smallestPath[v].dist == INFINITY) {
            
                newDist = INFINITY;
            } 
            
            else {

                newDist = smallestPath[v].dist + current->weight;

                if (newDist <= smallestPath[current->v].dist) {

                    // Amends and removes pred vertexes only if, the 
                    // distance of the newpath is found to be shorter
                    if (smallestPath[current->v].dist > newDist) {

                        freeList(smallestPath[current->v].pred);
                        smallestPath[current->v].dist = newDist;
                        smallestPath[current->v].pred = NULL;         
                    }

                    // Updates the queue and also inserts the previous vertex.
                    smallestPath[current->v].pred = insertPredNode(smallestPath[current->v].pred, v);
                    PQUpdate(q, current->v, newDist);
                }

            }

        }

        // Sets the distance to zero given that the distance from the source is found to be infinity.
        if (smallestPath[v].dist == INT_MAX) smallestPath[v].dist = INFINITY;

    }

    PQFree(q);
    return smallestPath;
}

// Frees the Node data
void freeNodeData(NodeData *data, int nV) {

    for (int i = ZERO; i<nV; i++) {
        freeList(data[i].pred);
    }
    
    free(data);
}


// Produces and inserts a new PredNode
// 
static PredNode *insertPredNode(PredNode *list, Vertex v) {

    PredNode *current = list;

    // Allocates memory and initialises a new node
    PredNode *new = malloc(sizeof(PredNode));
    new->v = v;
    new->next = NULL;

    // Checks whether the list is empty, and if so inserts new at the head
    if (list == NULL) {
    
        list = new;
    }

    else if (current->next == NULL && current->v > new->v){

        new->next=current;
        list = new;


    }

    //Travels to the end and then inserts a new node
    else {
        while (current->next != NULL && current->next->v < new->v) {
            current = current->next;

        }
        new->next = current->next;
        current->next = new;
        
    } 
    
    return list;
}

// Completely frees memory related to a certain PredNode list
static void freeList(PredNode *list) {

    PredNode *current = list;
    PredNode *previous = NULL;

    while (current != NULL) {

        previous = current;
        current = current->next;
        free(previous);
    }
    
}
