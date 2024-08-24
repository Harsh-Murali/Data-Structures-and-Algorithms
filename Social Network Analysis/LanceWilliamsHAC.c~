// Lance-Williams Algorithm for Hierarchical Agglomerative Clustering
// COMP2521 Assignment 2
// By z5361547
#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "LanceWilliamsHAC.h"

#define INFINITY DBL_MAX
#define ZERO 0

/**
 * Generates  a Dendrogram using the Lance-Williams algorithm (discussed
 * in the spec) for the given graph  g  and  the  specified  method  for
 * agglomerative  clustering. The method can be either SINGLE_LINKAGE or
 * COMPLETE_LINKAGE (you only need to implement these two methods).
 * 
 * The function returns a 'Dendrogram' structure.
 */
 

typedef struct coordinates {
    int x;
    int y;
} coordinates;

static bool incomplete(Dendrogram *array, int num_verticies);
static double LanceWilliams(double i_1, double j_1, int method);
static void dendrogramMerge (double **distances, Dendrogram *array, int num_verticies, int x, int y, int method);
static coordinates minSearch(double **distances, int num_verticies);

Dendrogram LanceWilliamsHAC(Graph g, int method) {

    // Makes a number of verticies
    int num_verticies = GraphNumVertices(g);
    double **distances = malloc(num_verticies * sizeof(*distances));

    // Arranges the distances in the 2d array to equal infinity.
    // Makes the distances from itself to the verticie equal to Zero.
    for (int i = ZERO; i < num_verticies; i++) {
        distances[i] = malloc(num_verticies * sizeof(double));
        for (int j = ZERO; j < num_verticies; j++) {
              
            if (i == j) {
            distances[i][j] = ZERO;
            } 
            
            else {
                distances[i][j] = INT_MAX;
            }
        }
    }

    // Assesses whether the verticies are adjacent to other verticies.
    // Updates their distance if they are adjacent.
    for (int vertex = ZERO; vertex < num_verticies; vertex++) {
            
        for (AdjList out = GraphOutIncident(g, vertex); out != NULL; out = out->next) {
                  
            if ((1.0 / out->weight) < distances[vertex][out->v]) {

                distances[vertex][out->v] = (1.0 / out->weight);
            }
        }

        for (AdjList in = GraphInIncident(g, vertex); in != NULL; in = in->next) {

            if ((1.0 / in->weight) < distances[vertex][in->v]) {

                distances[vertex][in->v] = (1.0 / in->weight);
            }
        }
    } 

    // Allocates memory to the array of dendrograms
    Dendrogram *array = malloc(num_verticies * sizeof(Dendrogram));

    // Initialises the dendrograms
    for (int i = ZERO; i < num_verticies; i++) {
        array[i] = malloc(sizeof(DNode));
        array[i]->vertex = i;
        array[i]->right = NULL;
        array[i]->left = NULL;
    }

    // Whilst the verticies are in different dedrograms then combine then
    while (incomplete(array, num_verticies)) {
        coordinates min = minSearch(distances, num_verticies);
        dendrogramMerge(distances, array, num_verticies, min.x, min.y, method);
    }

    // The last dendrogram will be indexed at position zero of the array
    Dendrogram ans = array[ZERO];
      
    // The array is freed
    for (int i = ZERO; i < num_verticies; i++) {
        free(distances[i]);
    }
      
    free(distances);
    free(array);

    return ans;
}


static double LanceWilliams(double i_1, double j_1, int method) {


    // Checks for the real distance by:
    // seeing if a distance is equal to infinity
    // if it is then it sets the distance as the other distance found
    if (i_1 == INT_MAX) {
        return j_1;
    } 
    else if (j_1 == INT_MAX) {
        return i_1;
    }

    double value = (i_1 - j_1);
    if (value < ZERO) {
        value = -value;
    }
    
    double variable = ZERO;
    if (method == 1) {
        variable = (-0.5);
    } 
    else if (method == 2) {
        variable = (0.5);
    }

    double answer = (((0.5) * i_1) + ((0.5) * j_1) + (variable * value));
    return answer;
}

// Examines whether all the vertices are within a single dendrogram
static bool incomplete(Dendrogram *array, int num_verticies) {

    // Returns true if dendrograms are in the array, otherwise returns false
    for (int i = 1; i < num_verticies; i++) {
        if (array[i] != NULL) {
            return true;
        }
    }

    return false;
}

// Calculates the smallest distance within the array.
static coordinates minSearch(double **distances, int num_verticies){
      
    coordinates answer;
    double curr_min = INT_MAX;

    for (int i = ZERO; i < num_verticies; i++) {
        for (int j = ZERO; j < num_verticies; j++) {
            if ((distances[i][j] <= curr_min) && (distances[i][j] > ZERO)) {
                curr_min = distances[i][j];
                answer.x = i;
                answer.y = j;
            }
        }
    }
    return answer;
}

// Mixes two dendrograms together
static void dendrogramMerge (double **distances, Dendrogram *array, int num_verticies, int x, int y, int method) {
      
    if (y < x) {
        int temp = x;
        x = y;
        y = temp;
    }

    // Revises and amends the distances for verticies which are adjacent to both x and y
    for (int i = ZERO; i < num_verticies; i++) {
        if ((i != x) && (i != y) && (array[i] != NULL)) {
                  
            distances[x][i] = LanceWilliams(distances[x][i], distances[y][i], method);
            distances[i][x] = LanceWilliams(distances[i][x], distances[i][y], method);
        }
            
        distances[y][i] = INT_MAX;
        distances[i][y] = INT_MAX;
    }

    // Produces another dendrogram with x and y included
    Dendrogram new = malloc(sizeof(DNode));
    new->right = array[x];
    new->left = array[y];
    array[x] = new;
    array[y] = NULL;
}




