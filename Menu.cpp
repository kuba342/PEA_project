#include "Menu.h"
#include "BruteForce.h"
#include "Combinations.h"

Menu::Menu()
{
	this->graph = nullptr;
	this->brut = nullptr;
	this->held = nullptr;
	this->branch = nullptr;
	this->lib = new Additional();
	this->clock = new Clock();
}

Menu::~Menu()
{

}

void Menu::tests() {
	int v = 0;
	char decision1;
	std::string bufor;

	do {
		system("cls");
		std::cout << "Ile wierzcholkow maja miec instancje? (minimum 3)\n"
				  << "Wprowadz liczbe: ";
		std::cin >> bufor;
		fflush(stdin);
		if (this->lib->isNum(bufor)) {
			int number = std::stoi(bufor);
			if (number > 2) {
				v = number;
			}
			else {
				system("cls");
				std::cout << "Wprowadzono niepoprawne dane!";
				Sleep(2);
			}
		}
		else {
			system("cls");
			std::cout << "Wprowadzono niepoprawne dane!";
			Sleep(2);
		}
	} while (v == 0);

	do {
		system("cls");
		std::cout << "Ktory algorytm problemu komiwojazera przeanalizowac?\n"
				  << "1. Brute Force\n"
				  << "2. Programowanie dynamiczne\n"
				  << "3. Metoda podzialu i ograniczen\n"
				  << "Wprowadz numer algorytmu: ";
		std::cin >> decision1;
		fflush(stdin);
		switch (decision1) {
		case '1':
			generateResults(decision1, v);
			break;
		case '2':
			generateResults(decision1, v);
			break;
		case '3':
			generateResults(decision1, v);
			break;
		default:
			decision1 = ' ';
			system("cls");
			std::cout << "Niepoprawny znak!\n"
					  << "Operacja anulowana!";
			Sleep(2);
			break;
		}
	} while (decision1 == ' ');
}

void Menu::generateResults(char decision, int v) {
	//Liczba prób narzucona przez prowadz¹cego:
	int count = 100;
	//Tabela na rezultaty
	long long* results = new long long[count];

	for (int i = 0; i < count; i++) {
		results[i] = 0;
	}

	GraphGenerator* generator = new GraphGenerator();
	
	system("cls");
	std::cout << "Process: ";

	for (int i = 0; i < count; i++) {
		do {
			this->graph = generator->generate(this->graph, v);
			switch (decision) {
			case '1':
				this->brut = new BruteForce(this->graph);
				this->clock->startTime();
				this->brut->calculate();
				this->clock->endTime();
				results[i] = this->clock->executionTime();
				delete this->brut;
				break;
			case '2':
				this->held = new HeldKarp(this->graph);
				this->clock->startTime();
				this->held->calculate();
				this->clock->endTime();
				results[i] = this->clock->executionTime();
				delete this->held;
				break;
			case '3':
				this->branch = new BranchAndBound(this->graph);
				this->clock->startTime();
				this->branch->calculate();
				this->clock->endTime();
				results[i] = this->clock->executionTime();
				delete this->branch;
				break;
			}
		} while (results[i] == 0);
		if (i % 2 == 0) {
			std::cout << "|";
		}
	}

	system("cls");
	std::cout << "Tablica rezultatow:\n"
		<< "Tab = [";
	for (int i = 0; i < count; i++) {
		std::cout << " " << results[i] << " ";
	}
	std::cout << "]\n\n";
	std::cout << "Srednia: "
		<< this->lib->average(results, count)
		<< "\n\n";
	std::cout << "Wcisnij Enter, aby kontynuowac!";
	std::cin.get();
	std::cin.get();
	fflush(stdin);
}

void Menu::reading() {
	std::string name = "Dane\\";
	std::string bufor;
	std::cout << "Wprowadz nazwe pliku i zatwierdz Enterem: ";
	std::cin >> bufor;
	name += bufor;

	std::ifstream file;
	file.open(name);
	if (file) {
		file.close();
		ATSPFileReader* reader = new ATSPFileReader();
		this->graph = reader->readFile(name);
	}
	else {
		system("cls");
		std::cout << "Nie ma takiego pliku w folderze: Dane\\!";
		Sleep(3000);
		return;
	}
}

void Menu::readData() {
	
	if (this->graph == nullptr) {
		reading();
	}
	else
	{
		char decision;
		std::cout << "Wczytano juz graf!\n"
				  << "Czy chesz nadpisac obecny?\n"
				  << "Wprowadz znak T lub N: ";
		std::cin >> decision;

		switch (decision) {
		case 't':
			system("cls");
			reading();
			break;
		case 'T':
			system("cls");
			reading();
			break;
		case 'n':
			return;
			break;
		case 'N':
			return;
			break;
		
		default:
			system("cls");
			std::cout << "Wprowadzono niepoprawny znak!\n"
				<< "Operacja anulowana!";
			Sleep(3000);
			break;
		}
	}
}

