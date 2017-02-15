#include <SFML/Graphics.hpp>

#include "../include/gameStatePlay.hpp"
#include "../include/gameState.hpp"

void gameStateMenu::draw(const float dt) {

	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	return;
}

void gameStateMenu::update(const float dt) {
	return;
}

void gameStateMenu::handleInput() {
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

GameStateMenu::GameStateMenu(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->window.getSize());
	//this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos * = 0.5f;
	//this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);
}










