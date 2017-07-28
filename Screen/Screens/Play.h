//play a level

#ifndef PLAY_H
#define PLAY_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include "../../Game/Level.h"
#include "../ScreenEngine.h"

namespace ice { namespace screen {

class Play : public Screen
{
    bool pressed = false;

    Level level;

    sf::Clock clock;

    sf::Sprite menuBackgroundSprite;

    sf::Text levelTitleText;
    sf::Text moveCountText;
    sf::Text timeText;

    long time = 0;

    float timeRemainder = 0;

    int levelNumber;
    int moveCount = 0;

public:
    Play(ScreenConstructionParameters parameters, const LevelData & levelData, int levelNumber);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;

    double getTransitionInTime() override;
    double getTransitionOutTime() override;
};

}}

#endif