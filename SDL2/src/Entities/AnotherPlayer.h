#pragma once
#include "Entity.h"

class AnotherPlayer: public Entity{
private:
	SDL_Rect* leftClipRects, * rightClipRects, * upClipRects, * downClipRects;
	SDL_Rect currentClipRect;

	char direction;
	int health;

public:
	AnotherPlayer(const char* path, float x, float y, int width, int height);
	~AnotherPlayer();

	void setDirection(char direction);
	void setHealth(int health);

	void tick() override;
	void render() override;
	void render(int playerWorldX, int playerWorldY);
};

