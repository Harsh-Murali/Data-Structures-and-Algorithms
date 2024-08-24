// Centrality Measures API implementation
// COMP2521 Assignment 2
// By z5361547

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "Graph.h"

#define ZERO 0

static double ShortestPathAmount(NodeData *shortestPaths, Vertex dest, Vertex src);
static double betweennessCentralityFinder(double i, double j, double k);

double *closenessCentrality(Graph g) {

    // Makes a number of nodes
    int Node_num = GraphNumVertices(g);
    double *quantity = malloc(Node_num* sizeof(double));

    // Finds nodes to visit and the total distance through looping through vertexes
    for (int src = ZERO; src < Node_num; src++) {

        NodeData *shortestPaths = dijkstra(g, src);
        double n = ZERO, Num = Node_num, distSum = ZERO;
        for (int i = ZERO; i < Node_num; i++) {

            if (shortestPaths[i].dist == INFINITY) {
                distSum += ZERO;
                continue;
            }

            // Creates the required number of visitable nodes along with the source
            if (shortestPaths[i].dist != ZERO || i == src) {
                n++;
            }

            // Constructs the sum of shortest distances of all nodes from the source
            if (shortestPaths[i].dist == INFINITY) {
                distSum += ZERO;
                continue;
            }
            distSum += shortestPaths[i].dist;
        }

        if (distSum == ZERO) {
            quantity[src] = ZERO;
        }
        
        else { 
            quantity[src] = ((n-1)/(Num-1)) * ((n-1)/(distSum));
        }
    }
    return quantity;
}

double *betweennessCentrality(Graph g) {

    // Creates Node_num and then initialises and allocates memory
    int Node_num = GraphNumVertices(g);
    double *quantity = malloc(Node_num * sizeof(double));

    // Loops the array made for quantity   
    for (int node = ZERO; node < Node_num; node++) {
        quantity[node] = ZERO;

        // The source loops through all the vertexes
        for (int src = ZERO; src < Node_num; src++) {
            NodeData *shortestPaths = dijkstra(g, src);

            // Searches for possible destinations for that source
            for (int dest = ZERO; dest < Node_num; dest++) {

                // Executes the betweenness Centrality formula if paths exist
                // from the source to the destination
                if (ShortestPathAmount(shortestPaths, dest, src) != ZERO) {
                    quantity[node] += betweennessCentralityFinder(ShortestPathAmount(shortestPaths, node, src),
                    ShortestPathAmount(shortestPaths, dest, node),
                    ShortestPathAmount(shortestPaths, dest, src));	                

                }

            }

        }

    }

    return quantity;
}

// Performs the betweennessCentrality formula. 
static double betweennessCentralityFinder(double i, double j, double k) {

    return (i * j)/ k;

}

static double ShortestPathAmount(NodeData *shortestPaths, Vertex dest, Vertex src) {

    double count = ZERO;

    // This is a counter for when source is discovered from the destination
    for (PredNode *current = shortestPaths[dest].pred; current != NULL; current = current->next) {

        if (src == current->v) {

            count = count + 1;
        }

        count = count + ShortestPathAmount(shortestPaths, current->v, src);

    }

    return count;

}


