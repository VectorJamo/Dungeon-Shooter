#include "AnotherPlayer.h"
#include "../graphics/Display.h"
#include "../utils/Macros.h"

#include <iostream>

AnotherPlayer::AnotherPlayer(const char* path, float x, float y, int width, int height): Entity(path, x, y, width, height){
	leftClipRects = new SDL_Rect[4];
	rightClipRects = new SDL_Rect[4];
	upClipRects = new SDL_Rect[4];
	downClipRects = new SDL_Rect[4];

	downClipRects[0] = { 0, 0, 32, 32 };
	downClipRects[1] = { 32, 0, 32, 32 };
	downClipRects[2] = { 32 * 2, 0, 32, 32 };
	downClipRects[3] = { 32 * 3, 0, 32, 32 };

	rightClipRects[0] = { 0, 32 * 2, 32, 32 };
	rightClipRects[1] = { 32, 32 * 2, 32, 32 };
	rightClipRects[2] = { 32 * 2, 32 * 2, 32, 32 };
	rightClipRects[3] = { 32 * 3, 32 * 2, 32, 32 };

	upClipRects[0] = { 0, 32 * 4, 32, 32 };
	upClipRects[1] = { 32, 32 * 4, 32, 32 };
	upClipRects[2] = { 32 * 2, 32 * 4, 32, 32 };
	upClipRects[3] = { 32 * 3, 32 * 4, 32, 32 };

	leftClipRects[0] = { 0, 32 * 6, 32, 32 };
	leftClipRects[1] = { 32, 32 * 6, 32, 32 };
	leftClipRects[2] = { 32 * 2, 32 * 6, 32, 32 };
	leftClipRects[3] = { 32 * 3, 32 * 6, 32, 32 };

	currentClipRect = downClipRects[0];

	health = 100;
	animationCounter = 0.0f;
}

AnotherPlayer::~AnotherPlayer() {

}

void AnotherPlayer::setDirection(char direction) {
	this->direction = direction;
}

void AnotherPlayer::setHealth(int health){
	this->health = health;
}



void AnotherPlayer::tick() {
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
void AnotherPlayer::render() {

}
void AnotherPlayer::render(int playerWorldX, int playerWorldY) {
	int anotherPlayerWorldX = x;
	int anotherPlayerWorldY = y;
	int anotherPlayerScreenX = anotherPlayerWorldX - ((playerWorldX + 64 / 2) - Display::getScreenWidth() / 2);
	int anotherPlayerScreenY = anotherPlayerWorldY - ((playerWorldY + 64 / 2) - Display::getScreenHeight() / 2);

	SDL_Rect destRect = { anotherPlayerScreenX, anotherPlayerScreenY, 64, 64 };
	SDL_RenderCopy(Display::getRendererInstance(), entityImage, &currentClipRect, &destRect);

	SDL_Rect healthRect = { 20, 60, health, 30 };
	SDL_Rect outlineRect = { 18, 58, 104, 34 };
	SDL_SetRenderDrawColor(Display::getRendererInstance(), 0, 0, 255, 255);
	SDL_RenderFillRect(Display::getRendererInstance(), &healthRect);
	SDL_SetRenderDrawColor(Display::getRendererInstance(), 255, 255, 255, 255);
	SDL_RenderDrawRect(Display::getRendererInstance(), &outlineRect);
}