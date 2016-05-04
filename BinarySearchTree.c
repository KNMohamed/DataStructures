#include <stdio.h>
#include <stdlib.h>

typedef enum{InOrder,PostOrder,PreOrder} TraversalOrder;

struct tree_node{
	struct tree_node *left,*right;
	int value;
};

struct tree_node* new_node(int v){
	struct tree_node *temp = (struct tree_node*)malloc(sizeof(*temp));
	if(temp == NULL){ printf("Unable to allocate Memory!\n"); exit(0); }
	temp->value = v;	
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void tree_insert(struct tree_node *n, int v){
	if(n == NULL)
		n = new_node(v);
	else if(v < n->value)
		tree_insert(n->left,v);
	else if(v > n->value)
		tree_insert(n->right,v);	
}

//Post Order erase of tree node and children
void tree_erase(struct tree_node *t){
	if(t == NULL) return;
	tree_erase(t->left);
	tree_erase(t->right);
	free(t);
}

void traverse(struct tree_node *t, TraversalOrder TO){
	if(t != NULL){
		if(TO == PreOrder){
			printf("%d",t->value);
			traverse(t->left,PreOrder);
			traverse(t->right,PreOrder);
		}else if(TO == InOrder){
			printf("(");
			traverse(t->left,InOrder);
			printf("%d",t->value);
			traverse(t->right,InOrder);
			printf(")");
		}else if(TO == PostOrder){
			traverse(t->left,PostOrder);
			traverse(t->right,PostOrder);
			printf("%d",t->value);
		}
	}
}

int main(int argc, char *argv[]){
	struct tree_node *t = NULL;
	tree_insert(t,5);
	tree_insert(t,3);
	tree_insert(t,1);
	tree_insert(t,4);
	tree_insert(t,6);
	traverse(t,1);
	return 0;
}
