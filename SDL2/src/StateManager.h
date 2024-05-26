#pragma once

class StateManager {
public:
	static StateManager* currentState;

	virtual void tick() = 0;
	virtual void render() = 0;
};
