﻿// Binary tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>       /* time */
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

struct treeElement {
	int key;
	treeElement *left;
	treeElement *right;
	char *word;
};

#pragma region Binary tree functions

void initialize(treeElement *&root) {
	root = NULL;
}

#pragma region Rotation

//if return == 0 govenNode doesn't exist
//if return == 1 found parent or found parent and grandfather
int findFamily(treeElement *root, treeElement *child, treeElement *&parent, treeElement *&grandfather)
{
	parent = NULL;
	grandfather = NULL;

	treeElement *actual = root;

	while (child->key != actual->key)
	{
		if (parent != NULL)
			grandfather = parent;

		parent = actual;

		if (child->key < actual->key)
			if (actual->left == NULL)
				return 0;
			else
				actual = actual->left;
		else
			if (actual->right == NULL)
				return 0;
			else
				actual = actual->right;
	}

	return 1;
}

void rotateRight(treeElement *&root, treeElement *child)
{
	treeElement *grandfather, *parent, *actual = root;

	if (0 == findFamily(root, child, parent, grandfather))
		cout << "UFORTUNATELLY I CANT FIND FAMILY OF NOT EXISTING ELEMENT" << endl;

	if (grandfather != NULL)
	{
		if (grandfather->right == parent)
			grandfather->right = child;
		else grandfather->left = child;
	}
	else
		root = child;

	treeElement *temp = child->right;
	child->right = parent;
	parent->left = temp;

	return;
}

void rotateLeft(treeElement *&root, treeElement *child)
{
	treeElement *grandfather, *parent, *actual = root;

	if (0 == findFamily(root, child, parent, grandfather))
		cout << "UFORTUNATELLY I CANT FIND FAMILY OF NOT EXISTING ELEMENT" << endl;

	if (grandfather != NULL)
	{
		if (grandfather->right == parent)
			grandfather->right = child;
		else grandfather->left = child;
	}
	else
		root = child;

	treeElement *temp = child->left;
	child->left = parent;
	parent->right = temp;

	return;
}

#pragma endregion

void promoteNode(treeElement *&root, treeElement *child)
{
	while (root != child)
	{
		treeElement *parent, *grandFather;

		findFamily(root, child, parent, grandFather);

		if (grandFather == NULL)
		{
			if (parent->right == child)
				rotateLeft(root, child);
			else
				rotateRight(root, child);

			return;
		}

		//zig-zig
		if ((grandFather->left == parent) && (parent->left == child))
		{
			rotateRight(root, parent);
			rotateRight(root, child);
		}
		else if ((grandFather->right == parent) && (parent->right == child))
		{
			rotateLeft(root, parent);
			rotateLeft(root, child);
		}
		//zig-zag
		else if ((grandFather->right == parent) && (parent->left == child))
		{
			rotateRight(root, child);
			rotateLeft(root, child);
		}
		else if ((grandFather->left == parent) && (parent->right == child))
		{
			rotateLeft(root, child);
			rotateRight(root, child);
		}
	}
}

//return == 0 oznacza, że dany węzeł już istnieje
//return == 1 oznacza prawidłowe zakończenie procesu dodawania
int addNode(treeElement *&root,int givenKey) {
	treeElement	*temp;
	temp = new treeElement;

	temp->key = givenKey;
	temp->left = NULL;
	temp->right = NULL;

	char *word = new char[16];

	for (int i = 0; i < 16; i++)
	{
		word[i] = rand() % 26 + 'a';
	}
	
	word[16] = NULL;
	
	temp->word = word;

	//cout << "Temp >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;

	if (root == NULL)
	{
		root = temp;
		cout << "\nAdded element >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;
	}
	else 
	{
		treeElement *actual = root, *parent = NULL, *grandfather = NULL;

		while (1)
		{
			//Obsługa wyjątku kiedy mamy już węzeł o tym samym kluczu
			if (givenKey == actual->key)
			{
				cout << "Node with given key already exist!\n";
				delete temp;
				return 0;
			}

			if (givenKey < actual->key)
			{
				if (actual->left == NULL)
				{
					actual->left = temp;
					promoteNode(root, temp);
					cout << "\nAdded element >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;
					return 1;
				}
				else
				{
					actual = actual->left;
				}
			}
			else
			{
				if (actual->right == NULL)
				{
					actual->right = temp;
					promoteNode(root, temp);
					cout << "\nAdded element >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;
					return 1;
				}
				else
				{
					actual = actual->right;
				}
			}
		} 
	}
	//cout << "Root >> Key: " << root->key << " Left: " << root->left << " Right: " << root->right << "\nWord: " << root->word << endl;

}

