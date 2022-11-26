#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//needed commands:
//start up: (simState)
    //create 2d array with 3 columns
    //init variable for size of the array
    //init variable for current state

//no command: (print current state)
    //print "current state" variable

//0 or 1: (next state)
    //use array to find the next state:
            //current state = array[current_state][0 or 1]
int getIndex(char arr[][3], int arrSize, char element);
void nextState(char arr[][3], int newState, char *currState, int *current_state);
            

//print: 
    //loop through 2d array
void print(char arr[][3], int arrSize);

//change: c [0 or 1] [state]
    //use array to change the values
        //array[current_state][0 or 1] = array[current_state][0 or 1]
void change(char arr[][3], int col, char newChar, int current_state);

//garbage:
    //loop through 2nd and 3rd columns in the array and search
        //for what is missing from the 1st and 2nd columns
int contains(char arr[][3], int arrSize, char val);
void garbage(char arr[][3], int arrSize, char *stateList[]);

//delete:
    //create new array from scratch and copy everything over
        //except for whatever is being deleted
void delete(char arr[][3], int *arrSize, char stateList, char deleteState);

int main(int argc, char * argv[])
{
	int getIndex(char arr[][3], int arrSize , char element){
		int i;
		for (i = 0; i < arrSize; i++){
			if (arr[i][0] == element){
				return i;
			}
		}
		return 20;
	}
	
    void nextState(char arr[][3], int newState, char *currState, int *current_state, int arrSize){
        *currState = arr[*current_state][newState+1];
        //printf("%d %d %d %d %d %d\n", 'A', 'B', 'C', 'D', 'E', 'F');
        //'A' == 65 in ASCII. current_state should equal the ASCII value - 65
        *current_state = getIndex(arr, arrSize, *currState);
        printf("Current State: %c, %d\n", *currState, *current_state);
    }
    
    void print(char arr[][3], int arrSize){
        int i, j;
        for(i=0; i<arrSize; i++) {
            for(j=0;j<3;j++) {
                printf("%c ", arr[i][j]);
            }
            printf("\n");
        }
        //printf("\n");
    }
    
    void change(char arr[][3], int col, char newChar, int current_state){
        //printf("mang: %d, %c, %d\n", col, newChar, current_state);
        //col-47 because ASCII value of 0 is 48, then +1 for array means col-48+1
        arr[current_state][col-47] = newChar;
    }
    
    int contains(char arr[][3], int arrSize, char val){
        int i, j;
        for(i=0; i<arrSize; i++) {
            for(j=1;j<3;j++) {
				//printf("contain check: %c\n", arr[i][j]);
                if (val != arr[i][0] && val == arr[i][j]){
					//printf("found it\n");
                    return 1;
                }
            }
        }
        return 0;
    }
    
    void garbage(char arr[][3], int arrSize, char stateList[]){
		strcpy(stateList, "");
		//int contains(char arr[][3], int arrSize, char val);
        int i; 
        int j = 0;
        //char missingList[arrSize];
        //int containsBool = 0;
        //array loop through 0th column of arr
        //create 2d temp array called stateList[][2]
            //0th column holds the state
            //1st column holds 0 or 1; default all 0's
        //loop through stateList[i][j] if j == 0, 
        
        //int x  = contains(arr, 1, 'A');
        for(i=0; i<arrSize; i++) {
			//printf("is %c reachable?\n", arr[i][0]);
			if (contains(arr, arrSize, arr[i][0]) == 0){
				stateList[j+1] = arr[i][0];
				//printf("%c added to unreachables\n", stateList[j]);
				j+=1;
			}  
        }
        stateList[0] = j+1;
        //printf("%d\n", j+1);
    }
    
    void delete(char arr[][3], int *arrSize, char stateList[], char deleteState){
		garbage(arr, *arrSize, stateList);
		int i;
		int j = 0;
		int k;
		int x;
		
		int containsBool = 0;
		
		//printf("deleteState = %c\n", deleteState);
		
		if (deleteState != '0'){
			for(i=1; i<stateList[0]; i++) {
				//containsBool = 0;
				if (stateList[i] == deleteState){
						containsBool += 1;
				}
				if (containsBool == 1){
					j = getIndex(arr, *arrSize, deleteState);
					//printf("j = %d\n", j);
					for (i = j; i < *arrSize; i++){
						for (k = 0; k < 3; k++){
							arr[i][k] = arr[i+1][k];
						}
					}
					printf("Deleted.\n");
					*arrSize -= 1;
				}
			}
			if(containsBool == 0){
				printf("Not deleted.\n");
			}/*else{
				printf("Deleted.2\n");
			}*/
		}
		
		//if (deleteState == 0 &&)
		if (stateList[0] == 1 && deleteState == '0'){
			printf("No states deleted\n");
		}else if(deleteState == '0'){
			for (x = 1; x < stateList[0]; x++){
				j = getIndex(arr, *arrSize, stateList[x]);
				for (i = j; i < *arrSize; i++){
					for (k = 0; k < 3; k++){
						arr[i][k] = arr[i+1][k];
					}
				}
				*arrSize -= 1;
			}
		}
		
	}
	
    int i;
    int arrSize = 8;
    char stateList[arrSize+1];
    char currState = 'G';
    int current_state = 6;
    char A = 'A'; 
    char B = 'B';
    char C = 'C';
    char D = 'D';
    char E = 'E';
    char F = 'F';
    char G = 'G';
    char H = 'H';
    
    char arr[8][3] = {
        {A, E, A},
        {B, C, F},
        {C, G, H},
        {D, B, G},
        {E, F, D},
        {F, H, D},
        {G, B, A},
        {H, A, C}
    };
    
    char cmd[6];
    printf("List of commands: 0, 1, p, c, g, d, s\n");
    int loop = 1;
    printf("Current State: %c\n", currState);
    //int x = contains(arr, 1, 'A');
    //printf("getIndex(G): %d\n", getIndex(arr, arrSize, G));
    while(loop == 1){
        //scanf("%5[^\n]", cmd);
        fgets(cmd, 6, stdin);
        //printf("%s \n", cmd);
        //printf("0: %c, 1: %c, 2: %c, 3: %c, 4: %c\n", cmd[0], cmd[1], cmd[2], cmd[3], cmd[4] );
        switch (cmd[0]){
            case '0': //next state [0]
                nextState(arr, 0, &currState, &current_state, arrSize);
                break;
            case '1': //next state[1]
                nextState(arr, 1, &currState, &current_state, arrSize);
                break;
            case 'p': //print 2d array
                print(arr, arrSize);
                break;
            case 'c': //change value (format: c [0 or 1] [char])
                change(arr, cmd[2], cmd[4], current_state);
                break;
            case 'g': //find garbage
                garbage(arr, arrSize, stateList);
                if (stateList[0] == 1){
					printf("No Garbage");
				}else{
					printf("Garbage: ");
					for(i=1; i<stateList[0]; i++) {
						printf("%c ", stateList[i]);
					}
				}
				printf("\n");
                break;
            case 'd': //delete
				//printf("argc: %d; cmd[1] = %c, cmd[2] = %c, cmd[3] = %c, cmd[4] = %c\n",
				 //argc, cmd[1], cmd[2], cmd[3], cmd[4]);
				if (cmd[1] == '\n'){
					delete(arr, &arrSize, stateList, '0');
					if (stateList[0] != 1){
						printf("Deleted: ");
						for(i=1; i<stateList[0]; i++) {
							printf("%c ", stateList[i]);
						}
					printf("\n");
				}
					//printf("bruh1\n");
                }else{
					delete(arr, &arrSize, stateList, cmd[2]);
					//printf("bruh2\n");
				}
                break;
            case 's': //stop
				loop = 0;
				printf("Program Terminated.\n");
				break;
            default:
                //printf("Current State1: %c\n", currState);
                break;
        }
    }
    exit(0);
}
