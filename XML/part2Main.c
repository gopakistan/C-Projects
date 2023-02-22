#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
struct Stack { int top; int size; int* array; };
extern struct Stack* stackInit();
extern int pop(struct Stack* stack);
extern void push(struct Stack* stack, int);

void updateArray(char uniqueList[][2], char element, int* uniqueSize){
	int i;
	for (i = 0; i < *uniqueSize; i++){
		if (uniqueList[i][0] == element){
			uniqueList[i][1]+=1;
			return;
		}
	}
	uniqueList[i-1][0] = element;
	uniqueList[i-1][1] = 1;
	*uniqueSize+=1;
}

int main(int argc, char * argv[])
{
	struct Stack* stack = stackInit();
	int ch;
	int endPrompt = 0;
	int read = 0;
	int uniqueSize = 1;
	char uniqueList[100][2];
	
	int i = 0;
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
				updateArray(uniqueList, ch, &uniqueSize);
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
			}
		}
	}
	if (stack->top != -1|| read == 1 || isalpha(ch)){
		printf("NOT Valid\n");
		exit(1); 
	} else {
		printf("Valid\n");
		for (i = 0; i < uniqueSize - 1; i++){
			printf("%c %d\n", uniqueList[i][0], uniqueList[i][1]);
		}
	exit(0);
	}
}
