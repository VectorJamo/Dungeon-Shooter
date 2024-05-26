#pragma once
#include <SDL_image.h>

class Entity {
protected:
	int x, y, width, height;
	SDL_Texture* entityImage;

public:
	Entity(const char* path, int x, int y, int width, int height);
	~Entity();

	virtual void tick() = 0;
	virtual void render() = 0;

	void setXPos(int x);
	void setYPos(int y);
	void setWidth(int width);
	void setHeight(int height);
	
	int getXPos() const;
	int getYPos() const;
	int getWidth() const;
	int getHeight() const;
};