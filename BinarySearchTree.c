#include <stdio.h>
#include <stdlib.h>

typedef enum{InOrder,PostOrder,PreOrder} TraversalOrder;

struct tree_node{
	struct tree_node *left,*right;
	int value;
};

struct tree{
	struct tree_node *root;
	int num_nodes;
};

void tree_node_init(struct tree_node *n, int v) { n->value = v; }
void tree_init(struct tree *t){ t->root = NULL; t->num_nodes = 0; }
void tree_insert(struct tree *t, struct tree_node *i){


}

struct tree_node* new_node(int v){
	struct tree_node *temp = (struct tree_node*)malloc(sizeof(*temp));
	if(temp == NULL){ printf("Unable to allocate Memory!\n"); exit(0); }
	temp->value = v;	
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

//Post Order erase of tree node and children
void tree_erase(struct tree_node *t){
	if(t == NULL) return;
	tree_erase(t->left);
	tree_erase(t->right);
	free(t);
}

void tree_clear(struct tree *t){
	tree_erase(t->root);
	t->num_nodes = 0;
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
	return 0;
}
