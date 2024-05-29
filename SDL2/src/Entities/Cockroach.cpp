#include "Cockroach.h"

#include "CollisionChecker.h"
#include "../graphics//Display.h"

#include <cstdlib>
#include <iostream>

Cockroach::Cockroach(const char* path, float x, float y, int width, int height, Tilemap* map, char direction): Entity(path, x, y, width, height) {
	this->map = map;
	srand(time(NULL));

	roachLeft = { 0, 32*3, 32, 32 };
	roachRight = { 0, 0, 32, 32 };
	roachUp = { 0, 32, 32, 32 };
	roachDown = { 0, 32 * 2, 32, 32 };

	currentClipRect = roachDown;

	dx = 0.0f;
	dy = 0.0f;
	speed = 2.0f;
	directionCounter = 0;
	this->direction = direction;
}

Cockroach::~Cockroach() {

}

void Cockroach::tick() {

	if (direction == 'D') {
		dy = speed;
		currentClipRect = roachDown;
	}
	else if (direction == 'U') {
		dy = -speed;
		currentClipRect = roachUp;
	}
	else if (direction == 'L') {
		dx = -speed;
		currentClipRect = roachLeft;
	}
	else if (direction == 'R') {
		dx = speed;
		currentClipRect = roachRight;
	}

	CollisionAxes axes = checkCollision(this, map, dx, dy);
	if (axes.xCollision) {
		dx = 0;

		int index = rand() % 4;
		direction = directions[index];
	}
	if (axes.yCollision) {
		dy = 0;

		int index = rand() % 4;
		direction = directions[index];
	}

	directionCounter++;
	if (directionCounter > 120) { // Approx. 2 seconds
		directionCounter = 0;

		int index = rand() % 4;
		direction = directions[index];
	}

	x += dx;
	y += dy;
}

void Cockroach::render() {
}

void Cockroach::render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight) {

	int roachWorldX = x;
	int roachWorldY = y;
	int roachScreenX = roachWorldX - ((playerWorldX + playerWidth / 2) - Display::getScreenWidth() / 2);
	int roachScreenY = roachWorldY - ((playerWorldY + playerHeight / 2) - Display::getScreenHeight() / 2);

	SDL_Rect dest = { roachScreenX, roachScreenY, width, height };
	SDL_RenderCopy(Display::getRendererInstance(), entityImage, &currentClipRect, &dest);

	dx = 0;
	dy = 0;
}
