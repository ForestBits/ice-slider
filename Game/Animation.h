//holds several textures (reference, they must be kept alive) and frame times
//gives current texture given time 

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <initializer_list>

namespace sf {class Texture;}

namespace ice {

class Animation
{
    const sf::Texture * texture;

    std::vector<std::pair<sf::IntRect, float>> frames;

    mutable sf::Clock clock;

    mutable float time;
    float totalTime;

public:
    Animation();
    Animation(const sf::Texture & texture, std::initializer_list<std::pair<sf::IntRect, float>> frames);

    void create(const sf::Texture & texture, std::initializer_list<std::pair<sf::IntRect, float>> frames);

    void setFrame(int index);

    const sf::IntRect & getCurrentFrameRectangle() const;
};

}

#endif