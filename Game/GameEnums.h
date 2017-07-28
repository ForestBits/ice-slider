#ifndef GAMEENUMS_H
#define GAMEENUMS_H

#include <SFML/Graphics/Rect.hpp>
#include "Animation.h"

namespace ice {

enum class Block
{
    ICE, //slippery
    WALL, //impassible
    GROUND //not slippery
};

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct VisualTile
{
    sf::IntRect textureRectangle;

    Animation * animation = nullptr;
};

}

#endif