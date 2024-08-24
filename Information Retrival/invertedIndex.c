// COMP2521 Assignment 1
//By Harsh Murali
//z5361547
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "invertedIndex.h"

#define SIZE 50
#define ZERO 0

char *normaliseword(char *word);
InvertedIndexBST BSTNodeNew(char *word);
FileList FileListNodeNew(char* filename, double tf);
void fileListNodeInsert(InvertedIndexBST node, char *filename, double tf);
InvertedIndexBST InsertBST(InvertedIndexBST node, char *word);
InvertedIndexBST FileListsAdding(InvertedIndexBST node, int totalFiles, char filename [SIZE][SIZE]); 
InvertedIndexBST FileListInsert(InvertedIndexBST node, int totalFiles, char filename[SIZE][SIZE]);
InvertedIndexBST generateInvertedIndex(char *collectionFilename);
InvertedIndexBST BSTFinder(InvertedIndexBST t, char *word);
TfIdfList TfIdfListNodeNew(char* filename, double tfIdfSum);
TfIdfList TfIdfListInsert(TfIdfList list, char* filename, double tfIdfSum);
TfIdfList MatchingNameSearch(TfIdfList list, char* filename);

// Traverses the tree to find word node
InvertedIndexBST BSTFinder(InvertedIndexBST t, char *word) {

	if (t == NULL) // Couldn't find the required word
	    return NULL;
	else if (strcmp(t->word, word) > ZERO)
		return BSTFinder(t->left, word);
	else if (strcmp(t->word, word) < ZERO)
		return BSTFinder(t->right, word);
	else {
		return t;
	}
}

TfIdfList TfIdfListInsert(TfIdfList list, char* filename, double tfIdfSum) {

    TfIdfList New_node = TfIdfListNodeNew(filename, tfIdfSum);
    TfIdfList matching = MatchingNameSearch(list, filename); 
    
    if (matching != NULL) {
        
        matching->tfIdfSum += tfIdfSum;
        
        free(New_node);
    
    }

    // If the list is empty,New_node becomes the head
    else if (list == NULL) {
        list = New_node;
 
    }    
    
    else if (tfIdfSum >= list->tfIdfSum) {
    
        // Case 1:If the position is full but after the head, then insert the node
        if (New_node->tfIdfSum == list->tfIdfSum 
            && strcmp(New_node->filename, list->filename) < ZERO) {
            New_node->next = list->next;
            list->next = New_node;        
        }
        else {
            New_node->next = list;
            list = New_node;
        }
    }
    
    // Case 2: If the position is in the middle
    else {
    
        TfIdfList current = list;
        
        // Loop through the list until the new value is greater than or equal to the current value
        while (current->next != NULL && current->next->tfIdfSum > tfIdfSum) {
        
            current = current->next;
        
        }
           
        // Case 3: If there are two equal values
        if (current->next != NULL && current->next->tfIdfSum == tfIdfSum) {
            
            // Loop until the new filename is larger than the current filename.
            while (current->next->tfIdfSum == tfIdfSum &&
                   strcmp(current->next->filename, filename) < ZERO) {                
                current = current->next;    
                      
            }       
        }
        
        // Insert node at current position
        New_node->next = current->next;
        current->next = New_node;
    }
    
    // Returning a pointer to the list
    return list;
}


// Makes another TfIdfListNode with values and allocates it memory
TfIdfList TfIdfListNodeNew(char* filename, double tfIdfSum) {

    TfIdfList new = malloc(sizeof(*new));
	
	new->filename = filename;
	new->tfIdfSum = tfIdfSum;
	new->next = NULL;
	
	return new;

}


// Finds a node inside TfIdfList with the filename and returns a pointer
TfIdfList MatchingNameSearch(TfIdfList list, char* filename) {

    TfIdfList current = list;
    
    // Loops till the required node is found or till the end
    while (current != NULL && strcmp(current->filename, filename) != 0) {
    
        current = current->next;
    }
    
    if (current == NULL) 
        return NULL;
        
    else 
        return current;

}


// Part 1

// Function to remove punctuation and remove capital letters
char *normaliseword(char *word) {
    int current = ZERO;
    while (word[current] != '\0') {
        if (toupper(word[current]) != 0){
            word[current] = tolower(word[current]);
            current++;
        }
    }
    
    int length = strlen(word);
    while(word[length] < 'a' || word[length] > 'z') {
        if (word[length] == '.' || word[length] == ',' || word[length] == ':' || word[length] == ';' || word[length] == '?' || word[length] == '*') {
            if (word[length + 1] == '\0') {
                word[length] = '\0';
            }
        }
        length --;
    }
    return word;
}



// Creates a new BST Node and allocates it memory
InvertedIndexBST BSTNodeNew(char *word) {

    InvertedIndexBST new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}
	
	new->word = word;
	new->right = NULL;
	new->left = NULL;
	new->fileList = NULL;
	return new;

}

// A new node is inserted into the BST and the root of the new BST is returned

InvertedIndexBST InsertBST(InvertedIndexBST node, char *word)
{
	if (node == NULL) // Empty Tree
		return BSTNodeNew(word);
	
	else if (strcmp(word, node->word) > ZERO)
		node->right = InsertBST(node->right, word);
	else if (strcmp(word, node->word) < ZERO)
		node->left = InsertBST(node->left, word);
	return node;
}


