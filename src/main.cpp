#include <iostream>

#include "config.hpp"
#include "../include/game.hpp"
#include "../include/gameStateMenu.hpp"


int main()
{
	std::cout << "Battleship" << std::endl;
	std::cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << std::endl;

	Game game;

	game.pushState(new GameStateMenu(&game));
	game.gameLoop();

	return 0;
}