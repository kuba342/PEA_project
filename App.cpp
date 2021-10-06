#include <iostream>
#include "App.h"

App::App(){

}

App::~App(){

}

void App::mainLoop() {
	std::cout << "Chyba dziala!\n";
	for (int i = 0; i < 10; i++) {
		printf("Numer %d\n", i);
	}
}