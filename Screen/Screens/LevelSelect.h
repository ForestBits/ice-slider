#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <vector>
#include "../ScreenEngine.h"
#include "../../Input/Button.h"
#include "../../Input/LevelSelectButton.h"

namespace ice {namespace screen {

class LevelSelect : public Screen
{
    sf::Sprite menuBackgroundSprite;

    input::Button backButton;

    std::vector<input::LevelSelectButton> levelButtons;

public:
    LevelSelect(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;

    double getTransitionInTime() override;
    double getTransitionOutTime() override;
};

}}

#endif