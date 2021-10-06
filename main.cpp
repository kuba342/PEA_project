#include <iostream>
#include "App.h"

int main(void) {
	App* app = new App();
	app->mainLoop();
	std::cout << "Hello world!";
	return 0;
}