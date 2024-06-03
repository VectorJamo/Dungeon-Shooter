#pragma once
#include "Entity.h"
#include "../entities/Laser.h"

class AnotherPlayer: public Entity {
private:
	SDL_Rect* leftClipRects, * rightClipRects, * upClipRects, * downClipRects;
	SDL_Rect currentClipRect;

	char direction;
	int health;

	float animationCounter;

public:
	bool hasShot = false;

	AnotherPlayer(const char* path, float x, float y, int width, int height);
	~AnotherPlayer();

	void setDirection(char direction);
	void setHealth(int health);

	void tick() override;
	void render() override;
	void render(int playerWorldX, int playerWorldY);
};

