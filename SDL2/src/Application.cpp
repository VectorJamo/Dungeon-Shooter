#include "Game.h"
#include <memory>
#include <string>

int main(int argc, char** argv) {
	std::unique_ptr<Game> game = std::make_unique<Game>(768, 640, "Dungeon Shooter");
	game->run();

	return 0;
}