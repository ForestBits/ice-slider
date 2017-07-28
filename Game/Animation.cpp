#include <cassert>
#include "Animation.h"

using namespace ice;

Animation::Animation() {}

Animation::Animation(const sf::Texture & texture, std::initializer_list<std::pair<sf::IntRect, float>> frames)
{
    create(texture, frames);
}

void Animation::create(const sf::Texture & texture, std::initializer_list<std::pair<sf::IntRect, float>> frames)
{
    time = 0;
    totalTime = 0;
    
    this->frames = frames;

    this->texture = &texture;

    for (auto frame : frames)
        totalTime += frame.second;
}

void Animation::setFrame(int index)
{
    assert(index >= 0 && index < frames.size() && "frame index must be in range");

    time = (float) index/frames.size();
}

const sf::IntRect & Animation::getCurrentFrameRectangle() const
{
    assert(frames.size() != 0 && "Animation must be initialized to use");

    time += clock.restart().asSeconds();

    while (time >= totalTime)
        time -= totalTime;

    return frames[(time/totalTime)*frames.size()].first;
}