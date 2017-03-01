#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class Board : public sf::Drawable, public sf::Transformable
{
public:
    Board() {}
    bool load(const std::string& tileset, sf::Vector2u tileSize, 
        std::vector<int>& tiles, unsigned int width, unsigned int height);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif // BOARD_HPP