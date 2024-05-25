#include "Game.h"
#include <memory>

int main(int argc, char** argv) {
	std::unique_ptr<Game> game = std::make_unique<Game>(500, 500, "My Game");
	game->run();

	return 0;
}