#include <iostream>
#include <Windows.h>
#include "Menu.h"

Menu::Menu()
{
	
}

Menu::~Menu()
{

}

void Menu::showMenu() 
{
	char option;
	std::cout << "Ktory problem ma zostac przeanalizowany?\n"
			  << "1. Asymetryczny problem komiwojazera.\n"
			  << "X lub x. Koniec programu\n\n"
			  << "Wpisz znak operacji: ";
	std::cin >> option;
	fflush(stdin);

	switch (option) {
	case '1':
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