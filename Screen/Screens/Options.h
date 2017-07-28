//audio and fullscreen options

#ifndef OPTIONS_H
#define OPTIONS_H

#include "../ScreenEngine.h"
#include "../../Input/Slider.h"
#include "../../Input/Button.h"
#include "../../Input/Checkbox.h"

namespace ice { namespace screen {

class Options : public Screen
{
    sf::Sprite menuBackgroundSprite;

    input::Button backButton;

    input::Checkbox fullscreenCheckbox;

    input::Slider soundSlider;
    input::Slider musicSlider;
    input::Slider globalAudioSlider;

public:
    Options(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;

    double getTransitionInTime() override;
    double getTransitionOutTime() override;
};

}}

#endif