#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "AVLInterface.h"
#define MAXARRAY 200

AVLTreeNode* openFile(FILE *fileprt);
int getInput();
void menu();
void welcomeScreen();

int main(int argc, char*argv[]){
	AVLTreeNode *Tree = NULL;
	AVLTreeNode *temp;
	FILE *F;
	char fileName[MAXARRAY];
	char selection[MAXARRAY];
	int input;
	int i;
	bool fileOpen = false;
	
	welcomeScreen();
	do{
		menu();
		printf("avl/> ");
		input = getInput();
		switch(input){
			case 1:
				printf("filename: ");
				fgets(fileName,MAXARRAY,stdin);
				fileName[strlen(fileName)-1] = '\0';
				F = fopen(fileName,"r");
				Tree = openFile(F);
				fileOpen = true;
				break;
			case 2:
				printf("find: ");
				fgets(selection,MAXARRAY,stdin);
				selection[strlen(selection) - 1] = '\0';
				temp = findKey(Tree,selection);
				if(temp == NULL)
					printf("No_such_key\n");
				else
					printf("Key: %s, Frequency: %d\n", temp->Key, temp->count);
				break;
			case 3:
				printf("Insert Key: ");
				fgets(selection,MAXARRAY,stdin);
				selection[strlen(selection) - 1] = '\0';
				insertNode(&Tree,selection);
				temp = findKey(Tree,selection);
				if(temp == NULL)
					printf("No_such_key\n");
				else
					printf("Key: %s, Frequency: %d\n", temp->Key, temp->count);				
				break;
			case 4:
				printf("remove Key: ");
				fgets(selection,MAXARRAY,stdin);
				selection[strlen(selection) - 1] = '\0';
				deleteNode(&Tree,selection);
				temp = findKey(Tree,selection);
				if(temp != NULL)
					printf("Key: %s, Frequency: %d\n", temp->Key, temp->count);	
				break;
			case 5:
				printf("Height: %d\n", maxHeight(Tree));
				printf("Size: %d nodes\n", getSize(Tree));
				break;
			case 6:
				do{
					printf("frequency: ");
					i = getInput();
					if(i == -1)
						printf("Invalid Input\n\n");
					else
						findAboveFrequency(Tree,i);
				}while(i == -1);
				break;
			case 7:
				deleteTree(Tree);
				if(fileOpen == true){
					fclose(F);
				}
				printf("Quitting....\n");
				break;
			default:
				printf("INVALID INPUT!\n\n");
		}
	}while(input != 7);
	return 0;
}

AVLTreeNode* openFile(FILE *fileptr){
	AVLTreeNode *Tree = NULL;
	char buff[MAXARRAY];
	
	while(fscanf(fileptr,"%s",buff) != EOF){
		insertNode(&Tree,buff);
	}	
	return Tree;
}

int getInput()
{
    char buffer[MAXARRAY];
    int i, string2Num, length;
    char holder;
 
    fgets(buffer,MAXARRAY,stdin);
    if(buffer[0] == '\n'){
        return -1;
    }else{
		buffer[strlen(buffer) - 1] = '\0';
		length = strlen(buffer);
        for(i=0;i<length;i++){
            holder = buffer[i];
            if(!isdigit(holder)){
                return -1;
            }else{
                string2Num = atoi(buffer);
			}
		}
    return(string2Num);
	}
}

void welcomeScreen(){
	printf("WELCOME TO THE AVL TREE PROGRAM!\n");
	printf("NAME: Khalid Mohamed\n");
	printf("STUDENT ID: 0832889\n");
}

void menu(){
	printf(" 1) Initialization\n");
	printf(" 2) Find\n");
	printf(" 3) Insert\n");
	printf(" 4) Remove\n");
	printf(" 5) Check height and size\n");
	printf(" 6) Find all (above a give frequency)\n");
	printf(" 7) Exit\n");
}


