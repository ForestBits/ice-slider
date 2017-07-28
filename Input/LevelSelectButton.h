//button used in level select

#ifndef LEVELSELECTBUTTON_H
#define LEVELSELECTBUTTON_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <functional>
#include "Input.h"


namespace ice { namespace input {

class LevelSelectButton : public Input
{
    const sf::Texture & inactiveTexture;
    const sf::Texture & activeTexture;
    const sf::Texture & lockedTexture;

    sf::Sound clickSound;

    sf::Sprite sprite;

    sf::Text text;

    bool locked = true;

    bool active = false;

    int number;

    std::function<void (int number)> onClick;

public:
    LevelSelectButton(const sf::Font & font, const sf::Texture & inactiveTexture, const sf::Texture & activeTexture, const sf::Texture & lockedTexture, sf::Sound & clickSound);

    void setLocked(bool locked);

    void setNumber(int number);

    void setOnClick(const std::function<void (int number)> & function);

    void setPosition(int x, int y);
    void setPosition(sf::Vector2i position);

    void update(EventQueue events, sf::Vector2i mousePosition) override;

    void draw(sf::RenderTarget & target) override;
};

}}

#endif