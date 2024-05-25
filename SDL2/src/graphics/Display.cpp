#include "Display.h"
#include "../utils/Macros.h"

#include <iostream>

SDL_Window* Display::window;
SDL_Renderer* Display::renderer;
int Display::width;
int Display::height;

Display::Display(int width, int height, const char* title) {
	this->width = width;
	this->height = height;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window) {
		DEBUG_LOG("Failed to initialize SDL Window");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		DEBUG_LOG("Failed to initialize SDL Renderer");
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Display::~Display() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Display::clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

void Display::show() {
	SDL_RenderPresent(renderer);
}