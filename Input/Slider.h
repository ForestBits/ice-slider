//a standard slider bar

#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <functional>
#include "Input.h"

namespace ice { namespace input {

class Slider : public Input
{
    bool active = false;

    double percent = 0;

    sf::Vector2i position;

    sf::Text label;

    const sf::Texture & activeSlider;
    const sf::Texture & inactiveSlider;

    sf::Sprite barSprite;
    sf::Sprite sliderSprite;

    sf::Sound & updateSound;

    std::function<void (double percent)> onUpdate;

    void recalculate();

public:
    Slider(const sf::Font & font, const sf::Texture & barTexture, const sf::Texture & sliderTexture, const sf::Texture & activeSliderTexture, sf::Sound & updateSound);

    //[0, 1]
    double getPercent();

    //[0, 1]
    void setPercent(double percent);

    void setPosition(int x, int y);
    void setPosition(sf::Vector2i position);

    void setLabel(const std::string & label);

    void setOnUpdate(const std::function<void (double percent)> & function);

    void update(EventQueue events, sf::Vector2i mousePosition) override;

   void draw(sf::RenderTarget & target) override; 
};

}}

#endif