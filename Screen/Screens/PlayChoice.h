//you come here after successfully completing a level

#ifndef PLAYCHOICE_H
#define PLAYCHOICE_H

#include <SFML/Graphics/Sprite.hpp>
#include "../ScreenEngine.h"
#include "../../Input/Button.h"

namespace ice { namespace screen {

class PlayChoice : public Screen
{
    bool hasNext = true;

    sf::Sprite sprite;
    sf::Sprite menuBackgroundSprite;
    sf::Sprite backgroundSprite;

    sf::Text text;

    sf::Texture backgroundTexture;

    sf::RenderTexture render;

    input::Button restartButton;
    input::Button levelSelectButton;
    input::Button nextLevelButton;
public:
    PlayChoice(ScreenConstructionParameters parameters, int currentLevelNumber);

    void update(ScreenUpdateParameters)  override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;

    double getTransitionInTime() override;
    double getTransitionOutTime() override;
};

}}

#endif