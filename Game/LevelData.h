//what each level contains

#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <SFML/System/Vector2.hpp>
#include <string>
#include "GameEnums.h"

//what each tile has
struct TileData
{
    ice::Block block;

    ice::VisualTile visual;
};

namespace ice {

struct LevelData
{
    sf::Vector2i size;

    std::vector<std::vector<TileData>> tiles;

    sf::Vector2i startPosition;
    sf::Vector2i endPosition;

    std::string title;

public:
    LevelData(int width, int height);
    LevelData(sf::Vector2i dimensions);

    Block getBlockType(int x, int y) const;
    Block getBlockType(sf::Vector2i coordinates) const;

    VisualTile getVisualTile(int x, int y) const;
    VisualTile getVisualTile(sf::Vector2i coordinates) const;

    sf::Vector2i getStartPosition() const;
    sf::Vector2i getEndPosition() const;

    sf::Vector2i getSize() const;

    const std::string & getTitle() const;

    void setBlockType(int x, int y, Block type);
    void setBlockType(sf::Vector2i coordinates, Block type);

    void setVisualTile(int x, int y, VisualTile visual);
    void setVisualTile(sf::Vector2i coordinates, VisualTile visual);

    void setStartPosition(int x, int y);
    void setStartPosition(sf::Vector2i coordinates);

    void setEndPosition(int x, int y);
    void setEndPosition(sf::Vector2i coordinates);

    void setTitle(const std::string & title);
};

}

#endif