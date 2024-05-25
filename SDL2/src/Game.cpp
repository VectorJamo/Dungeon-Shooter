#include "Game.h"

Game::Game(int width, int height, const char* title) {
	display = new Display(width, height, title);
	running = true;
}

Game::~Game() {
	delete display;
}

void Game::run() {
	while (running) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {
				running = false;
			}
		}
		// Clear the screen
		display->clear(0, 0, 0, 255);
		
		// Tick
		
		// Draw

		// Swap buffers
		display->show();
	}
}
