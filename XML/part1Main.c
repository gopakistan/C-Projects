#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
struct Stack { int top; int size; int* array; };
extern struct Stack* stackInit();
extern int pop(struct Stack* stack);
extern void push(struct Stack* stack, int);

int main(int argc, char * argv[])
{
	struct Stack* stack = stackInit();
	int ch;
	int endPrompt = 0;
	int read = 0;
	
	while ((ch = getchar()) != EOF) {
		if (!(isalpha(ch) || ch == '>' || ch == '<' || ch == '/'))
		continue;
		//printf("%c ; r:%d ; eP:%d\n", ch, read, endPrompt);
		if (ch == '<'){ // means previous was a > -> read == 0
			if (read == 1){ //detecting <<
				printf("NOT Valid\n");
				exit(1);
			}
			else{ // good
				read = 1;
			}
			continue;
		}

		if (ch == '>'){ // means previous was a letter -> read == 1
			if (read == 0){ //detecting >>
				printf("NOT Valid\n");
				exit(1);
			}
			else{ // good
				read = 0;
			}
			continue;
		}
			
		if (read == 1 && endPrompt == 0){ // means previous was a < or a /
			if (ch == '/'){ //detecting < 
				endPrompt = 1;
			}
			else if (isalpha(ch)){ // detecting letter
				push(stack, ch);
			}
			else{
				printf("NOT Valid\n");
				exit(1);
			}
			continue;
		}
		if (read == 0 && ch != '<'){ //means previous was a >
			printf("NOT Valid\n");
			exit(1);
		}
		if (endPrompt == 1){
			if (isalpha(ch)){
				if (ch != pop(stack)){
					printf("NOT Valid\n");
					exit(1);
				}
			endPrompt = 0;
			//read = 0;
			}
		}
	}
	if (stack->top != -1 || read == 1 || isalpha(ch)){ 
		printf("NOT Valid\n");
		exit(1);
	}
	else printf("Valid\n");
	exit(0);
}
