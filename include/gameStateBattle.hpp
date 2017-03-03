#ifndef GAMESTATEBATTLE_HPP
#define GAMESTATEBATTLE_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class GameStateBattle : public GameState
{

public:
	int playerShots = 0;
	int AIShots = 0;

	int playerHits = 0;
	int AIHits = 0;

	void playerHasWon(int ph, int ah);
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	void AITurn();

	GameStateBattle(Game* game);

private:

	sf::View gameView;
	void loadgame();
};


#endif // GAMESTATEBATTLE_HPP