#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <thread>
#include <exception>
#include <chrono>
#include <string>
#include <unordered_map>
#include "Utility/EventQueue.h"
#include "Utility/Random.h"
#include "Game/Animation.h"
#include "Game/Level.h"
#include "Screen/ScreenEngine.h"
#include "Screen/Screens/MainMenu.h"
#include "Game/Levels.h"
#include "Utility/StringNumberConvert.h"

using namespace ice;

static sf::IntRect getRectangleForPosition(int x, int y)
{
    sf::IntRect rectangle;

    rectangle.width = 32;
    rectangle.height = 32;

    rectangle.left = (x + 1) + 32*x;
    rectangle.top = (y + 1) + 32*y;

    return rectangle;
}

class MissingResourceException : public std::runtime_error
{

public:
    MissingResourceException(const std::string & resourceName) : std::runtime_error("Missing file: " + resourceName)
    {

    }
};

int main()
{
    //if there was an error last time we ran, remove the log of it
    //if it is fixed, all is well, ohterwise it will be made again

    remove("error.txt");

    try
    {
        sf::Font mainFont;

        if (!mainFont.loadFromFile("res/Pacifico.ttf"))
            throw MissingResourceException("Pacifico.ttf");

        sf::Music music;

        if (!music.openFromFile("res/Mining by Moonlight.ogg"))
            throw MissingResourceException("Mining by Moonlight.ogg");

        music.setLoop(true);

        sf::SoundBuffer clickSoundBuffer;

        if (!clickSoundBuffer.loadFromFile("res/clickSound.wav"))
            throw MissingResourceException("clickSound.wav");

        sf::Sound clickSound;

        clickSound.setBuffer(clickSoundBuffer);

        sf::Texture menuBackgroundTexture;

        if (!menuBackgroundTexture.loadFromFile("res/menuBackground.png"))
            throw MissingResourceException("menuBackground.png");

        sf::Texture activeButtonTexture;

        if (!activeButtonTexture.loadFromFile("res/activeButton.png"))
            throw MissingResourceException("activeButton.png");

        sf::Texture inactiveButtonTexture;

        if (!inactiveButtonTexture.loadFromFile("res/inactiveButton.png"))
            throw MissingResourceException("inactiveButton.png");

        sf::Texture sliderBarTexture;

        if (!sliderBarTexture.loadFromFile("res/sliderBar.png"))
            throw MissingResourceException("sliderBar.png");

        sf::Texture sliderSliderTexture; //that is pretty slidey

        if (!sliderSliderTexture.loadFromFile("res/sliderSlider.png"))
            throw MissingResourceException("sliderSlider.png");

        sf::Texture checkboxBackgroundTexture;

        if (!checkboxBackgroundTexture.loadFromFile("res/checkboxBackground.png"))
            throw MissingResourceException("checkboxBackground.png");

        sf::Texture checkboxCheckTexture;

        if (!checkboxCheckTexture.loadFromFile("res/checkboxCheck.png"))
            throw MissingResourceException("checkboxCheck.png");

        sf::Texture spriteSheetTexture;

        if (!spriteSheetTexture.loadFromFile("res/spritesheet.png"))
            throw MissingResourceException("spritesheet.png");

        sf::Texture checkboxactiveBackgroundTexture;

        if (!checkboxactiveBackgroundTexture.loadFromFile("res/checkboxActiveBackground.png"))
            throw MissingResourceException("checkboxActiveBackground.png");

        sf::Texture sliderActiveSliderTexture;

        if (!sliderActiveSliderTexture.loadFromFile("res/sliderActiveSlider.png"))
            throw MissingResourceException("sliderActiveSlider.png");

        sf::Texture sfmlLogoTexture;

        if (!sfmlLogoTexture.loadFromFile("res/sfmlLogo.png"))
            throw MissingResourceException("sfmlLogo.png");

        sf::Texture levelSelectInactiveTexture;

        if (!levelSelectInactiveTexture.loadFromFile("res/levelSelectInactive.png"))
            throw MissingResourceException("levelSelectInactive.png");

        sf::Texture levelSelectActiveTexture;

        if (!levelSelectActiveTexture.loadFromFile("res/levelSelectActive.png"))
            throw MissingResourceException("levelSelectActive.png");

        sf::Texture levelSelectLockedTexture;

        if (!levelSelectLockedTexture.loadFromFile("res/levelSelectLocked.png"))
            throw MissingResourceException("levelSelectLocked.png");

        sf::Image iconImage;

        if (!iconImage.loadFromFile("res/icon.png"))
            throw MissingResourceException("icon.png");

        std::unordered_map<std::string, sf::IntRect> textureRectangles;

        textureRectangles["ice"] = getRectangleForPosition(0, 0);
        textureRectangles["rocks"] = getRectangleForPosition(1, 0);
        textureRectangles["snow"] = getRectangleForPosition(2, 0);
        textureRectangles["player"] = getRectangleForPosition(3, 0);
        textureRectangles["water1"] = getRectangleForPosition(4, 0);
        textureRectangles["water2"] = getRectangleForPosition(5, 0);
        textureRectangles["water3"] = getRectangleForPosition(6, 0);
        textureRectangles["cliff"] = getRectangleForPosition(7, 0);
        textureRectangles["stream1"] = getRectangleForPosition(8, 0);
        textureRectangles["stream2"] = getRectangleForPosition(9, 0);
        textureRectangles["stream3"] = getRectangleForPosition(10, 0);
        textureRectangles["stream4"] = getRectangleForPosition(11, 0);
        textureRectangles["finish"] = getRectangleForPosition(13, 0);
        textureRectangles["snowman"] = getRectangleForPosition(14, 0);
        textureRectangles["verticalbridge"] = getRectangleForPosition(15, 0);
        textureRectangles["secretrock"] = getRectangleForPosition(16, 0);
        textureRectangles["deer"] = getRectangleForPosition(17, 0);
        textureRectangles["santa"] = getRectangleForPosition(18, 0);
        textureRectangles["tree"] = getRectangleForPosition(0, 1);

        LevelList::initialize(spriteSheetTexture, textureRectangles);

        sf::RenderWindow window;

        std::unordered_map<std::string, Animation *> animations;

        Animation waterAnimation(spriteSheetTexture, {
            {textureRectangles["water1"], 0.1},
            {textureRectangles["water2"], 0.1},
            {textureRectangles["water3"], 0.1}
        });

        Animation waterStreamAnimation = {spriteSheetTexture, {
            {textureRectangles["stream1"], 0.1},
            {textureRectangles["stream2"], 0.1},
            {textureRectangles["stream3"], 0.1},
            {textureRectangles["stream4"], 0.1}
        }};

        animations["water"] = &waterAnimation;
        animations["waterstream"] = &waterStreamAnimation;

        AudioData audioData;

        bool fullscreen = false;

        //loading from the options file for audio and fullscreen setting

        std::fstream file("options.txt", std::ios::in);

        //is nonexistent or empty
        if (!file || file.peek() == std::ifstream::traits_type::eof())
        {
            audioData.globalVolume = 1;
            audioData.soundVolume = 0.5;
            audioData.musicVolume = 0.5;
        }
        else
        {
            //file is valid

            while (!file.bad())
            {
                std::string input;

                std::getline(file, input);

                std::string string = input.substr(input.find(":") + 1);

                if (input.find("sound") != std::string::npos)
                    audioData.soundVolume = toNumber<double>(string);
                else if (input.find("music") != std::string::npos)
                    audioData.musicVolume = toNumber<double>(string);
                else if (input.find("global") != std::string::npos)
                    audioData.globalVolume = toNumber<double>(string);
                else if (input.find("fullscreen") != std::string::npos)
                    fullscreen = (string == "1");
                else
                    break;
            }
        }

        //updating sounds and musics with loaded volume

        int soundVolume = audioData.globalVolume*audioData.soundVolume*100;
        int musicVolume = audioData.globalVolume*audioData.musicVolume*100;

        clickSound.setVolume(soundVolume);

        music.setVolume(musicVolume);

        ScreenEngine engine(window, mainFont, menuBackgroundTexture, activeButtonTexture, inactiveButtonTexture, 
                                      sliderBarTexture, sliderSliderTexture, sliderActiveSliderTexture, checkboxBackgroundTexture, 
                                      checkboxactiveBackgroundTexture, checkboxCheckTexture, sfmlLogoTexture, 
                                      levelSelectInactiveTexture, levelSelectActiveTexture, levelSelectLockedTexture,
                                      clickSound, music, spriteSheetTexture, textureRectangles, animations, audioData);

        if (fullscreen)
        {
            window.create(sf::VideoMode::getFullscreenModes()[0], "Ice Slider", sf::Style::Fullscreen);

            sf::View view;

            view.setSize(640, 480);
            view.setCenter(320, 240);

            window.setView(view);
        }
        else
            window.create(sf::VideoMode(640, 480), "Ice Slider", sf::Style::Close | sf::Style::Titlebar);

        window.setIcon(32, 32, iconImage.getPixelsPtr());

        engine.getController().setScreen<screen::MainMenu>(engine.getConstructionParameters());

        sf::Clock update, draw;

        while (true)
        {
            if (update.getElapsedTime().asSeconds() > 0.06)
            {
                update.restart();

                engine.update();
            }

            if (draw.getElapsedTime().asSeconds() > 0.015)
            {
                draw.restart();

                engine.draw();

                window.display();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    catch (const std::exception & exception)
    {
        //write problem to error file

        std::fstream file("error.txt", std::ios::out | std::ios::app);

        file << exception.what();
    }

    catch (...)
    {
        return 0; //something broke, or we quit
    }
}