#pragma region All ordered search

int preorderCounter = 0;

void showPreorderRec(treeElement *&root)
{
	if (root)
	{
		cout << root->key << " - ";
		preorderCounter++;

		//cout << "\nShowed >> Key: " << root->key << " Left: " << root->left << " Right: " << root->right << "\nWord: " << root->word << endl;
		showPreorderRec(root->left);
		showPreorderRec(root->right);
	}
}

int inorderCounter = 0;

void showInorderRec(treeElement *&root)
{
	if (root)
	{
		inorderCounter++;

		showInorderRec(root->left);
		cout << root->key << " - ";
		showInorderRec(root->right);
	}
}

int postorderCounter = 0;

void showPostorderRec(treeElement *&root)
{
	if (root)
	{
		postorderCounter++;

		showPostorderRec(root->left);
		showPostorderRec(root->right);
		cout << root->key << " - ";
	}
}

void showPreorder(treeElement *&root) 
{
	preorderCounter = 0;
	cout << endl;
	showPreorderRec(root);
	cout << "\nPreorder occurrences >> " << preorderCounter << endl;
}

void showInorder(treeElement *&root)
{
	inorderCounter = 0;
	cout << endl;
	showInorderRec(root);
	cout << "\nInorder occurrences >> " << inorderCounter << endl;
}

void showPostorder(treeElement *&root)
{

	postorderCounter = 0;
	cout << endl;
	showPostorderRec(root);
	cout << "\nPostorder occurrences >> " << postorderCounter << endl;
}

#pragma endregion

treeElement* findTreeEl(treeElement *&root, int X)
{	
	treeElement *actual = root;
	bool found = false;

	while ((actual!=NULL) && found==false)
	{
		if (actual->key == X) found = true;
		else if (actual->key < X) actual = actual->right;
		else actual = actual->left;
	}

	//if(found) cout << "\nFound >> Key: " << actual->key << " Left: " << actual->left << " Right: " << actual->right << "\nWord: " << actual->word << endl;
	//else cout << "\nNot found an element with key "<< X << endl;

	return(actual);

}

void showTreeEl(treeElement *&root, int givenKey)
{
	treeElement *temp = findTreeEl(root, givenKey);

	if (temp) cout << "\nFound >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;
	else cout << "\nNot found an element with key "<< givenKey << endl;
}

void randomElPutting(treeElement *&root, int amount)
{
	int key = rand() % 29974 + 26;

	for (int i = 0; i < amount; i++)
	{
		while (findTreeEl(root, key) != NULL)
		{
			key = rand() % 18989 + 11;
		}

		addNode(root, key);
	}
}

void deleteEl(treeElement *&root, int givenKey)
{
	treeElement *parent = NULL, *actual = root;

	//Parent and key search :
	while ((actual != NULL)&&(givenKey != actual->key))
	{
		parent = actual;
		if (givenKey > actual->key) actual = actual->right;
		else actual = actual->left;
	}

	//There isn't given key - return
	if (actual == NULL) 
	{
		cout << "\nDeleted element doesn't exist!" << endl;
		return;
	}

	cout << "\nDeleted element >> Key: " << actual->key << " Left: " << actual->left << " Right: " << actual->right << "\nWord: " << actual->word << endl;

	//Case when deleted element is a leaf:
	if ((actual->left == NULL) && (actual->right == NULL))
	{
		if (actual == root)
		{
			delete actual;
			root = NULL;
			return;
		}

		if (parent->left == actual) parent->left = NULL;
		else parent->right = NULL;

		delete actual;
		actual = NULL;

		return;
	}

	if ((parent == NULL) && (actual == root))
	{
		if (actual->left == NULL)
		{
			root = actual->right;
			delete actual;
			actual = NULL;
			return;
		}
		if (actual->right == NULL)
		{
			root = actual->left;
			delete actual;
			actual = NULL;
			return;
		}

		root = actual->right;

		treeElement *inside=actual->right;

		while (inside->left != NULL)
		{
			inside = inside->left;
		}

		inside->left = actual->left;
		delete actual;
		actual = NULL;
		return;

	}

	//Case when deleted element have only right subtree:
	if (actual->left == NULL)
	{
		if (parent->right == actual) parent->right = actual->right;
		else parent->left = actual->right;

		delete actual;
		actual = NULL;
		return;
	}

	//Case when deleted element have only left subtree:
	if (actual->right == NULL)
	{
		if (parent->right == actual) parent->right = actual->left;
		else parent->left = actual->left;

		delete actual;
		actual = NULL;
		return;
	}

	//Other cases with predecessor:

	treeElement *preparent = actual, *child = actual->left;

	//Search for the deepest right element after first left :
	while (child->right != NULL)
	{
		preparent = child;
		child = child->right;
	}

	//predecessor is left descendant of deleted node: 
	if (child == actual->left)
	{
		if (parent->right == actual) parent->right = child;
		else parent->left = child;

		delete actual;
		actual = NULL;
		return;
	}

	//predecessor isn't left descendant of actual node but he is his grandson or great...grandson:

	treeElement *grandChild = child->left;

	if (preparent->right == child) preparent->right = grandChild;
	else preparent->left = grandChild;

	child->left = actual->left;

	if (parent->right == actual) parent->right = child;
	else parent->left = child;

	delete actual;
	root = NULL;

	return;

}

