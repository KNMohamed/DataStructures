typedef enum{InOrder,PostOrder,PreOrder} TraversalOrder;
typedef enum { false, true } bool;
typedef char* KeyType;

typedef struct AVLTreeNodeTag{
	KeyType Key;
	int height;
	int count;
	struct AVLTreeNodeTag *leftChild;
	struct AVLTreeNodeTag *rightChild;
}AVLTreeNode;
