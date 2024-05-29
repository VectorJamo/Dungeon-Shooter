#include "Laser.h"

#include "../graphics/Display.h"
Laser::Laser(const char* path, const char* path2, float x, float y, int width, int height, Tilemap* map): Entity(path, x, y, width, height) {
	entityImage2 = IMG_LoadTexture(Display::getRendererInstance(), path2); // 1 = vertical laser, 2 = horizontal laser
	lazerSpeed = 1;
}

Laser::~Laser(){
	for (auto& lazer : lazers)
		delete lazer;
}

void Laser::tick(){
}

void Laser::render(){
}

void Laser::tick(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, char& direction) {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_SPACE]) {
		ActiveLazer* lazer = new ActiveLazer();
		lazer->lazerWorldX = playerWorldX;
		lazer->lazerWorldY = playerWorldY;
		lazer->lazerDirection = direction; 

		lazers.push_back(lazer);
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
	}
}

void Laser::render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, char& direction){
	int lazerWorldX = x;
	int lazerWorldY = y;
	int lazerScreenX = lazerWorldX - ((playerWorldX + playerWidth / 2) - Display::getScreenWidth() / 2);
	int lazerScreenY = lazerWorldY - ((playerWorldY + playerHeight / 2) - Display::getScreenHeight() / 2);

	SDL_Rect dest = { lazerWorldX, lazerWorldY, width, height };
	if(direction == 'U' || direction == 'D')
		SDL_RenderCopy(Display::getRendererInstance(), entityImage, NULL, &dest);
	else
		SDL_RenderCopy(Display::getRendererInstance(), entityImage2, NULL, &dest);
}
