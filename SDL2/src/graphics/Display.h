#pragma once

#include <SDL.h>

class Display {
private:
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static int width, height;

public:
	Display(int width, int height, const char* title);
	~Display();

	void clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void tick();
	void show();

	inline static SDL_Window* getWindowInstance() { return window; }
	inline static SDL_Renderer* getRendererInstance() { return renderer; }
	inline static int getScreenWidth() { return width; };
	inline static int getScreenHeight() { return height; }
};

