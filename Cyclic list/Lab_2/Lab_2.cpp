// Lab_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "time.h"
#include <time.h>       /* time */
#include <cstdlib>
#include <iostream>

using namespace std;

struct listElement {
	int key;
	double number;
	char sign;
	listElement *next;
};

listElement *tail;

void initialize(listElement *&head) {
	head = new listElement;
	head->key = NULL;
	head->number = NULL;
	head->sign = NULL;
	head->next = head;
	tail = head;
}

void add(listElement *&head,int givenKey) 
{
	listElement *actual = head, *prev = tail,*temp;
	do
	{
		if (actual->key == givenKey)
		{
			cout << "Element with given key already exist!\n";
			return;
		}
		
		//Case when we haven't any element on the list :
		if (head->key == NULL)
		{
			head->key = givenKey;
			head->number = rand() % 500;
			head->sign = 'Z';

			break;
		}
		else if (givenKey < head->key)
		{
			temp = head;

			head = new listElement;

			head->key = givenKey;
			head->number = rand() % 500;
			head->sign = 'Z';
			head->next = temp;

			tail->next = head;

			break;
		}
		else if (givenKey < actual->key)
		{
			temp = new listElement;

			temp->key = givenKey;
			temp->number = rand() % 500;
			temp->sign = 'Z';

			prev->next = temp;
			temp->next = actual;

			break;
		}
		else if ((actual->next == head) && (givenKey > actual->key))
		{
			temp = new listElement;

			temp->key = givenKey;
			temp->number = rand() % 500;
			temp->sign = 'Z';

			actual->next = temp;
			temp->next = head;

			tail = temp;

			break;
		}

		prev = actual;
		actual = actual->next;

	} while (actual != head);

}

void insertElements(listElement *&head, int X) {
	for (int i = 0; i < X; i++)
	{
		add(head, (rand() % 19990 + 10));
	}
}

// Wyœwietla Y pierwszych elementów :
void show(listElement *&head, int Y) {

	//sprawdzenie czy element znajduje siê na liscie:

	listElement *actual = head;
	for (int i = 0; i < Y; i++)
	{
		cout << "Key: " << actual->key << " Number: " << actual->number << " Sign:" << actual->sign << endl;
		actual = actual->next;

		//Jeœli nie chcemy przekraczaæ wyœwietlanych elementow (if Y > od iloœci struktór wyœwietl tylko wszystkie) :
		if (actual == head) break;
	}
}

void deleteList(listElement *&head)
{
	listElement *actual = head;
	listElement *temp = actual->next;

	do
	{
		temp = actual->next;
		delete actual;
		actual = temp;

	} while (actual != head);


}

void find(listElement *&head, int key)
{
	listElement *actual = head;
	do
	{
		if (key == actual->key)
		{
			cout << "\nFounded >> Key: " << actual->key << " Number: " << actual->number << " Sign:" << actual->sign << endl;
			return;
		}
		actual = actual->next;

	} while (actual != head);

	cout << "\nNot founded element with key = " << key << endl;
}

void deleteElement(listElement *&head, int givenKey)
{
	listElement *actual = head, *temp, *prev = tail;

	do
	{
		if (givenKey == head->key)
		{
			temp = head;
			delete head;
			head = temp->next;

			tail->next = head;

			cout << "\nDeleted (head) >> Key: " << actual->key << " Number: " << actual->number << " Sign:" << actual->sign << endl;
			return;
		}
		else if (givenKey == actual->key)
		{
			if (actual == tail) tail = prev;

			prev->next = actual->next;
			delete actual;

			cout << "\nDeleted >> Key: " << actual->key << " Number: " << actual->number << " Sign:" << actual->sign << endl;
			return;
		}

		prev = actual;
		actual = actual->next;

	} while (actual != head);

	cout << "\nNot founded element with key = " << givenKey << endl;

}

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	//Zegar start:
	clock_t begin, end;
	double time_spent;
	begin = clock();

	//File read:
	int X, k1, k2, k3, k4, k5;
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp,"inputData.txt", "r");
	if (err != 0)
		return -1;
	fscanf_s(fp, "%d %d %d %d %d %d", &X, &k1, &k2, &k3, &k4, &k5);
	fclose(fp);

	printf("I read from file %d %d %d %d %d %d\n\n", X, k1, k2, k3, k4, k5);

	//CONTENT :

	listElement *list;

	initialize(list);

	add(list, k1);

	insertElements(list,X);

	show(list, 20);
	cout << endl;

	add(list, k2);
	show(list, 20);
	cout << endl;

	add(list, k3);
	show(list, 20);
	cout << endl;

	add(list, k4);
	show(list, 20);
	cout << endl;

	add(list, k5);

	deleteElement(list, k3);
	show(list, 20);
	cout << endl;

	deleteElement(list, k2);
	show(list, 20);
	cout << endl;

	deleteElement(list, k5);

	find(list, k5);

	deleteList(list);

	//Zegar stop:
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	// Wyœwietl czas na ekranie: 
	printf("\nTime of process : %f\n", time_spent);

	//Czekaj na enter:
	cin.sync();
	cin.get();

    return 0;
}