// Creates a new FileListNode and allocates memory to store details. Also returns a pointer

FileList FileListNodeNew(char* filename, double tf) {

    FileList new = malloc(sizeof(*new));
  
    new->tf = tf;
	new->filename = filename;
	new->next = NULL;
	
	return new;

}

void fileListNodeInsert(InvertedIndexBST node, char *filename, double tf) {

    FileList New_node = FileListNodeNew(filename,tf);
    
    // Case 1: If fileList is empty, New_node becomes head
    if (node->fileList == NULL) {
        node->fileList = New_node;
        
    }
    
    // Case 2: If position is before head
    
    else if (strcmp(node->fileList->filename, filename) > ZERO) {
    
        New_node->next = node->fileList;
        node->fileList = New_node;
    
    }
    
    // Case 3: If position is in the middle
    else {
    
        FileList current = node->fileList;
        
        // Loops through the list and finds position then inserts node accordingly
        while (current->next != NULL && strcmp(current->next->filename, filename) < 0) {
            current = current->next;  
        }
        New_node->next = current->next;
        current->next = New_node;
    }
}

// Inserts fileLists at a certain tree node
InvertedIndexBST FileListInsert(InvertedIndexBST node, int totalFiles, 
char filename[SIZE][SIZE]) {
	
	// Creates a loop for the files
	int i = ZERO;
	while (i < totalFiles) {
	    
	    char temp[SIZE];
	    double word_total = ZERO, count = ZERO;
	    FILE* textfile = fopen(filename[i], "r");
	    
	    // Checks all the words inside the textfile
	    while (fscanf(textfile, "%s", temp) == 1) {
	    
	        word_total++;
	        
	        // Stores if a match is found
	        if (strcmp(node->word, normaliseword(temp)) == ZERO) {
	            count++;
            }
            memset(temp, '\0', sizeof temp);
	    }
	    
	    if (count != ZERO) {
	        fileListNodeInsert(node, filename[i], count/word_total);
	    }
	    
	    // Closes the textfile
	    fclose(textfile);
	    i++;
	
	}
	// Returns a pointer to the changed tree node
	return node; 

}


// Adds filelists at all the word nodes
InvertedIndexBST FileListsAdding(InvertedIndexBST node, int totalFiles, char filename [SIZE][SIZE]) {

    if (node != NULL) {
    
        node = FileListInsert(node, totalFiles, filename);
        FileListsAdding(node->right,totalFiles, filename);
        FileListsAdding(node->left,totalFiles, filename);

    }
    
    return node;
}

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
    
// Opens the textfile
    FILE* collection = fopen(collectionFilename, "r");
    
    char filename[1000][SIZE];
    int i = ZERO;
    
    // Stores every filename into an array of strings
    while (fscanf(collection, "%s", filename[i]) == 1) {
        i++;
    }
    
    fclose(collection);
    
    int totalFiles = i, j = ZERO; 
    char words[10000][SIZE];
    
    // Generates an empty BST
    InvertedIndexBST BSTNew(void) {
	return NULL;
}
    InvertedIndexBST treeNew = BSTNew();
    
    i = ZERO;
    while (i < totalFiles) {
    
        FILE* textfile = fopen(filename[i], "r");
        
        // Inserts every word into an array
        while (fscanf(textfile, "%s", words[j]) == 1) {

            treeNew = InsertBST(treeNew, normaliseword(words[j])); 
            j++;   
           
        }
       i++; 
}

    treeNew = FileListsAdding(treeNew, totalFiles, filename);

    // Returns the new tree
    return treeNew;
}


// Prints out the results into a file
void inOrderTraversePrint(InvertedIndexBST tree, FILE *outputText) {

    if (tree == NULL) {
    return;
    }

    inOrderTraversePrint(tree->left, outputText);
    fprintf(outputText, "%s ", tree->word);
    
    FileList list = tree->fileList;
    while (list != NULL) {
        fprintf(outputText, "%s (%0.7lf) ", list->filename, list->tf);
        list = list->next;
    }
    
    fprintf(outputText, "\n");
    inOrderTraversePrint(tree->right, outputText);
    
}


void printInvertedIndex(InvertedIndexBST tree, char *filename) {
    
FILE* outputText = fopen(filename, "w");
    
    inOrderTraversePrint(tree, outputText);
    fclose(outputText);
}

void freeInvertedIndex(InvertedIndexBST tree) {

}

// Part 2

TfIdfList searchOne(InvertedIndexBST tree, char *searchWord, int D) {

    // Detects the node
    InvertedIndexBST node = BSTFinder(tree, searchWord);
    
    // If the node is null, then return an empty list
    if (node == NULL) {
        return NULL;
    
    }
    
    FileList current = node->fileList;
    
    double Document_amount = ZERO;

    // Loops through the node, whilst tracking Document_amount 
    while (current != NULL) {

        Document_amount++;
        current = current->next;

    }
   
    double idf = log10(D/Document_amount);
    
    // Resets the pointer and makes a new list
    current = node->fileList;
    TfIdfList list;   
    
    // Inserts required node into the new tfIdfList
    while (current != NULL) {
        
        list = TfIdfListInsert(list, current->filename, idf * current->tf);  
        
        current = current->next;
    }
    
    return list;

}

TfIdfList searchMany(InvertedIndexBST tree, char *searchWords[], int D) {
    return NULL;
}



void freeTfIdfList(TfIdfList list) {

}

