#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
using std::string;
#include <map>
using std::map;

class TextureManager
{

public:
	// Add a texture from a file
	void loadTexture(const string &name, const string &filename);

	// translate an id into a reference
	sf::Texture &getRef(const string &texture);

	TextureManager() {}

private:
	// Array for textures used
	map<string, sf::Texture> textures;
};


#endif // TEXTUREMANAGER_HPP