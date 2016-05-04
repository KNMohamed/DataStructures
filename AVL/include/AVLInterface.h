#include "AVLTypes.h"

AVLTreeNode* DoubleLeft(AVLTreeNode* Root);
AVLTreeNode* DoubleRight(AVLTreeNode* Root);
AVLTreeNode* LeftRight(AVLTreeNode* Root);
AVLTreeNode* RightLeft(AVLTreeNode* Root);
AVLTreeNode* findKey(AVLTreeNode * Tree, char *str);
int maxHeight(AVLTreeNode* T);
void deleteTree(AVLTreeNode *T);
AVLTreeNode *createNode(char * str);
int getBalance(AVLTreeNode * T);
void insertNode(AVLTreeNode **Tree, char *str);
void deleteNode(AVLTreeNode **Tree, char * str);
void traverse(AVLTreeNode *T, TraversalOrder TO);
int getSize(AVLTreeNode *T);
void findAboveFrequency(AVLTreeNode * T, int frequency);
