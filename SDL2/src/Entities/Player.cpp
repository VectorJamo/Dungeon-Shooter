#include "Player.h"

#include "../graphics/Display.h"
#include "../Game.h"

#include "CollisionChecker.h"
#include <iostream>

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
	health = 100;

	SDL_SetTextureAlphaMod(entityImage, 220);
}

Player::~Player() {
	delete[] leftClipRects;
	delete[] rightClipRects;
	delete[] upClipRects;
	delete[] downClipRects;
}

void Player::setCurrentClipRect(SDL_Rect rect) {
	currentClipRect = rect;
}


void Player::tick() {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	direction = 'X';
	if (keyState[SDL_SCANCODE_W]) {
		dy = -speed;
		direction = 'U';
	}
	if (keyState[SDL_SCANCODE_S]) {
		dy = speed;
		direction = 'D';
	}
	if (keyState[SDL_SCANCODE_A]) {
		dx = -speed;
		direction = 'L';
	}
	if (keyState[SDL_SCANCODE_D]) {
		dx = speed;
		direction = 'R';
	}

	CollisionAxes axes = checkCollision(this, map, dx, dy);
	if (axes.xCollision) {
		dx = 0;
		
	}
	if (axes.yCollision) {
		dy = 0;
	}

	x += dx;
	y += dy;
	playAnimation();

}

void Player::render() {
	SDL_Rect dest = { Display::getScreenWidth()/2 - (int)width/2, Display::getScreenHeight()/2 - (int)height/2, width, height};
	SDL_RenderCopy(Display::getRendererInstance(), entityImage, &currentClipRect, &dest);

	SDL_Rect healthRect = { 20, 20, health, 30 };
	SDL_Rect outlineRect = { 18, 18, 104, 34 };

	SDL_SetRenderDrawColor(Display::getRendererInstance(), 255, 0, 0, 255);
	SDL_RenderFillRect(Display::getRendererInstance(), &healthRect);
	SDL_SetRenderDrawColor(Display::getRendererInstance(), 255, 255, 255, 255);
	SDL_RenderDrawRect(Display::getRendererInstance(), &outlineRect);

	dx = 0;
	dy = 0;
}

void Player::playAnimation() {
	if (direction == 'D') {
		animationCounter += 0.2f;
		if (animationCounter >= 4.0f) {
			animationCounter = 0;
			return;
		}
		currentClipRect = downClipRects[(int)animationCounter];
	}
	if (direction == 'U') {
		animationCounter += 0.2f;
		if (animationCounter >= 4.0f) {
			animationCounter = 0;
			return;
		}
		currentClipRect = upClipRects[(int)animationCounter];
	}if (direction == 'L') {
		animationCounter += 0.2f;
		if (animationCounter >= 4.0f) {
			animationCounter = 0;
			return;
		}
		currentClipRect = leftClipRects[(int)animationCounter];
	}if (direction == 'R') {
		animationCounter += 0.2f;
		if (animationCounter >= 4.0f) {
			animationCounter = 0;
			return;
		}
		currentClipRect = rightClipRects[(int)animationCounter];
	}
	if (direction == 'X') {
		currentClipRect = downClipRects[0];
	}
}