void Menu::showGraph() {
	if (this->graph != nullptr) {
		this->graph->showGraph();
		std::cout << "\nWcisnij Enter, aby kontynuowac!";
		std::cin.get();
		std::cin.get();
	}
	else {
		std::cout << "Nie wczytano grafu!";
		Sleep(2000);
	}
}

void Menu::heldKarp() {
	/*Combinations* comb = new Combinations(6, 4);
	comb->print();
	std::cin.get();
	std::cin.get();*/
	if (this->graph != nullptr) {
		system("cls");

		this->held = new HeldKarp(this->graph);

		this->held->calculate();

		std::cout << "Najkrotsza sciezka:\n";
		this->held->showShortestCycle();
		std::cout << "Wcisnij Enter, aby kontynuowac!";
		std::cin.get();
		std::cin.get();
		delete this->held;
	}
	else {
		system("cls");
		std::cout << "Nie wczytano grafu!\n"
			<< "Operacja anulowana!";
		Sleep(3000);
	}
}

void Menu::bruteForce() {
	if (this->graph != nullptr) {
		system("cls");
		this->brut = new BruteForce(this->graph);
		
		this->brut->calculate();
		
		std::cout << "Najkrotsza sciezka:\n";
		this->brut->showShortestCycle();
		std::cout << "Wcisnij Enter, aby kontynuowac!";
		std::cin.get();
		std::cin.get();
		delete this->brut;
	}
	else {
		system("cls");
		std::cout << "Nie wczytano grafu!\n"
				  << "Operacja anulowana!";
		Sleep(3000);
	}
}

void Menu::generator() {
	if (this->graph == nullptr) {
		GraphGenerator* generator = new GraphGenerator();
		this->graph = generator->generate(this->graph);
	}
	else {
		char decision;
		std::cout << "Wczytano juz graf!\n"
				  << "Czy chcesz nadpisac obecny?\n"
				  << "Wpisz T lub N: ";
		std::cin >> decision;
		GraphGenerator* generator = new GraphGenerator();
		switch (decision) {
		case 't':
			system("cls");
			this->graph = generator->generate(this->graph);
			break;
		case 'T':
			system("cls");
			this->graph = generator->generate(this->graph);
			break;

		case 'n':
			return;
			break;
		case 'N':
			return;
			break;
		default:
			system("cls");
			std::cout << "Wprowadzono niepoprawny znak!\n"
					  << "Operacja anulowana!";
			Sleep(3000);
			break;
		}
	}
}

void Menu::BnB()
{
	if (this->graph != nullptr) {
		system("cls");
		this->branch = new BranchAndBound(this->graph);

		this->branch->calculate();

		std::cout << "Najkrotsza sciezka:\n";
		this->branch->getSolution()->getCycle()->showList();
		std::cout << "\nCost: " << this->branch->getSolution()->getCost() << "\n";
		std::cout << "Wcisnij Enter, aby kontynuowac!";
		std::cin.get();
		std::cin.get();
		delete this->branch;
	}
	else {
		system("cls");
		std::cout << "Nie wczytano grafu!\n"
			<< "Operacja anulowana!";
		Sleep(3000);
	}
}

void Menu::showMenu() 
{
	char option;
	std::cout << "ASYMETRYCZNY PROBLEM KOMIWOJAZERA\n\n"
			  << "Wprowadz znak operacji do wykonania:\n"
			  << "A lub a. Testy automatyczne\n"
			  << "1. Wczytaj dane z pliku\n"
			  << "2. Wyswietl graf na ekranie\n"
			  << "3. Wygeneruj graf losowo\n"
			  << "4. Metoda Brute force\n"
			  << "5. Programowanie dynamiczne (algorytm Helda-Karpa)\n"
			  << "6. Metoda podzialu i ograniczen\n"
			  << "X lub x. Koniec programu\n\n"
			  << "Wpisz znak operacji: ";
	std::cin >> option;
	fflush(stdin);

	switch (option) {
	case 'A':
		system("cls");
		tests();
		system("cls");
		break;
	case 'a':
		system("cls");
		tests();
		system("cls");
		break;

	case '1':
		system("cls");
		readData();
		system("cls");
		break;
	case '2':
		system("cls");
		showGraph();
		system("cls");
		break;
	case '3':
		system("cls");
		generator();
		system("cls");
		break;
	case '4':
		system("cls");
		bruteForce();
		system("cls");
		break;
	case '5':
		system("cls");
		heldKarp();
		system("cls");
		break;
	case '6':
		system("cls");
		BnB();
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