#include <SFML/Graphics.hpp>

#include "../include/gameStatePlay.hpp"
#include "../include/gameState.hpp"
#include "../include/map.hpp"

void GameStatePlay::draw(const float dt) {

	this->game->window.clear(sf::Color::Red);
	this->game->window.draw(this->game->gamebg);
	//this->game->window.draw(this->game->watertile);

	this->game->window.setView(this->gameView);
	map.draw(this->game->window, dt);

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

			case sf::Event::MouseMoved: {
    			// Pan the camera 
    			if(this->actionState == ActionState::PANNING) {
        			sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(this->game->window) - this->panningAnchor);
        			gameView.move(-1.0f * pos * this->zoomLevel);
        			panningAnchor = sf::Mouse::getPosition(this->game->window);
    			}
    			break;
			}
			case sf::Event::MouseButtonPressed: {
    			// Start panning 
    			if(event.mouseButton.button == sf::Mouse::Middle) {
        			if(this->actionState != ActionState::PANNING) {
            			this->actionState = ActionState::PANNING;
            			this->panningAnchor = sf::Mouse::getPosition(this->game->window);
        			}
    			}
    			break;
			}
			case sf::Event::MouseButtonReleased: {
    			// Stop panning */
    			if(event.mouseButton.button == sf::Mouse::Middle) {
        			this->actionState = ActionState::NONE;
    			}
    			break;
			}
			
			// Zoom the view 
			case sf::Event::MouseWheelMoved: {
    			if(event.mouseWheel.delta < 0) {
        			gameView.zoom(2.0f);
        			zoomLevel *= 2.0f;
    			}
    			else {
        			gameView.zoom(0.5f);
        			zoomLevel *= 0.5f;
    			}
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

	map = Map("battleship_map.dat", 0, 0, game->tileAtlas);

	this->zoomLevel = 1.0f;

	// Centre the camera on the map
	sf::Vector2f centre(this->map.width, this->map.height*0.5);
	centre *= float(this->map.tileSize);
	//gameView.setCenter(centre);
	this->actionState = ActionState::NONE;
}










