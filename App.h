#pragma once
#ifndef App_h
#define App_h

#include "Menu.h"

class App
{
public:
	App();
	~App();
	void mainLoop();

private:
	Menu* menu;
};

#endif // !App_h