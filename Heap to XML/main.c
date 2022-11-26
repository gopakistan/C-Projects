#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
extern int pop();
extern void push(int);
extern void addHeap(int);
extern void printHeap();
extern void printXML(int);
extern int heapSize();
extern int heapDelete();
extern int isEmpty();

int main(int argc, char * argv[])
{
    //TEST SEQUENCE: 35 33 42 10 14 19 27 44 26 31
	int value;
	while (scanf("%d\n", &value) != EOF) {
		//fprintf(stdout, "READING INPUT: %d\n", value);
		//
		//push(value);
		addHeap(value);
		//printHeap();
		
    }
    //printHeap();
    printf("\n");
    printXML(1); printf("\n\n");
    int i;
    int temp;
    for (i = 0; heapSize() > 1; i++){
        temp = heapDelete();
        printf("%d \n", temp);
        push(temp);
    }
    printf("\n");
    while (isEmpty() == 0) printf("%d\n", pop());
    //printf("\n%d", heapSize());
    exit(0);
}
