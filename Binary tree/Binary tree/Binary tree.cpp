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
	showPreorderRec(root);
	cout << "\nPreorder occurrences >> " << preorderCounter << endl;
}

void showInorder(treeElement *&root)
{
	inorderCounter = 0;
	showInorderRec(root);
	cout << "\nInorder occurrences >> " << inorderCounter << endl;
}

void showPostorder(treeElement *&root)
{

	postorderCounter = 0;
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
	while ((givenKey != actual->key)&&(actual != NULL))
	{
		parent = actual;
		if (givenKey > actual->key) actual = actual->right;
		else actual = actual->left;
	}

	//There isn't given key - return
	if (actual == NULL) 
	{
		cout << "\nDeleted element does'nt exist!" << endl;
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
		root->left = actual->left;
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

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	//Time start:
	clock_t begin, end;
	double time_spent;
	begin = clock();

	//File read:
	int X, k1, k2, k3, k4;
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, "inputData.txt", "r");
	if (err != 0)
		return -1;
	fscanf_s(fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
	fclose(fp);

	printf("I read from file %d %d %d %d %d\n\n", X, k1, k2, k3, k4);

	//CONTENT :

	treeElement *root;
	
	initialize(root);

	addNode(root, 1);

	addNode(root, 12);
	addNode(root, 3);

	
	addNode(root, 14);
	addNode(root, 5);
	addNode(root, 16);

	randomElPutting(root, 500);

	showPreorder(root);
	showInorder(root);
	showPostorder(root);

	findTreeEl(root, 14);
	findTreeEl(root, 1);
	findTreeEl(root, 1);
	

	deleteEl(root, 1);

	showPreorder(root);


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

