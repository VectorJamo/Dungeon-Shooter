#pragma once
#include "graphics/Display.h"

class Game {
private:
	Display* display;

public:
	bool running;

public:
	Game(int width, int height, const char* title);
	~Game();

	void run();
};