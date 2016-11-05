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
	char word[100];
};

void initialize(treeElement *&root) {
	root = new treeElement;
	root->key = NULL;
}

void addNode(treeElement *&root,int givenKey) {
	treeElement	*temp;
	temp = new treeElement;

	temp->key = givenKey;
	temp->left = NULL;
	temp->right = NULL;

	for (int i = 0; i < 100; i++)
	{
		temp->word[i] = rand() % 26 + 'a';
	}

	temp->word[100] = NULL;

	//cout << "Temp >> Key: " << temp->key << " Left: " << temp->left << " Right: " << temp->right << "\nWord: " << temp->word << endl;

	if (root->key == NULL)
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
	cout << "Root >> Key: " << root->key << " Left: " << root->left << " Right: " << root->right << "\nWord: " << root->word << endl;

}

int preorderCounter = 0;

void showPreorder(treeElement *&root)
{
	if (root)
	{
		cout << root->key << " - ";

		//cout << "\nShowed >> Key: " << root->key << " Left: " << root->left << " Right: " << root->right << "\nWord: " << root->word << endl;
		showPreorder(root->left);
		showPreorder(root->right);
	}
}

void randomElPutting(treeElement *&root, int X)
{

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

	cout << "\nActual >> Key: " << actual->key << " Left: " << actual->left << " Right: " << actual->right << "\nWord: " << actual->word << endl;
	return(actual);

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

	addNode(root, 10);
	addNode(root, 12);
	addNode(root, 3);
	addNode(root, 14);
	addNode(root, 5);
	addNode(root, 16);

	showPreorder(root);

	findTreeEl(root, 14);

	//cout << "KEY: " << findTreeEl(root, 14)->key << " LEFT: " << findTreeEl(root, 14)->left << " RIGHT: " << findTreeEl(root, 14)->key << "\nWORD: " << findTreeEl(root, 14)->word << endl;

	//findTreeEl(root, 5);

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

