#include <SFML/Graphics.hpp>
#include <map>
using std::map;
#include <string>
using std::string;

#include "../include/textureManager.hpp"

void TextureManager::loadTexture(const string &name, const string &filename) {
	// Load the texture
	sf::Texture tex;
	tex.loadFromFile(filename);

	// Add it to the list of textures
	this->textures[name] = tex;

	return;
}

sf::Texture & TextureManager::getRef(const string &texture) {
	return this->textures.at(texture);
}