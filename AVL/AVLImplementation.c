#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLInterface.h"

AVLTreeNode* DoubleLeft(AVLTreeNode* Root){
	AVLTreeNode* temp = Root->leftChild;
	Root->leftChild = temp->rightChild;
	temp->rightChild = Root;
	Root->height = maxHeight(Root);
	temp->height = maxHeight(temp);
	return temp;
}

AVLTreeNode* DoubleRight(AVLTreeNode* Root){
	AVLTreeNode* temp;
	temp = Root->rightChild;
	Root->rightChild = temp->leftChild;
	temp->leftChild = Root;
	Root->height = maxHeight(Root);
	temp->height = maxHeight(temp);
	return temp;
}

AVLTreeNode* LeftRight(AVLTreeNode* Root){
	Root->leftChild = DoubleRight(Root->leftChild);
	Root = DoubleLeft(Root);
	return Root;
}

AVLTreeNode* RightLeft(AVLTreeNode* Root){
	Root->rightChild = DoubleLeft(Root->rightChild);
	Root = DoubleRight(Root);
	return Root;	
}

void deleteTree(AVLTreeNode *T){
	if(T != NULL){
		deleteTree(T->leftChild);
		deleteTree(T->rightChild);
		free(T->Key);
		free(T);
	}
}

AVLTreeNode *createNode(char * str){
	AVLTreeNode *temp;
	temp = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
	temp->Key = (char*)malloc((strlen(str)+1) * sizeof(char));
	strcpy(temp->Key,str); 
	temp->count = 1;
	temp->rightChild = NULL;
	temp->leftChild = NULL;
	return temp;
}

int maxHeight(AVLTreeNode* T){
	int leftHeight, rightHeight;
	if(T== NULL){
		return 0;
	}
	if(T->leftChild == NULL)
		leftHeight = 0;
	else
		leftHeight = T->leftChild->height + 1;
	if(T->rightChild == NULL)
		rightHeight = 0;
	else
		rightHeight = T->rightChild->height + 1;
		
	
	if(leftHeight > rightHeight)
		return leftHeight;
	return rightHeight;
}

int getBalance(AVLTreeNode * T){
	int leftHeight, rightHeight;
	if(T== NULL){
		return 0;
	}
	if(T->leftChild == NULL)
		leftHeight = 0;
	else
		leftHeight = T->leftChild->height + 1;
	if(T->rightChild == NULL)
		rightHeight = 0;
	else
		rightHeight = T->rightChild->height + 1;
		
	return (leftHeight - rightHeight);
}

void insertNode(AVLTreeNode **Tree, char *str){		
	if(*Tree == NULL){
		(*Tree) = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
		(*Tree)->Key = (char*)malloc((strlen(str)*sizeof(char)) + 1);		
		(*Tree)->count = 1;
		(*Tree)->leftChild = NULL;
		(*Tree)->rightChild = NULL;
		strcpy((*Tree)->Key,str);
	}else{
		if(strcmp((*Tree)->Key,str) == 0){
			(*Tree)->count += 1; 
			return;
		}else{
			if(strcmp((*Tree)->Key,str) < 0){
				insertNode(&(*Tree)->rightChild,str);
				if(getBalance(*Tree) < -1){
					if(strcmp((*Tree)->rightChild->Key,str) < 0)
						(*Tree) = DoubleRight(*Tree);
					else
						(*Tree) = RightLeft(*Tree);
				}
			}else if(strcmp((*Tree)->Key,str) > 0){    /*If Tree is leaning to left*/
				insertNode(&(*Tree)->leftChild,str);
				if(getBalance(*Tree) > 1){
					if(strcmp((*Tree)->leftChild->Key,str) > 0)
						(*Tree) = DoubleLeft(*Tree);
					else
						(*Tree) = LeftRight(*Tree);					
				}
			}
		}
	}
	(*Tree)->height = maxHeight(*Tree);
}

void deleteNode(AVLTreeNode **Tree, char * str){
	AVLTreeNode *temp;
	
	if(*Tree == NULL){
		printf("No_such_key\n");
		return;
	}else{
		if(strcmp((*Tree)->Key,str) == 0){
			if((*Tree)->count > 1){		/*If count is greater than 1 subtract 1 from count*/
				(*Tree)->count -= 1;
			}else{
				if((*Tree)->rightChild != NULL){
					temp = (*Tree)->rightChild;
					while(temp->leftChild != NULL)
						temp = temp->leftChild;
					
					strcpy((*Tree)->Key,temp->Key);
					(*Tree)->count = temp->count;
					
					deleteNode(&(*Tree)->rightChild,temp->Key);
					if(getBalance(*Tree) == 2){
						if(getBalance((*Tree)->leftChild) >= 0)
							(*Tree) = DoubleLeft(*Tree);
						else
							(*Tree) = LeftRight(*Tree);					
					}					
				}else{
					(*Tree) = (*Tree)->leftChild;
				}		
			}
		}else{
			if(strcmp((*Tree)->Key,str) < 0){
				deleteNode(&(*Tree)->rightChild,str);
				if(getBalance(*Tree) == -2){
					if(getBalance((*Tree)->rightChild) <= 0)
						(*Tree) = DoubleRight(*Tree);
					else
						(*Tree) = RightLeft(*Tree);
				}
			}else if(strcmp((*Tree)->Key,str) > 0){    /*If Tree is leaning to left*/
				deleteNode(&(*Tree)->leftChild,str);
				if(getBalance(*Tree) == 2){
					if(getBalance((*Tree)->leftChild) >= 0)
						(*Tree) = DoubleLeft(*Tree);
					else
						(*Tree) = LeftRight(*Tree);					
				}				
			}
		}
	}
	(*Tree)->height = maxHeight(*Tree);
}

AVLTreeNode* findKey(AVLTreeNode * Tree, char *str){
	if(Tree == NULL)
		return NULL;
	if(strcmp(Tree->Key,str) > 0)
		return findKey(Tree->leftChild,str);
	else if(strcmp(Tree->Key,str) < 0)
		return findKey(Tree->rightChild,str);
	else
		return Tree;
}

void traverse(AVLTreeNode *T, TraversalOrder TO){
	if(T != NULL){
		if(TO == PreOrder){
			printf("%d\n",getBalance(T));
			traverse(T->leftChild,PreOrder);
			traverse(T->rightChild,PreOrder);
		}else if(TO == InOrder){
			traverse(T->leftChild,InOrder);
			printf("%d\n",getBalance(T));
			traverse(T->rightChild,InOrder);
		}else if(TO == PostOrder){
			traverse(T->leftChild,PostOrder);
			traverse(T->rightChild,PostOrder);
			printf("%d\n",getBalance(T));				
		}
	}
}

void findAboveFrequency(AVLTreeNode * T, int frequency){
	if(T != NULL){
		if(T->count >= frequency){
			printf("Key: %s, ",T->Key);
			printf("Frequency: %d\n",T->count);
		}
		findAboveFrequency(T->leftChild,frequency);
		findAboveFrequency(T->rightChild,frequency);
	}
}

int getSize(AVLTreeNode *T){
	int count = 0;
	if(T != NULL){
		count = 1 + getSize(T->leftChild) + getSize(T->rightChild);
	}
	return count;		
}
	
