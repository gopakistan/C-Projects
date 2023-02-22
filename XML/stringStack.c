/**
 *  The functions in this module implement a Stack data structure
 *  of char pointers (aka "strings").
 *  
 *  NOTE: the stack is implemented as a fixed size array (size = 100).
 *  Consequently, no more than 100 strings can be pushed onto
 *  the Stack at any given time.
 */

// Implementation hints:
//   The 3 functions--push, pop and isEmpty--share information
//   about the array used to implement the stack and the index
//   of the "top" of the stack.
//
//   You may want to make these variables global...
//   ...but that would
//   be a mistake (because anyone using the module would have
//   to ensure that they did not use global variables with the
//   same names).
//
//   An alternative in C is a "static global".
//   If a global variable is qualified as "static", it is global only
//   within the source code file where it is declared.
//   In parituclar, it cannot conflict with any other global variable.
//
//  RECOMMENDATION:
//   Uncomment the following 2 lines and use these static globals!
#include <stdio.h>
#include <string.h>
static int top = -1;
static char * stack[100];
int isEmpty();

/**
 * pop() removes the top string on the stack and returns it.
 *
 * If pop() is attempted on an empty stack, an error message
 * is printed to stderr and the value NULL ((char *) 0) is returned.
 */

char *  pop()
{
	if (isEmpty() == 1){ 
		return (char*)-1;
	}
	else{
		/*char* toReturn = stack[top];
		top -= 1; 
		printf("%s has been popped\n", toReturn);
		return toReturn;*/
		//printf("%s has been popped\n", stack[top]);
		return stack[top--];
	}
	//return (char *) 0;  //A dummy return statement
}

/**
 *  push(thing2push) adds the "thing2push" to the top of the stack.
 *
 *  If there is no more space available on the Stack, an error
 *  message is printed to stderr.
 */
void push(char * thing2push)
{
	//printf("man2.\n");
	top += 1;
	//printf("man3. %d\n", top);
	stack[top] = thing2push;
	//printf("man3. %d\n", top);
	//printf("%s has been pushed\n", thing2push);
	
}

/**
 * isEmpty() returns a non-zero integer (not necessarily 1) if the
 * stack is empty; otherwise, it returns 0 (zero).
 *
 */
int isEmpty()
{
	if (top == -1){ 
		return 1; 
	}  //A dummy return statement
	else return 0;
}

/*
void readList()
{
	int leng = top; int i;
	if (leng == -1) return;
	printf("RL: "); 
	for (i = leng; i > -1; i--){
		printf("%s ", stack[i]);
	}
	printf("\n");
}

char strTrans(char str2[30])
{
	char str1[30] = "";
	int i; strcpy(str1, "");
	for (i = 0; str2[i] != '\0'; i++){
		str1[i] = str2[i];
	}
	return str1;
}*/
