// Binary tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>       /* time */
#include <iostream>

using namespace std;

struct treeElement {
	int key;
	treeElement *left;
	treeElement *right;
	char word[100];
};

void randomWord(char *word) {

	for (int i = 0; i < 100; i++)
	{
		word[i] = rand() % 26 + 'a';
	}

	word[100] = NULL;
}

void initialize(treeElement *&root) {
	root = new treeElement;
	root->key = NULL;
}

void addNode(treeElement *&root,int givenKey) {
	if (root->key == NULL)
	{
		root->key = givenKey;
		root->left = NULL;
		root->right = NULL;
		randomWord(root->word);
	}
	cout << "Root >> Key: " << root->key << " Left: " << root->left << " Right: " << root->right << "\nWord: " << root->word << endl;
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

	addNode(root,10);

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

