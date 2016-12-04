// Binary tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>       /* time */
#include <iostream>
#include <string.h>

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


void addNode(treeElement *&root,int givenKey) {
	treeElement	*temp;
	temp = new treeElement;

	temp->key = givenKey;
	temp->left = NULL;
	temp->right = NULL;

	char *word = new char[100];

	for (int i = 0; i < 100; i++)
	{
		word[i] = rand() % 26 + 'a';
	}
	
	word[100] = NULL;
	
	temp->word = word;

	//cout << "Temp >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;

	if (root == NULL)
	{
		root = temp;
		cout << "\nAdded element >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;
	}
	else 
	{
		treeElement *actual = root;

		while (1)
		{
			if (givenKey == actual->key)
			{
				cout << "Node with given key already exist!\n";
				delete temp;
				return;
			}

			if (givenKey < actual->key)
			{
				if (actual->left == NULL)
				{
					actual->left = temp;
					cout << "\nAdded element >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;
					return;
				}
				else
					actual = actual->left;
			}
			else
			{
				if (actual->right == NULL)
				{
					actual->right = temp;
					cout << "\nAdded element >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;
					return;
				}
				else
					actual = actual->right;
			}
		} 
	}
	//cout << "Root >> Key: " << root->key << " Left: " << root->left << " Right: " << root->right << "\nWord: " << root->word << endl;

}


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

void randomElPutting(treeElement *&root, int amount)
{
	int key = rand() % 18989 + 11;

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

	cout << "\nReleased memory of " << memoryAmount  << " elements." << endl;
}

#pragma endregion

#pragma region Rotation

void rotateRight(treeElement *root, treeElement *grandFather, treeElement *parent, treeElement *child)
{
	if (grandFather != NULL)
	{
		if (grandFather->right == parent)
			grandFather->right = child;
		else grandFather->left = child;
	}
	else
		root = child;

	treeElement *temp = child->right;
	child->right = parent;
	parent->left = temp;

	return;
}

void rotateLeft(treeElement *root, treeElement *grandFather, treeElement *parent, treeElement *child)
{
	if (grandFather != NULL)
	{
		if (grandFather->right == parent)
			grandFather->right = child;
		else grandFather->left = child;
	}
	else
		root = child;

	treeElement *temp = child->left;
	child->left = parent;
	parent->right = temp;

	return;
}

#pragma endregion


void treeToList(treeElement *root)
{
	treeElement *grandFather = NULL, *temp = root, *temp2;

	while (temp != NULL)
	{
		if ((temp->left) != NULL)
		{
			temp2 = temp->left;
			rotateRight(root, grandFather, temp, temp->left);
			temp = temp2;
		}
		else
		{
			grandFather = temp;
			temp = temp->right;
		}
	}

}

void listToPerfectTree(treeElement *root, int N) {
	treeElement *grandFather = NULL, *temp = root, *temp2;
	int m = 1;

	while (m <= N) m = 2 * m + 1;
	m = m / 2;
	
	for (int i = 0; i < (N - m); i++)
	{
		temp2 = temp->right;
		if (temp2 != NULL)
		{
			rotateLeft(root, grandFather, temp, temp->right);
			grandFather = temp2;
			temp = temp2->right;
		}
	}

	while (m > 1)
	{
		m = m / 2;
		grandFather = NULL;
		temp = root;

		for (int i = 0; i < m; i++)
		{
			temp2 = temp->right;
			rotateLeft(root, grandFather, temp, temp->right);
			grandFather = temp2;
			temp = temp2->right;
		}
	}
}

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

	height = getTreeHeightRec(root) + 1;

	return height;
}

void showTreeHeight(treeElement *root)
{
	
	height = getTreeHeightRec(root)+1;

	cout << "\nTree height >> " << height << endl;
}

#pragma endregion

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	//Time start:
	clock_t begin, end;
	double time_spent;
	begin = clock();

	//File read:
	int X1, X2;
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, "inlab04.txt", "r");
	if (err != 0)
		return -1;
	fscanf_s(fp, "%d %d", &X1, &X2);
	fclose(fp);

	printf("I read from file %d %d\n", X1, X2);

	//CONTENT :

	treeElement *root;
	
	initialize(root);

	//randomElPutting(root, X1);
	//showTreeHeight(root);

	addNode(root, 30);
	addNode(root, 26);
	addNode(root, 22);
	addNode(root, 28);
	addNode(root, 27);
	addNode(root, 29);


	showPreorder(root);
	showTreeHeight(root);

	rotateLeft(root, findTreeEl(root, 30), findTreeEl(root, 26), findTreeEl(root, 28));
	//treeToList(root);

	showPreorder(root);
	showTreeHeight(root);

	//listToPerfectTree(root,getTreeHeight(root));

	//showPreorder(root);
	//showTreeHeight(root);

	//Wykonaj algorytm DSW:

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

