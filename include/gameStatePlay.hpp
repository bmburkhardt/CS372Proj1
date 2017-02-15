#ifndef GAMESTATEPLAY_HPP
#define GAMESTATEPLAY_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class GameStatePlay : public GameState
{

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStatePlay(Game* game);

private:
	sf::View gameView;
	//sf::View guiView
};




#endif // GAMESTATEPLAY_HPP