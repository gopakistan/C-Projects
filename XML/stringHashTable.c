#include <string.h>
#include <stdio.h>
extern int compareStr(char*, char*);
#define HASH_TABLE_SIZE 1057
typedef struct Entry Entry, *EntryPtr;
struct hash_list{
	char string[100];
	int frequency; //0
};

struct Entry {
  //char * string;
  int latest; //-1
  //int count; //0
  struct hash_list linkedList[50];
};
Entry hash_table[HASH_TABLE_SIZE];

void initHash(){
	int i;
	for (i = 0; i< HASH_TABLE_SIZE; i++){
		hash_table[i].latest = 0;
	}
}

int getHash(char *stringConv){ //given a 
	int value = 0; int i;
	for (i = 0; i < strlen(stringConv); i++){
		value = value * 100;
		value += stringConv[i] - 64;
		if (2147483647 / 100 < value) break;
	}
	value = value % HASH_TABLE_SIZE;
	return value;
	
	return 0;
	
}

int getLinkedIndex(int value, char* tag){
	
	int linkedIndex;
	for (linkedIndex = 0; linkedIndex < hash_table[value].latest; linkedIndex++){
			if (compareStr(hash_table[value].linkedList[linkedIndex].string, tag)){
				//printf("\tduplicate found: %d\n", linkedIndex);
				break;
			}
		}
	//printf("linkedIndex: %d\n", linkedIndex);
		//for loop above:
			//if value exists already: make linkedList = that index
				//start at 0, go to 1; loop end
			//if value not exist already: make linkedList = latest
				//start at 0, (assume latest is 1); 0 goes up to 2.
	return linkedIndex;
}

void add(char * tag)
{
	int value = 0;
	int linkedIndex = 0;
	
	value = getHash(tag);
	
	linkedIndex = getLinkedIndex(value, tag);
	if (linkedIndex == hash_table[value].latest){ //DUPLICATE NOT FOUND
		strcpy(hash_table[value].linkedList[linkedIndex].string, tag);
		hash_table[value].latest += 1;
	}
	hash_table[value].linkedList[linkedIndex].frequency += 1;
		//duplicate found:
			//frequency++
			//
		//duplicate NOT found:
			//frequency++
			//latest++
			//strcpy
	
	//printf("%s has been added\n", tag);
	/*printf("S: %s / %s; V: %d; L: %d; F: %d LI: %d\n", 
	tag, 
	hash_table[value].linkedList[linkedIndex].string, 
	value, 
	hash_table[value].latest,
	hash_table[value].linkedList[linkedIndex].frequency,
	linkedIndex);*/
}

void readHash(int value, int linkedIndex)
{
	printf(" %d\n", hash_table[value].linkedList[linkedIndex].frequency);
}
	/*
	if (hash_table[value] > 0){
		hash_table[value].string = tag;
		if (hash_table[value].count == 0){
			hash_table[value].count = 1
		}
		else hash_table[value].count += 1; 
	}*/
