#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
using std::stack;
#include <SFML/Graphics.hpp>
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <random>

#include "textureManager.hpp"
#include "board.hpp"

class GameState;

class Game
{

public:
	const static int tileSize = 32;

	stack<GameState*> states;

	sf::RenderWindow window;
	TextureManager texmgr;
    Board board;
	sf::Sprite menubg;
	sf::Sprite gamebg;
	sf::Font font;
	sf::Text headline;
	sf::Text prompt;
	sf::Text result;
	sf::Text quitPrompt;

	bool playerWin = false;

    vector<int> level = randomBoard(rand()%12);


	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

	Game();
	~Game();

	vector<int> randomBoard(int n);
	

private:
	void loadTextures();

};





#endif // GAME_HPP
