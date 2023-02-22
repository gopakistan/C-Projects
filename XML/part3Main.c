#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
extern char *  pop();
extern void push(char *);
extern int isEmpty();
extern void readList();
extern void add();
extern int getHash();
extern int getLinkedIndex();
extern void readHash();
extern void initHash();

int compareStr(char* str1, char* str2){
	int i;
	for (i = 0; str1[i] != '\0' || str2[i] != '\0'; i++ ){
		if (!((str1[i+1] > 64 && str1[i+1] < 91) || (str1[i+1] > 96 && str1[i+1] < 123))) str1[i+1] = '\0';
		if (!((str2[i+1] > 64 && str2[i+1] < 91) || (str2[i+1] > 96 && str2[i+1] < 123))) str2[i+1] = '\0';
		if (str1[i] != str2[i]) return 0;
	}
	if (str1[i] != str2[i] &&(str1[i] == '\0' || str2[i] == '\0')) return 0; 
	else{
		return 1;
	}
}

int checkUnique(char array[200][50], char element[50]){
	int i;
	for (i = 0; array[i][0] != '\0'; i++){
		if (compareStr(array[i], element) == 1) return 1;
	}
	return 0;
}

int main(int argc, char * argv[])
{
	initHash();
	int endPrompt = 0;
	int read = 0;
	int i = 0; int j = 0; int rend = 0;
	int ch;
	char text[200][50];
	char pushList[100][50];
	while ((ch = getchar()) != EOF) {
		if (!(isalpha(ch) || ch == '>' || ch == '<' || ch == '/'))
		continue;
		if (ch == '<' && read == 0){ 
			read = 1; 
			i = 0;
			continue; 
		}
		else if (ch == '>' && read == 1){ 
			read = 0; 
			if (endPrompt == 0){
				push(text[j]);
				add(text[j]);
				if (checkUnique(pushList, text[j]) == 0) strcpy(pushList[rend++], text[j]);
			}else{
				if (compareStr(text[j], pop()) == 0){ 
					printf("NOT Valid\n");
					exit(1);
				}
			}
			j++;
			endPrompt = 0; 
			continue; 
		}
		else if (ch == '<' && read == 1){ // detecting "<<"
			printf("NOT Valid\n");
			exit(1);
		}
		else if (ch == '>' && read == 0){ // detecting ">>"
			printf("NOT Valid\n");
			exit(1);
		}
		
		if (read == 1 && ch == '/'){ endPrompt = 1; }
		if (read == 0 && ch == '/'){
			printf("NOT Valid\n");
			exit(1);
		}
		
		if (read == 1 && ch != '>' && ch != '<'){
			if (ch != '/') text[j][i++] = ch;
			if (ch == '/' && i != 0){
				printf("NOT Valid\n");
				exit(1);
			} 
		}	
    }
    if (isEmpty() == 1 && read != 1 && isalpha(text[0][0])){
		printf("Valid\n");
		int linkedIndex; int value;
		for (i = 0; i < rend; i++){
			value = getHash(pushList[i]);
			linkedIndex = getLinkedIndex(value, pushList[i]);
			printf("%s", pushList[i]);
			readHash(value, linkedIndex);
		}
	}
	else{
		printf("NOT Valid\n");
		exit(1);
	}
	
    exit(0);
}
