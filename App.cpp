#include <iostream>
#include <Windows.h>
#include "App.h"
#include "Menu.h"

App::App()
{
	this->menu = new Menu();
}

App::~App()
{
	delete this->menu;
}

void App::mainLoop() 
{
	system("cls");
	std::cout << "Projekt z Projektowania efektywnych algorytmow - zadanie nr 1\n\n"
			  << "Autor:		Jakub Derda\n"
			  << "nr indeksu:	252819\n"
			  << "Grupa:		K03-59d\n";
	Sleep(3000);
	while (1) 
	{
		system("cls");
		this->menu->showMenu();
	}
}