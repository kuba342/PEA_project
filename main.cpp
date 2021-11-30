#include <iostream>
#include "App.h"

int main(void) {
	App* app = new App();
	app->mainLoop();
	return 0;
}