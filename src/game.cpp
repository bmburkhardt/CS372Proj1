#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "config.hpp"
#include "../include/game.hpp"
#include "../include/gameState.hpp"

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

Game::Game() {
	this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battleship", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(60);
}

Game::~Game() {
	while(!this->states.empty())
		popState();
}














