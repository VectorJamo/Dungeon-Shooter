#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Texture {
private:
	SDL_Texture* texture;

public:
	Texture();
	~Texture();

	virtual void draw();

};

