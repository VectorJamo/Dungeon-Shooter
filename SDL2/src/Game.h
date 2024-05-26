#pragma once
#include "graphics/Display.h"
#include "GameState.h"

class Game {
private:
	Display* display;
	GameState* gameState;

	static const unsigned int FPS = 60;
	float lastTime = 0.0f;
public:
	bool running;

public:
	Game(int width, int height, const char* title);
	~Game();

	void run();
	void limitFPS();
};