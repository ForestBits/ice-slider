#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../ScreenEngine.h"
#include "../../Input/Button.h"
#include "../../Game/Level.h"

namespace ice { namespace screen { 

class MainMenu : public Screen
{
    sf::Sprite menuBackgroundSprite;

    input::Button playButton;
    input::Button instructionsButton;
    input::Button optionsButton;
    input::Button creditsButton;
    input::Button quitButton;


public:
    MainMenu(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters)  override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;

    double getTransitionInTime() override;
    double getTransitionOutTime() override;
};

}}

#endif