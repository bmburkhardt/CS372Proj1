#ifndef GAMESTATEBATTLE_HPP
#define GAMESTATEBATTLE_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class GameStateBattle : public GameState
{

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateBattle(Game* game);

private:

	sf::View gameView;
};


#endif // GAMESTATEBATTLE_HPP