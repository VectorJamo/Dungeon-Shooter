#include "Entity.h"
#include "../graphics/Display.h"
#include "../utils/Macros.h"

#include <iostream>

Entity::Entity(const char* path, float x, float y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	collideRect = { 0, 0, width, height };

	entityImage = IMG_LoadTexture(Display::getRendererInstance(), path);
	if (!entityImage){
		DEBUG_LOG("Failed to load entity image.");
	}
}

Entity::~Entity() {
	SDL_DestroyTexture(entityImage);
}

void Entity::setXPos(float x){
	this->x = x;
}
void Entity::setYPos(float y) {
	this->y = y;
}
void Entity::setWidth(int width) {
	this->width = width;
}
void Entity::setHeight(int height) {
	this->height = height;
}

void Entity::setCollisionRect(int x, int y, int width, int height) {
	collideRect = { x, y, width, height };
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
const SDL_Rect& Entity::getCollideRect() const {
	return collideRect;
}



