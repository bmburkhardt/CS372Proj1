#include <SFML/Graphics.hpp>

#include "../include/gameStatePlay.hpp"
#include "../include/gameState.hpp"

void GameStatePlay::draw(const float dt) {

	this->game->window.clear(sf::Color::Red);
	//this->game->window.draw(this->game->background);

	return;
}

void GameStatePlay::update(const float dt) {
	return;
}

void GameStatePlay::handleInput() {
	sf::Event event;

	while(this->game->window.pollEvent(event)) {
		switch(event.type) {
			// Close the window
			case sf::Event::Closed: {
				game->window.close();
				break;
			}
			
			/*
				Possible add resize function
			*/

			
			default: 
				break;
		}
	}
	return;
}

GameStatePlay::GameStatePlay(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	//this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	//this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);
}










