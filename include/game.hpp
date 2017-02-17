#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <SFML/Graphics.hpp>
#include <map>
using std::map;
#include <string>
using std::string;

#include "textureManager.hpp"
#include "tile.hpp"

class GameState;

class Game
{

public:
	const static int tileSize = 8;

	std::stack<GameState*> states;

	sf::RenderWindow window;
	TextureManager texmgr;
	sf::Sprite menubg;
	sf::Sprite gamebg;
	sf::Font font;
	sf::Text headline;
	sf::Text prompt;

	map<string, Tile> tileAtlas;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

	Game();
	~Game();

private:
	void loadTextures();
	void loadTiles();

};





#endif // GAME_HPP
