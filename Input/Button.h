//a button. Allows action on click

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <functional>
#include "Input.h"

namespace ice { namespace input { 

class Button : public Input
{
    sf::Text text;

    sf::Sprite sprite;

    const sf::Texture & activeTexture;
    const sf::Texture & inactiveTexture;

    sf::Sound & clickSound;

    sf::Vector2i position;

    bool centered;
    bool pressed = false;

    std::function<void ()> onClick;

    //position and size correctly
    void recalculate();

public:
    Button(const sf::Font & font, const sf::Texture & activeTexture, const sf::Texture & inactiveTexture, sf::Sound & clickSound);

    void setText(std::string text);

    void setPosition(int x, int y, bool centered = true);
    void setPosition(sf::Vector2i position, bool centered = true);

    void setOnClick(const std::function<void ()> & function);

    void update(EventQueue events, sf::Vector2i mousePosition) override;
    void draw(sf::RenderTarget & target) override;
};

}}

#endif