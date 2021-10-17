#include <iostream>
#include <Windows.h>
#include "Menu.h"
#include "AdjMatrix.h"
#include "ATSPFileReader.h"

Menu::Menu()
{
	
}

Menu::~Menu()
{

}

void Menu::tests() {
	std::cout << "Test grafu\n\n";

	//AdjMatrix* matrix = new AdjMatrix(5);
	//matrix->addDirectedEdge(0, 0, 10);
	//matrix->addEdge(0, 1, 15);
	AdjMatrix* matrix = nullptr;
	ATSPFileReader* reader = new ATSPFileReader();
	matrix = reader->readFile("br17.atsp");
	matrix->showGraph();

	std::cout << "Wcisnij Enter, aby kontynuowac!";
	//Sleep(1000);
	fflush(stdin);
	std::cin.get();
	std::cin.get();
}

void Menu::readData() {

}

void Menu::showGraph() {

}

void Menu::BruteForce() {

}

void Menu::showMenu() 
{
	char option;
	std::cout << "ASYMETRYCZNY PROBLEM KOMIWOJAZERA\n\n"
			  << "Wprowadz znak operacji do wykonania:\n"
			  << "A lub a. Testy automatyczne\n"
			  << "1. Wczytaj dane z pliku\n"
			  << "2. Wyswietl graf na ekranie\n"
			  << "3. Metoda Brute force\n"
			  << "4. \n"
			  << "5. \n"
			  << "X lub x. Koniec programu\n\n"
			  << "Wpisz znak operacji: ";
	std::cin >> option;
	fflush(stdin);

	switch (option) {
	case 'A':
		system("cls");
		tests();
		break;
	case 'a':
		system("cls");
		tests();
		break;

	case '1':
		system("cls");

		break;
	case '2':
		system("cls");

		break;
	case '3':
		system("cls");

		break;
	case '4':
		system("cls");

		break;
	case '5':
		system("cls");

		break;

	case 'X':
		system("cls");
		std::cout << "Dziekuje za uwage!";
		Sleep(2000);
		system("cls");
		exit(0);
		break;
	case 'x':
		system("cls");
		std::cout << "Dziekuje za uwage!";
		Sleep(2000);
		system("cls");
		exit(0);
		break;
	default:
		system("cls");
		std::cout << "Wprowadzono niepoprawny znak!";
		Sleep(1000);
		break;
	}
}