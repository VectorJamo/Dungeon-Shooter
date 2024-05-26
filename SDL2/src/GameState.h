#pragma once
#include "StateManager.h"

class GameState: public StateManager {
private:
	

public:
	GameState();
	~GameState();

	void tick() override;
	void render() override;
};

