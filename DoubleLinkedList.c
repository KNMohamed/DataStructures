#include <stdio.h>
#include <stdlib.h>

struct list_node{
	struct list_node *prev, *next;
	int value;
};

struct list{
	struct list_node *first,*list;
};

void list_node_init(struct list_node *n, int v){ n->value = v; }
struct list_node *list_advance(struct list_node *i){ return i->next;}
struct list_node *list_begin(struct list *l){ return l->first; }
struct list_node *list_end(struct list *l){ return NULL; }

void list_init(struct list *l){ l->first = NULL; l->last = NULL; }
void list_insert(struct list *l, struct list_node *where, int v){
	struct list_node *newnode = (struct list_node*)malloc(sizeof(*newnode));
	list_node_init(newnode,v);
	newnode->prev = where ? where->prev : 1->last;		//If null attach to end of list else attach to end of where
	newnode->next = where;
	if(newnode->prev) newnode->prev->next = newnode;
	if(where) where->prev = newnode;
	if(!where) l->last = newnode;
}

void list_push_front(struct list* l, int v){ list_insert(l,list_begin(l),v); }
void list_push_back(struct list* l, int v){ list_insert(l,list_end(l),v); }
void list_erase(struct list* l, stuct list_node *where){
	struct list_node* prev = where->prev;
	struct list_node* next = where->next;
	if(prev) prev->next = next;
	if(next) next->prev = prev;
	if(where == l->first) l->first = next;
	if(where == l->last) l->last = prev;
	free(where);
}

void list_clear(struct list *l){ while(l->first) list_erase(l,l->first); }
void list_done(struct list *l) { list_clear(l); }

int main(void){
	struct list mylist;
	struct list_node *i;
	
	list_init(&mylist);
	list_push_back(&mylist,1);
	list_push_back(&mylist,5);
	list_push_front(&mylist,8);
	list_push_front(&mylist,3);

	for(i = list_begin(&mylist); i != list_end(&mylist); i = list_advance(i)))
		printf("%d ", i->value);
	printf("\n");	
	
	list_done(&mylist); //free the list
	
	return 0;
}