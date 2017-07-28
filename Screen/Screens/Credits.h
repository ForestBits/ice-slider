//credits screen (music, SFML)

#ifndef CREDITS_H
#define CREDITS_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../../Input/Button.h"
#include "../ScreenEngine.h"

namespace ice { namespace screen {

class Credits : public Screen
{
    sf::Sprite menuBackgroundSprite;
    sf::Sprite sfmlLogoSprite;

    sf::Text musicText;
    sf::Text fontText;

    input::Button backButton;

public:
    Credits(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;

    double getTransitionInTime() override;
    double getTransitionOutTime() override;
};

}}

#endif