void promoteElDeleting(treeElement *&root, int givenKey)
{
	if (root != NULL)
	{
		if (root->key == givenKey)
		{
			deleteEl(root, givenKey);
		}
		else
		{
			promoteNode(root, findTreeEl(root, givenKey));
			deleteEl(root, givenKey);
		}
	}
	
}

int memoryAmount = 0;

void freeMemoryRec(treeElement *&root)
{
	if (root)
	{
		memoryAmount++;
		treeElement *left = root->left, *right = root->right;

		delete root;

		//cout << "\nShowed >> Key: " << root->key << " Left: " << root->left << " Right: " << root->right << "\nWord: " << root->word << endl;
		freeMemoryRec(left);
		freeMemoryRec(right);
	}
}

void freeMemory(treeElement *&root)
{
	memoryAmount = 0;
	
	freeMemoryRec(root);

	initialize(root);

	cout << "\nReleased memory of " << memoryAmount  << " elements." << endl;
}

#pragma endregion

#pragma region showTreeHeight

int height, leftHeight, rightHeight,tempHeight;

int getTreeHeightRec(treeElement *root)
{
	if (root == NULL) {
		return -1;
	}

	int leftHeight = getTreeHeightRec(root->left);
	int rightHeight = getTreeHeightRec(root->right);

	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	}
	else {
		return rightHeight + 1;
	}

}

int getTreeHeight(treeElement *root)
{

	/*height = getTreeHeightRec(root) + 1;

	return height;*/

	if (root == NULL)
		return 0;

	queue<treeElement *> que;

	que.push(root);
	int height = 0;

	while (1)
	{
		int nCounter = que.size();
		if (nCounter == 0)
			return height;

		height++;
		
		while (nCounter > 0)
		{
			treeElement *node = que.front();
			que.pop();
			if (node->left != NULL)
				que.push(node->left);
			if (node->right != NULL)
				que.push(node->right);
			nCounter--;
		}
	}
}

void showTreeHeight(treeElement *root)
{
	
	height = getTreeHeightRec(root)+1;

	cout << "\nTree height >> " << height << endl;
}

#pragma endregion

void hardNodeAdding(treeElement *&root, int givenKey)
{
	while (addNode(root, givenKey) == 0) { givenKey++; }
}

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	//Time start:
	clock_t begin, end;
	double time_spent;
	begin = clock();

#pragma region File reading

	int X1, k1,k2,k3;
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, "inlab05.txt", "r");
	if (err != 0)
		return -1;
	fscanf_s(fp, "%d %d %d %d", &X1, &k1, &k2, &k3);
	fclose(fp);

	printf("I have just read from file %d %d %d %d\n", X1, k1, k2, k3);

#pragma endregion

	//CONTENT :

	treeElement *root;
	
	initialize(root);

	randomElPutting(root, X1);

	showInorder(root);
	showPreorder(root);

	hardNodeAdding(root, k1);

	showPreorder(root);

	hardNodeAdding(root, k2);

	showPreorder(root);

	//Wyszukanie węzła
	showTreeEl(root, k3);

	showPreorder(root);

	promoteElDeleting(root, k2);

	showPreorder(root);
	showInorder(root);

	freeMemory(root);

	//Time stop:
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	//Show time:
	printf("\nTime of process : %f\n", time_spent);

	//Wait for sign: 
	cin.sync();
	cin.get();

    return 0;
}

