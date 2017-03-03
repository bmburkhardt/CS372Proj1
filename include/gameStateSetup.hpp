#ifndef GAMESTATESETUP_HPP
#define GAMESTATESETUP_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class GameStateSetup : public GameState
{

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	void placeShip(int n, int x, int y);

	GameStateSetup(Game* game);


private:

	sf::View gameView;
	void loadgame();
	bool firstTilePlaced = false;
	bool secondTilePlaced = false;
	bool horizontal = false;
	bool vertical = true;
	bool secondOfSize3 = false;
	int placedIndex;
	int originalIndex;
	int size = 1;
	int shipSize = 2;

};




#endif // GAMESTATESETUP_HPP