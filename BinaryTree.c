#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
	int value;
	struct Node* left;
	struct Node* right;
};

struct Node* createNode(int value);
void add(int value);
void addRecusive(int value, struct Node* ptr);
void printTree();
void printTreeRecursive(struct Node* ptr);
struct Node* getSmallest();
struct Node* getBiggest();
void removeNode(int value);
struct Node *removeNodeRecursive(int value,struct Node *ptr);


struct Node *root;

int main() {
	add(4);
	add(1);
	add(3);
	add(20);
	removeNode(4);
	removeNode(1);
	printTree();
	return 0;
}

struct Node* createNode(int value) {
	struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
	ptr->left = NULL;
	ptr->right = NULL;
	ptr->value = value;
	return ptr;
}
void addRecusive(int value, struct Node* ptr) {
	if (ptr == NULL) {
		return;
	}
	if (value > ptr->value) {
		if (ptr->right == NULL) {
			ptr->right = createNode(value);
			return;
		}
		addRecusive(value, ptr->right);
		return;
	}
	if(value < ptr->value) {
		if (ptr->left == NULL) {
			ptr->left = createNode(value);
			return;
		}
		addRecusive(value, ptr->left);

	}
}
void add(int value) {
	if (root == NULL) {
		root = createNode(value);
		return;
	}
	addRecusive(value, root);
}
void printTreeRecursive(struct Node* ptr) {
	if (ptr == NULL) {
		return;
	}
	printTreeRecursive(ptr->left);
	printf("%d\n", ptr->value);
	printTreeRecursive(ptr->right);
}
void printTree() {
	if (root == NULL) {
		printf("Empty tree\n");
		return;
	}
	printTreeRecursive(root);

}
struct Node* getSmallest(struct Node *root) {
	if (root == NULL) {
		return NULL;
	}
	struct Node* ptr = root;
	while (ptr->left != NULL) {
		ptr = ptr->left;
	}
	return ptr;
}
struct Node* getBiggest(struct Node* root) {
	if (root == NULL) {
		return NULL;
	}
	struct Node* ptr = root;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	return ptr;
}
//Quero remover o 3;
struct Node *removeNodeRecursive(int value,struct Node *ptr) {
	if (ptr == NULL) {
		return NULL;
	}
	if (value > ptr->value) {
		if (ptr->right != NULL) {
			if (ptr->right->value == value) {
				if (ptr->right->left == NULL && ptr->right->right == NULL) {
					struct Node* ptrAux = ptr->right;
					ptr->right = NULL;
					return ptrAux;
				}
				if (ptr->right->left != NULL) {
					struct Node* biggest = getBiggest(ptr->right->left);
					struct Node* auxPtr = NULL;
					if (removeNodeRecursive(biggest->value, ptr->right) != NULL) {
						auxPtr = ptr->right;
						ptr->right = biggest;
						return auxPtr;
					}
				}
				if (ptr->right->right != NULL) {
					struct Node* smallest = getSmallest(ptr->right->right);
					struct Node* auxPtr = NULL;
					if (removeNodeRecursive(smallest->value, ptr->right) != NULL) {
						auxPtr = ptr->right;
						ptr->right = smallest;
						return auxPtr;
					}
				}
			}
			else {
				return removeNodeRecursive(value, ptr->right);
			}
		}
	}
	if (value < ptr->value) {
		if (ptr->left != NULL) {
			if (ptr->left->value == value) {
				if (ptr->left->left == NULL && ptr->left->right == NULL) {
					struct Node* ptrAux = ptr->left;
					ptr->left = NULL;
					return ptrAux;
				}
				if (ptr->left->left != NULL) {
					struct Node* biggest = getBiggest(ptr->left->left);
					struct Node* auxPtr = NULL;
					if (removeNodeRecursive(biggest->value, ptr->left) != NULL) {
						auxPtr = ptr->left;
						ptr->left = biggest;
						return auxPtr;
					}
				}
				if (ptr->left->right != NULL) {
					struct Node* smallest = getSmallest(ptr->left->right);
					struct Node* auxPtr = NULL;
					if (removeNodeRecursive(smallest->value, ptr->left) != NULL) {
						auxPtr = ptr->left;
						ptr->left = smallest;
						return auxPtr;
					}
				}
			}
			else {
				return removeNodeRecursive(value, ptr->left);
				}
			
		}
	}
}
void removeNode(int value) {
	if (root == NULL) {
		return;
	}
	if (root->value == value) {
		if (root->left != NULL) {
			struct Node* auxPtr = getBiggest(root->left);
			if (removeNodeRecursive(auxPtr->value, root) != NULL) {
				auxPtr->left = root->left;
				auxPtr->right = root->right;
				free(root);
				root = auxPtr;
				return;
			}
		}
		else if (root->right != NULL) {
			struct Node* auxPtr = getSmallest(root->right);
			if (removeNodeRecursive(auxPtr->value, root) != NULL) {
				auxPtr->left = root->left;
				auxPtr->right = root->right;
				free(root);
				root = auxPtr;
				return;
			}
		}
		else {
			free(root);
		}
	}
	free(removeNodeRecursive(value, root));
}
