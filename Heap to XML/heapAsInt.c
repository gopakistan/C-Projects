/**
 *  The functions in this module implement a Heapdata structure
 *  of integers.
 */
#include <stdio.h>
#include <math.h>
void switchIndex(int, int);
void compHeap(int);
void printXML(int);

static int nodeCount = 1; // default is 1
static int array[15];

/**
 * heapDelete() removes the biggest integer in the heap and returns it.
 *
 */
 int logOf2(int a){
	int i; int b = 0;
    for (i = a; i > 1; i/=2){
        b++;
    }
    return b;
 }

int heapDelete()
{
    int i;
    for (i = 0; i < nodeCount; i++){
        array[i] = array[i+1];
    }
    if (array[1] < array[2]) switchIndex(1, 2);
    int a = logOf2(nodeCount);
    for (i = a; i < nodeCount; i++){
        compHeap(i);
    }
    //printf("------%d------\n", --nodeCount);
    --nodeCount;
    return array[0];  //A dummy return statement
}

/**
 *  addHeap(thing2add) adds the "thing2add" to the Heap.
 *
 */
void addHeap(int thing2add)
{ 
	array[nodeCount] = thing2add;
	if (nodeCount != 1){
	    compHeap(nodeCount);
	}
	else{
	    array[nodeCount] = thing2add;
	}
	nodeCount++;
	
	// add it to at the end of the array
	// figure out where the parents are relative to that point
	// check which is bigger
		// if newly added is bigger, switch -> check again
		// if newly added is smaller, do nothing
	// nodeCount++
}

/**
 * heapSize() returns the number of items in the Heap.
 *
 */
int heapSize()
{
  return nodeCount;  //A dummy return statement
}


void switchIndex(int a, int b)
{
    //printf("\t\tswitching %d and %d\n", array[a], array[b]);
	int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

void compHeap(int nC){
    //a = nC = 2;
    //b = nC/2 = 1;
        // if b < a -> return;
        // if a < b 
            // -> switch spots
            // -> if (a != 1) -> comp() again
    
    int a = nC;
    int b = nC/2;
    //printf("\tcomp: %d and %d at %d\n", array[a], array[b], nC);
    if (array[b] > array[a]){
        return;
    }
    else{
        switchIndex(a, b);
        if (nC > 3){
            compHeap(nC/2);
        }
        else{ return; }
    }
}

void printHeap(){
	int i; int j = 0;
	for (i = 1; i < nodeCount; i++){
	    j += j + 1;
		printf("%d %d\n", i, array[i]);
	}
	printf("\n");
}

void printXML(int a){
    printf("<node id=\"%d\">", array[a]);
    if (a*2 <= nodeCount) printXML(a*2);
    if (a*2 + 1 < nodeCount) printXML(a*2+1);
    printf("</node>");
}
