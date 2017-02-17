#include <stack>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "config.hpp"
#include "../include/game.hpp"
#include "../include/gameState.hpp"
#include "../include/textureManager.hpp"
#include "../include/tile.hpp"

void Game::pushState(GameState* state) {
	this->states.push(state);

	return;
}

void Game::popState() {
	delete this->states.top();
	this->states.pop();

	return;
}

void Game::changeState(GameState* state) {
	if(!this->states.empty())
		popState();
	pushState(state);

	return;
}

GameState* Game::peekState() {
	if(this->states.empty())
		return nullptr;
	return this->states.top();
}

void Game::gameLoop() {
	sf::Clock clock;

	while(this->window.isOpen()) {
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if(peekState() == nullptr)
			continue;
		peekState()->handleInput();
		peekState()->update(dt);
		this->window.clear(sf::Color::Black);
		peekState()->draw(dt);
		this->window.display();
	}
}

void Game::loadTextures() {
	texmgr.loadTexture("gamebg",    "../res/img/gamebg.jpg");
	texmgr.loadTexture("menubg",    "../res/img/menubg.jpg");
	texmgr.loadTexture("water",     "../res/tiles/water32.jpg");
	texmgr.loadTexture("hit",       "../res/tiles/hit32.jpg");
	texmgr.loadTexture("miss",      "../res/tiles/miss32.jpg");
	texmgr.loadTexture("ship",      "../res/tiles/ship32.jpg");
}

Game::Game() {
	this->loadTextures();
	this->loadTiles();

	this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battleship", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(60);

	if(!font.loadFromFile("../res/fonts/TopSecret.ttf"))
		std::cout << "Font couldn't be found" << std::endl;
	this->headline.setFont(font);
	this->headline.setString("[Battleship]");
	this->headline.setCharacterSize(72);
	this->headline.setColor(sf::Color::Black);
	this->headline.setPosition(170,100);

	this->prompt.setFont(font);
	this->prompt.setString("[Press] [Enter]");
	this->prompt.setCharacterSize(24);
	this->prompt.setColor(sf::Color::Black);
	this->prompt.setPosition(310,230);



	this->menubg.setTexture(this->texmgr.getRef("menubg"));
	this->gamebg.setTexture(this->texmgr.getRef("gamebg"));	
}

Game::~Game() {
	while(!this->states.empty())
		popState();
}

void Game::loadTiles()
{
	Animation staticAnim(0, 0, 1.0f);
	this->tileAtlas["water"] = Tile(this->tileSize, 1, texmgr.getRef("water"), { staticAnim }, TileType::WATER);
	this->tileAtlas["ship"] = Tile(this->tileSize, 1, texmgr.getRef("ship"), { staticAnim }, TileType::SHIP);
	this->tileAtlas["hit"] = Tile(this->tileSize, 1, texmgr.getRef("hit"), { staticAnim }, TileType::HIT);
	this->tileAtlas["miss"] = Tile(this->tileSize, 1, texmgr.getRef("miss"), { staticAnim }, TileType::MISS);
}














