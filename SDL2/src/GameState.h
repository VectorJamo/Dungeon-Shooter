#pragma once
#include "StateManager.h"
#include "tilemap/Tilemap.h"

#include "entities/Player.h"

class GameState: public StateManager {
private:
	Tilemap* map;
	Player* player;

public:
	GameState();
	~GameState();

	void handleInput(SDL_Event& ev) override;
	void tick() override;
	void render() override;
};

