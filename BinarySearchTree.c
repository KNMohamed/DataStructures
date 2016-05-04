#include <stdio.h>
#include <stdlib.h>

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

tree_node new_node(int v){
	tree_node *temp = (tree_node*)malloc(sizeof(*temp));
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

void tree_clear(struct tree){
	tree_erase(tree->root);
	tree->num_nodes = 0;
}

