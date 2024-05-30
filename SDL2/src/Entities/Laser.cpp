#include "Laser.h"
#include "../graphics/Display.h"

#include <iostream>
#include "../entities/CollisionChecker.h"

SDL_Texture* LaserAnimation::animationSprite;

Laser::Laser(const char* path, const char* path2, float x, float y, int width, int height, Tilemap* map): Entity(path, x, y, width, height) {
	this->map = map;
	entityImage2 = IMG_LoadTexture(Display::getRendererInstance(), path2); // 1 = vertical laser, 2 = horizontal laser
	lazerSpeed = 10;

	lazerTimer = 0;
	canShoot = true;

	animationClipRects = new SDL_Rect[12];
	for (int i = 0; i < 12; i++) {
		animationClipRects[i] = { i * 96, 0, 96, 96 };
	}

	LaserAnimation::animationSprite = IMG_LoadTexture(Display::getRendererInstance(), "res/images/explosion.png");
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

	std::vector<int> indexsToDelete;
	for (int i = 0; i < lazers.size(); i++) {
		if (lazers[i]->lazerDirection == 'U') {
			lazers[i]->lazerWorldY -= lazerSpeed;
		}
		if (lazers[i]->lazerDirection == 'D') {
			lazers[i]->lazerWorldY += lazerSpeed;
		}
		if (lazers[i]->lazerDirection == 'L') {
			lazers[i]->lazerWorldX -= lazerSpeed;
		}
		if (lazers[i]->lazerDirection == 'R') {
			lazers[i]->lazerWorldX += lazerSpeed;
		}
		if (lazers[i]->lazerDirection == 'X') {
			lazers[i]->lazerWorldY += lazerSpeed;
		}

		if (checkCollision(lazers[i]->lazerWorldX, lazers[i]->lazerWorldY, 16, 16, map)) {
			// Create a new laser animation object
			LaserAnimation* animation = new LaserAnimation();
			animation->currentClipRect = &animationClipRects[0];
			animation->animationWorldX = lazers[i]->lazerWorldX;
			animation->animationWorldY = lazers[i]->lazerWorldY;

			animations.push_back(animation);
			
			// Delete the laser
			indexsToDelete.push_back(i);

			delete lazers[i];
			lazers.erase(lazers.begin() + i);
			std::cout << "Deleted the lazer's memory" << std::endl;

		}
	}

	// Play the laser explosion animations
	

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
