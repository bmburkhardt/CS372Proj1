#include <SFML/Graphics.hpp>

#include "../incude/gameStateMenu.hpp"
#include "../include/gameStatePlay.hpp"
#include "../include/gameState.hpp"

void gameStateMenu::draw(const float dt) {
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	return;
}

void gameStateMenu::update(const float dt) {}

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

			case sf::Event::KeyPressed: {
				if(event.key.code == sf::Keyboard::Escape) 
					this->game->window.close();
				else if(event.key.code == sf::Keyboard::Enter) 
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
	sf::Vector2f pos = sf::Vector2f(this->window.getSize());
	this->view.setSize(pos);
	pos * = 0.5f;
	this->view.setCenter(pos);
}

void GameStateMenu::loadgame() {
	this->game->pushState(new gameStatePlay(this->game));
	return;
}










