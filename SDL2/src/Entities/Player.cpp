#include "Player.h"

#include "../graphics/Display.h"
#include "../Game.h"

#include "CollisionChecker.h"
#include <iostream>

void Player::playAnimation()
{
}

Player::Player(const char* path, float x, float y, int width, int height, Tilemap* map): Entity(path, x, y, width, height) {
	this->map = map;

	leftClipRects = new SDL_Rect[4];
	rightClipRects = new SDL_Rect[4];
	upClipRects = new SDL_Rect[4];
	downClipRects = new SDL_Rect[4];

	downClipRects[0] = { 0, 0, 32, 32 };
	downClipRects[1] = { 32, 0, 32, 32 };
	downClipRects[2] = { 32*2, 0, 32, 32 };
	downClipRects[3] = { 32*3, 0, 32, 32 };

	rightClipRects[0] = { 0, 32*2, 32, 32 };
	rightClipRects[1] = { 32, 32*2, 32, 32 };
	rightClipRects[2] = { 32 * 2, 32*2, 32, 32 };
	rightClipRects[3] = { 32 * 3, 32*2, 32, 32 };

	upClipRects[0] = { 0, 32*4, 32, 32 };
	upClipRects[1] = { 32, 32*4, 32, 32 };
	upClipRects[2] = { 32 * 2, 32*4, 32, 32 };
	upClipRects[3] = { 32 * 3, 32*4, 32, 32 };

	leftClipRects[0] = { 0, 32*6, 32, 32 };
	leftClipRects[1] = { 32, 32*6, 32, 32 };
	leftClipRects[2] = { 32 * 2, 32*6, 32, 32 };
	leftClipRects[3] = { 32 * 3, 32*6, 32, 32 };

	currentClipRect = downClipRects[0];

	dx = 0.0f;
	dy = 0.0f;
	speed = 5.0f;
}

Player::~Player() {
}

void Player::setCurrentClipRect() {
}


void Player::tick() {

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_W]) {
		dy = -speed;
	}
	if (keyState[SDL_SCANCODE_S]) {
		dy = speed;
	}
	if (keyState[SDL_SCANCODE_A]) {
		dx = -speed;
	}
	if (keyState[SDL_SCANCODE_D]) {
		dx = speed;
	}

	CollisionAxes axes = checkCollision(this, map, dx, dy);
	if (axes.xCollision) {
		dx = 0;
		std::cout << "X-Collision" << std::endl;
	}
	if (axes.yCollision) {
		dy = 0;
		std::cout << "Y-Collision" << std::endl;
	}

	x += dx;
	y += dy;
}

void Player::render() {
	SDL_Rect dest = { x, y, width, height };
	SDL_SetRenderDrawColor(Display::getRendererInstance(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Display::getRendererInstance(), &dest);
	SDL_RenderCopy(Display::getRendererInstance(), entityImage, &currentClipRect, &dest);

	dx = 0;
	dy = 0;
}

