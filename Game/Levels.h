//holds all the levels

#ifndef LEVELS_H
#define LEVELS_H

#include <vector>
#include <unordered_map>
#include "LevelData.h"

namespace ice {

//hackish thingy
class LevelList
{
    static bool init;

    static std::vector<LevelData> levels;

    static std::unordered_map<std::string, Animation> animations;

public:
    static void initialize(const sf::Texture & spriteSheet, const std::unordered_map<std::string, sf::IntRect> & textureRectangles);

    //call initialize before using this
    static const std::vector<LevelData> & getLevels();

    LevelList() = delete;
};

}

#endif