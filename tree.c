/*
*	Created by Nan Mihai on 05.05.2021
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Tree parent, Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->parent = parent;
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(Tree *root, Tree parent, Item value) {
	// TODO 0
	*root = malloc(sizeof(TreeNode));
	(*root)->parent = parent;
	(*root)->left = NULL;
	(*root)->right = NULL;
	(*root)->value = value;

}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/

//cu parametru parinte
Tree insert_param(Tree root, Item value, Tree parent) {
	if(root == NULL) {
		return createTree(parent, value);
	}
	if(root->value == value) return root;
	if(value < root->value) {
		if(root->left == NULL)
			root->left = createTree(root, value);
		else		
			root->left = insert_param(root->left, value, root);
	}
	else {
		if(root->right == NULL)
			root->right = createTree(root, value);
		else
			root->right = insert_param(root->right, value, root);
	}
	return root;
}

Tree insert(Tree root, Item value) {
	// TODO 1

	//cu parametrul parinte
	root = insert_param(root, value, NULL);
	return root;
	



	// if(root == NULL) {
	// 	return createTree(NULL, value);
	// }
	// if(root->value == value) return root;
	// if(value < root->value) {

	// 	if(root->left == NULL) {
	// 		root->left = createTree(root, value);

	// 	} else		
	// 	root->left = insert(root->left, value);
	// }
	// else {
	// 	if(root->right == NULL) {
	// 		root->right = createTree(root, value);

	// 	} else
	// 	root->right = insert(root->right, value);
	// }
	// return root;
}


/*
*	Funcție care verifică dacă un arbore este vid sau nu
*		- întoarce 1 dacă arborele este vid
*		- întoarce 0 dacă arborele nu este vid
*/
int isEmpty(Tree root) {
	// TODO 2
	return root == NULL;
}

/*
*	Funcție care verifică dacă o valoare există sau nu în arbore
*		- 1 dacă value există în arbore
*		- 0 dacă value nu există în arbore
*/
int contains(Tree tree, Item value) {
	// TODO 3
	if(tree == NULL) return 0;
	if(tree->value == value)
		return 1;
	if(tree->value < value)
		return contains(tree->right, value);
	if(tree->value > value)
		return contains(tree->left, value);
	return 0;
}

/*
*	Funcție care determină elementul minim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/

//iterativ
Tree minimum(Tree tree) {
	// TODO 4.1
	//ITERATIVVVV
	if(tree == NULL) return NULL;
	// Tree iter = tree;
	while(tree->left != NULL) {
		tree = tree->left;
	}
	return tree;

	//RECURSIV
	// if(tree == NULL) return NULL;
	// if(tree->left == NULL)
	// 	return tree;
	// return minimum(tree->left);
}

/*
*	Funcție care determină elementul maxim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree maximum(Tree tree) {
	// TODO 4.2
		if(tree == NULL) return NULL;
	if(tree->right == NULL)
		return tree;
	return maximum(tree->right);
}

/*
*	Funcție care determină succesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree find(Tree tree, Item value) {
	// TODO 3
	if(tree == NULL) return NULL;
	if(tree->value == value)
		return tree;
	if(tree->value < value)
		return find(tree->right, value);
	if(tree->value > value)
		return find(tree->left, value);
	return 	NULL;
}

int order(Tree tree) {
	if(tree == NULL) return 0;
	if(tree->parent == NULL) return 0;
	return (tree == tree->parent->left) ? -1 : 1;
}

Tree successor(Tree root, Item value) {
	// TODO 5
	Tree tree= find(root, value);
	if(tree == NULL) {
		return NULL;}
	if(tree->right == NULL) {
		while (order(tree) == 1)
			tree = tree->parent;
		return tree->parent;
	}
	return minimum(tree->right);
}

/*
*	Funcție care determină predecesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree predecessor(Tree root, Item value) {
	// TODO 6
	Tree tree= find(root, value);
	if(tree == NULL)
		return NULL;
	if(tree->left == NULL) {
		while (order(tree) == -1)
			tree = tree->parent;
		return tree->parent;
	}
	return maximum(tree->left);
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void destroyTree(Tree *root) {
	// TODO
	if(*root == NULL) return;
	destroyTree(&(*root)->left);
	destroyTree(&(*root)->right);
	free(*root);
	(*root) = NULL;
}

/*
*	Funcție care șterge un nod cu o anumită valoare din arbore
*/
Tree delete(Tree root, Item value) {
	// TODO 7
	Tree temp;
	if(root == NULL) return NULL;
	if(root->value > value)
		root->left = delete(root->left, value); 		
	else if(root->value < value)
		root->right = delete(root->right, value);
	else {
		if(root->left != NULL && root->right != NULL){
			temp = minimum(root->right);
			root->value = temp->value;
			root->right = delete(root->right, temp->value);
		}
		else {
			temp = root;
			if(root ->left != NULL)	root = root->left;
			else root = root->right;
			free(temp);
		}
	}
	return root;
}

/*
*	Funcție care determină cel mai apropiat strămoș comun pentru
* două noduri având cheile value1 și value2
*/

int gasit(Tree* vector, Tree node) {
	for(int i = 0; vector[i] != NULL; i++) {
		if(vector[i]->value == node->value)
		return 1; 
	}
	return 0;
}

Tree lowestCommonAncestor(Tree root, Item value1, Item value2) {
	// TODO 8
	Tree node1 = find(root, value1);
	Tree node2 = find(root, value2);
	if(node1 == NULL) return node2->parent;
	if(node2 == NULL) return node1->parent;
	int contor = 0;
	Tree *vector = malloc(50 * sizeof(Tree));
	Tree iter1 = node1;
	while(order(iter1) != 0) {
		vector[contor++] = iter1;		
		iter1 = iter1->parent;
	}
	Tree iter2 = node2;
	while(order(iter2) != 0) {
		if(gasit(vector, iter2) == 1)
			return iter2;
		iter2 = iter2->parent;
	}
	return root;

	// varinata de pe net
	/*
		if(root->value > value1 && root->value > value2)
			return lowestCommonAncestor(root->left, value1, value2);
		if(root->value < value1 && root->value < value2)
			return lowestCommonAncestor(root->right, value1, value2);
		return root;
	*/
}
