//ye olde' checkbox (not one of the three-state mutants)

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <functional>
#include "Input.h"


namespace ice { namespace input {

class Checkbox : public Input
{
    bool checked = false;
    bool active = false;

    sf::Text label;

    const sf::Texture & inactiveBackground;
    const sf::Texture & activeBackground;

    sf::Sprite boxSprite;
    sf::Sprite checkSprite;

    sf::Sound & clickSound;

    sf::Vector2i position;

    std::function<void (bool checked)> onClick;

    //position and size correctly
    void recalculate();

public:
    Checkbox(const sf::Font & font, const sf::Texture & boxTexture, const sf::Texture & activeBoxTexture, const sf::Texture & checkTexture, sf::Sound & clickSound);

    bool getChecked();

    void setChecked(bool checked);

    void setPosition(int x, int y);
    void setPosition(sf::Vector2i position);

    void setOnClick(const std::function<void (bool checked)> & function);

    void setText(const std::string & text);

    void update(EventQueue events, sf::Vector2i mousePosition) override;

    void draw(sf::RenderTarget & target) override;
};

}}

#endif