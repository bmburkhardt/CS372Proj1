#include "../include/game.hpp"
#include "../include/gameStateMenu.hpp"


int main()
{
	Game game;

	game.pushState(new gameStateMenu(&game));
	game.gameLoop();

	return 0;
}