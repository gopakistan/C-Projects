/**
 *  The functions in this module implement a Stack data structure
 *  of integers.  (Note that chars are also integers so this
 *  integer Stack can be used for chars as well.)
 *
 *  NOTE: the stack is implemented as a fixed size array (size = 100).
 *  Consequently, no more than 100 integers can be pushed onto
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
//static int top = 0;
//static int stack[100];
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int top;
    int size;
    int* array;
};

struct Stack* stackInit(){
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->top = -1;
	stack->size = 100;
	stack->array = (int*)malloc(stack->size * sizeof(int));
	return stack;
}

/**
 * pop() removes the top integer on the stack and returns it.
 *
 * If pop() is attempted on an empty stack, an error message
 * is printed to stderr and the value -1 (minus one) is returned.
 */

int pop(struct Stack* stack)
{
	if (stack->top == -1) return -1;
	else{
		int toReturn = stack->array[stack->top];
		--stack->top;
		//printf("popped: %c, at top = %d\n", toReturn, stack->top);
		return toReturn;
		}
  //return 0;  //A dummy return statement
}

/**
 *  push(thing2push) adds the "thing2push" to the top of the stack.
 *
 *  If there is no more space available on the Stack, an error
 *  message is printed to stderr.
 */
void push(struct Stack* stack, int thing2push)
{
	if (stack->top < 100){ //this means its not full
		stack->array[stack->top + 1] = thing2push;
		stack->top++;
		//printf("%c pushed, new top = %d\n", stack->array[stack->top], stack->top);
	}else fprintf(stderr, "stack is full at 100 items.\n");
}

/**
 * isEmpty() returns a non-zero integer (not necessarily 1) if the
 * stack is empty; otherwise, it returns 0 (zero).
 *
 */
int isEmpty(struct Stack* stack)
{
	if (stack->top == -1) return 0;
	else return 1;
  //return 0;  //A dummy return statement
}
