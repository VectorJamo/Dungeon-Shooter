#pragma once

#include <SDL.h>

class StateManager {
public:
	static StateManager* currentState;

	virtual void handleInput(SDL_Event& ev) = 0;
	virtual void tick() = 0;
	virtual void render() = 0;
};
