#ifndef GAMESTATEPLAY_HPP
#define GAMESTATEPLAY_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"
#include "map.hpp"
#include "tile.hpp"

enum class ActionState { NONE, PANNING };

class GameStatePlay : public GameState
{

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStatePlay(Game* game);

private:
	ActionState actionState;

	sf::View gameView;
	//sf::View guiView

	Map map;

	sf::Vector2i panningAnchor;
	float zoomLevel;
};




#endif // GAMESTATEPLAY_HPP