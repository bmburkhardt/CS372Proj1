#include "../include/game.hpp"
#include "../include/gameStateMenu.hpp"


int main()
{
	Game game;

	game.pushState(new GameStateMenu(&game));
	game.gameLoop();

	return 0;
}