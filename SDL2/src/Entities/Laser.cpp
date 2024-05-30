#include "Laser.h"
#include "../graphics/Display.h"

#include <iostream>

Laser::Laser(const char* path, const char* path2, float x, float y, int width, int height, Tilemap* map): Entity(path, x, y, width, height) {
	entityImage2 = IMG_LoadTexture(Display::getRendererInstance(), path2); // 1 = vertical laser, 2 = horizontal laser
	lazerSpeed = 10;

	lazerTimer = 0;
	canShoot = true;
}

Laser::~Laser(){
	for (auto& lazer : lazers)
		delete lazer;
}

void Laser::tick(){
}

void Laser::render(){
}

void Laser::tick(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, char direction) {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (!canShoot) {
		lazerTimer++;
		if (lazerTimer > 30) { // Approx. 0.5 second
			canShoot = true;
			lazerTimer = 0;
		}
	}
	if (keyState[SDL_SCANCODE_SPACE]) {
		if (canShoot) {
			std::cout << "Added a laser" << std::endl;
		
			ActiveLazer* lazer = new ActiveLazer();
			lazer->lazerWorldX = playerWorldX + playerWidth/2 - width/2;
			lazer->lazerWorldY = playerWorldY + playerHeight/2 - height/2;
			lazer->lazerDirection = direction; 

			lazers.push_back(lazer);
			canShoot = false;
		}
	}

	for (auto& lazer : lazers) {
		if (lazer->lazerDirection == 'U') {
			lazer->lazerWorldY -= lazerSpeed;
		}
		if (lazer->lazerDirection == 'D') {
			lazer->lazerWorldY += lazerSpeed;
		}
		if (lazer->lazerDirection == 'L') {
			lazer->lazerWorldX -= lazerSpeed;
		}
		if (lazer->lazerDirection == 'R') {
			lazer->lazerWorldX += lazerSpeed;
		}
		if (lazer->lazerDirection == 'X') {
			lazer->lazerWorldY += lazerSpeed;
		}
	}
}

void Laser::render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, char direction){

	for (auto& lazer : lazers) {
		int lazerWorldX = lazer->lazerWorldX;
		int lazerWorldY = lazer->lazerWorldY;
		int lazerScreenX = lazerWorldX - ((playerWorldX + playerWidth / 2) - Display::getScreenWidth() / 2);
		int lazerScreenY = lazerWorldY - ((playerWorldY + playerHeight / 2) - Display::getScreenHeight() / 2);

		SDL_Rect dest = { lazerScreenX, lazerScreenY, width, height };
		if(lazer->lazerDirection == 'U' || lazer->lazerDirection == 'D' || lazer->lazerDirection == 'X')
			SDL_RenderCopy(Display::getRendererInstance(), entityImage, NULL, &dest);
		else
			SDL_RenderCopy(Display::getRendererInstance(), entityImage2, NULL, &dest);
	}
}
