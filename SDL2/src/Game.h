#pragma once
#include "graphics/Display.h"
#include "GameState.h"
#include "networking/Server.h"
#include "networking/Client.h"
#include <thread>

class Game {
private:
	Display* display;
	GameState* gameState;

	static const unsigned int FPS = 60;
	float lastTime = 0.0f;

	std::thread* networkingThread;
	static bool isClient, isServer;

public:
	static bool running;

public:
	Game(int width, int height, const char* title);
	~Game();

	void run();
	void limitFPS();
};