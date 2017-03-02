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

};




#endif // GAMESTATESETUP_HPP