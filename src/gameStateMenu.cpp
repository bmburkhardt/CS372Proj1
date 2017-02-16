#include <SFML/Graphics.hpp>

#include "../include/gameStateMenu.hpp"
#include "../include/gameStatePlay.hpp"
#include "../include/gameState.hpp"

void GameStateMenu::draw(const float dt) {
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Black);
	//this->game->window.draw(this->game->background);

	return;
}

void GameStateMenu::update(const float dt) {}

void GameStateMenu::handleInput() {
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

			case sf::Event::KeyPressed: {
				if(event.key.code == sf::Keyboard::Escape) 
					this->game->window.close();
				else if(event.key.code == sf::Keyboard::Return) 
					this->loadgame();
				break;
			}
			default: 
				break;
		}
	}
	return;
}

GameStateMenu::GameStateMenu(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}

void GameStateMenu::loadgame() {
	this->game->pushState(new GameStatePlay(this->game));
	return;
}










