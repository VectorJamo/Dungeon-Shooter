#include "Entity.h"
#include "../graphics/Display.h"
#include "../utils/Macros.h"

#include <iostream>

Entity::Entity(const char* path, int x, int y, int width, int height) {
	entityImage = IMG_LoadTexture(Display::getRendererInstance(), path);
	if (!entityImage){
		DEBUG_LOG("Failed to load entity image.");
	}
}

Entity::~Entity() {
	SDL_DestroyTexture(entityImage);
}

void Entity::setXPos(int x){
	this->x = x;
}
void Entity::setYPos(int y) {
	this->y = y;
}
void Entity::setWidth(int width) {
	this->width = width;
}
void Entity::setHeight(int height) {
	this->height = height;
}

int Entity::getXPos() const {
	return x;
}
int Entity::getYPos() const {
	return y;
}
int Entity::getWidth() const {
	return width;
}
int Entity::getHeight() const {
	return height;
}



