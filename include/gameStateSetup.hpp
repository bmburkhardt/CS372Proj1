#ifndef GAMESTATEBATTLE_HPP
#define GAMESTATEBATTLE_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class GameStateSetup : public GameState
{

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateSetup(Game* game);

private:

	sf::View gameView;
	void loadgame();
};




#endif // GAMESTATEBATTLE_HPP