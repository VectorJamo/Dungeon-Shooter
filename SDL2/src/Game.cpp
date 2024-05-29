#include "Game.h"
#include <iostream>
#include "utils/Macros.h"

bool Game::running;
Game::Game(int width, int height, const char* title) {
	display = new Display(width, height, title);
	running = true;

	gameState = new GameState();
	StateManager::currentState = gameState;
}

Game::~Game() {
	delete gameState;
	delete display;
}

void Game::run() {
	while (running) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				running = false;

			StateManager::currentState->handleInput(ev);
		}

		// Clear the screen
		display->clear(10, 10, 10, 255);
		
		// Tick
		StateManager::currentState->tick();

		// Draw
		StateManager::currentState->render();

		// Swap buffers
		display->show();

		limitFPS();
	}
}
void Game::limitFPS() {
	float deltaTime = SDL_GetTicks() - lastTime;
	if (deltaTime < 1000.0f / FPS) {
		SDL_Delay((1000.0f / FPS) - deltaTime);
	}
	lastTime = SDL_GetTicks();
}
