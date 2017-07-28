#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../ScreenEngine.h"
#include "../../Game/Level.h"
#include "../../Input/Button.h"

namespace ice { namespace screen {

class Instructions3 : public Screen
{
    sf::Sprite menuBackgroundSprite;

    sf::Text lessonText;

    Level level;

    input::Button backButton;
    input::Button previousButton;

public:
    Instructions3(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition);

    double getTransitionInTime() override;
    double getTransitionOutTime() override;
};

}}