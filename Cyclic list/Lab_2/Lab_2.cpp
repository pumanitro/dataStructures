// Lab_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "time.h"
#include <time.h>       /* time */
#include <cstdlib>
#include <iostream>

using namespace std;

struct elementListy {
	int key;
	double number;
	char sign;
	elementListy *next;
};

elementListy *tail;

void initialize(elementListy *&head) {
	head = new elementListy;
	head->key = NULL;
	head->number = NULL;
	head->sign = NULL;
	head->next = head;
	tail = head;
}

void add(elementListy *&head,int givenKey) 
{
	//sprawdzenie czy element znajduje siê na liscie:
	elementListy *actual = head;
	do
	{
		if (actual->key == givenKey)
		{
			cout << "Element with given key already exist!\n";
			return;
		}
		actual = actual->next; 

	} while (actual != head);

	//przypisanie wartoœci nowemu elementowi listy:
	elementListy *newOne;
	if (head->key == NULL) {
		newOne = head;
	}
	else 
		newOne = new elementListy;

	tail->next = newOne;

	newOne->key = givenKey;
	newOne->number = rand() % 500;
	newOne->sign = 'Z';
	newOne->next = head;
	 
	tail = newOne;
}

void insertElements(elementListy *&head, int X) {
	for (int i = 0; i < X; i++)
	{
		add(head, (rand() % 20000 + 10));
	}
}

// Wyœwietla Y pierwszych elementów :
void show(elementListy *&head, int Y) {

	//sprawdzenie czy element znajduje siê na liscie:

	elementListy *actual = head;
	for (int i = 0; i < Y; i++)
	{
		cout << "Key: " << actual->key << " Number: " << actual->number << " Sign:" << actual->sign << endl;
		actual = actual->next;

		//Jeœli nie chcemy przekraczaæ wyœwietlanych elementow (if Y > od iloœci struktór wyœwietl tylko wszystkie) :
		if (actual == head) break;
	}
}

void deleteList(elementListy *&head)
{
	elementListy *actual = head;
	elementListy *temp = actual->next;

	do
	{
		/*
		cout << "\n\n" << actual << endl;
		cout << " " << temp << endl;
		*/

		temp = actual->next;
		delete actual;
		actual = temp;

	} while (actual != head);

}

void find(elementListy *&head, int key)
{
	elementListy *actual = head;
	do
	{
		/*
		cout << "\n\n" << actual << endl;
		cout << " " << temp << endl;
		*/
		if (key == actual->key)
		{
			cout << "\nFounded >> Key: " << actual->key << " Number: " << actual->number << " Sign:" << actual->sign << endl;
			return;
		}
		actual = actual->next;

	} while (actual != head);

	cout << "\nNot founded element with key = " << key << endl;
}

void deleteElement(elementListy *&head, int key)
{
	elementListy *actual = head;
	elementListy *prev = actual;
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

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	//Zegar start:
	clock_t begin, end;
	double time_spent;
	begin = clock();

	//CONTENT :

	elementListy *list;

	initialize(list);

	add(list, 2);
	add(list, 3);
	add(list, 1);

	insertElements(list,10);

	show(list, 15);

	find(list, 5);

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

