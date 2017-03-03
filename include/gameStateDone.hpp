#ifndef GAMESTATEDONE_HPP
#define GAMESTATEDONE_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class GameStateDone : public GameState
{

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	

	GameStateDone(Game* game);

private:

	sf::View gameView;
	void loadgame();
};




#endif // GAMESTATEDONE_HPP