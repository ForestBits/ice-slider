#include <fstream>
#include "ScreenList.h"

using namespace ice;
using namespace ice::screen;

static void saveOptions(AudioData data, bool fullscreen)
{
    //clear file

    std::fstream file("options.txt", std::ios::out | std::ios::trunc);

    file << "sound:" << data.soundVolume << '\n';
    file << "music:" << data.musicVolume << '\n';
    file << "global:" << data.globalVolume << '\n';
    file << "fullscreen:" << fullscreen << '\n';
}

Options::Options(ScreenConstructionParameters parameters) :
                         backButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound),
                         fullscreenCheckbox(parameters.mainFont, parameters.checkboxBackgroundTexture, parameters.checkboxActiveBackgroundTexture, parameters.checkboxCheckTexture, parameters.clickSound),
                         soundSlider(parameters.mainFont, parameters.sliderBarTexture, parameters.sliderSliderTexture, parameters.sliderActiveSliderTexture, parameters.clickSound),
                         musicSlider(parameters.mainFont, parameters.sliderBarTexture, parameters.sliderSliderTexture, parameters.sliderActiveSliderTexture, parameters.clickSound),
                         globalAudioSlider(parameters.mainFont, parameters.sliderBarTexture, parameters.sliderSliderTexture, parameters.sliderActiveSliderTexture, parameters.clickSound)
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0];

    menuBackgroundSprite.setTexture(parameters.menuBackgroundTexture);

    backButton.setText("Menu");
    backButton.setPosition(320, 400);
    backButton.setOnClick([parameters, fullscreenMode] {

        saveOptions(parameters.audioData, parameters.window.getSize().x == fullscreenMode.width && parameters.window.getSize().y == sf::VideoMode::getFullscreenModes()[0].height);

        parameters.control.setScreen<MainMenu>(parameters);
    });

    fullscreenCheckbox.setText("Fullscreen");
    fullscreenCheckbox.setChecked(parameters.window.getSize().x == fullscreenMode.width && parameters.window.getSize().y == fullscreenMode.height);
    fullscreenCheckbox.setPosition(200, 275);
    fullscreenCheckbox.setOnClick([parameters, fullscreenMode] (bool checked) {

        if (checked)
        {
            parameters.window.create(fullscreenMode, "Ice Slider", sf::Style::Fullscreen);

            sf::View view;

            view.setSize(640, 480);
            view.setCenter(320, 240);

            parameters.window.setView(view);
        }
        else
            parameters.window.create(sf::VideoMode(640, 480), "Ice Slider");
    });

    auto soundUpdate = [parameters] (double percent) {
    
        //add all sounds here

        parameters.audioData.soundVolume = percent;

        int volume = parameters.audioData.globalVolume*parameters.audioData.soundVolume*100;
        
        parameters.clickSound.setVolume(volume);
    };
    
    auto musicUpdate = [parameters] (double percent) {
    
        //add all musics here

        parameters.audioData.musicVolume = percent;

        int volume = parameters.audioData.globalVolume*parameters.audioData.musicVolume*100;
        
        parameters.music.setVolume(volume);
    };

    soundSlider.setPercent(parameters.audioData.soundVolume);
    soundSlider.setLabel("Sounds");
    soundSlider.setOnUpdate(soundUpdate);
    soundSlider.setPosition(200, 50);

    musicSlider.setPercent(parameters.audioData.musicVolume);
    musicSlider.setLabel("Music");
    musicSlider.setOnUpdate(musicUpdate);
    musicSlider.setPosition(200, 125);

    globalAudioSlider.setPercent(parameters.audioData.globalVolume);
    globalAudioSlider.setPosition(200, 200);
    globalAudioSlider.setLabel("Global Volume");
    globalAudioSlider.setOnUpdate([parameters, soundUpdate, musicUpdate] (double percent) {

        parameters.audioData.globalVolume = percent;

        soundUpdate(parameters.audioData.soundVolume); 
        musicUpdate(parameters.audioData.musicVolume);
    });
}

void Options::update(ScreenUpdateParameters parameters)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        saveOptions(parameters.constructionParameters.audioData, parameters.window.getSize().x == sf::VideoMode::getFullscreenModes()[0].width && parameters.window.getSize().y == sf::VideoMode::getFullscreenModes()[0].height);

        throw "(quitting application)";
    }

    EventQueue events(parameters.window);

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::Closed)
        {
            saveOptions(parameters.constructionParameters.audioData, parameters.window.getSize().x == sf::VideoMode::getFullscreenModes()[0].width && parameters.window.getSize().y == sf::VideoMode::getFullscreenModes()[0].height);

            throw "(quitting application)";
        }
    }

    sf::Vector2i mousePosition = getMousePosition(parameters.window);

    backButton.update(events, mousePosition);

    fullscreenCheckbox.update(events, mousePosition);

    soundSlider.update(events, mousePosition);
    musicSlider.update(events, mousePosition);
    globalAudioSlider.update(events, mousePosition);
}

void Options::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.draw(menuBackgroundSprite);

    backButton.draw(target);

    fullscreenCheckbox.draw(target);

    soundSlider.draw(target);
    musicSlider.draw(target);
    globalAudioSlider.draw(target);

    if (transition.transitioningIn || transition.transitioningOut)
    {
        if (transition.transitioningIn)
            menuBackgroundSprite.setColor(sf::Color(255, 255, 255, (1 - transition.transitionPercent)*255));
        else if (transition.transitioningOut)
            menuBackgroundSprite.setColor(sf::Color(255, 255, 255, transition.transitionPercent*255));

        target.draw(menuBackgroundSprite);

        menuBackgroundSprite.setColor(sf::Color::White);
    }
}

double Options::getTransitionInTime() {return 1;}
double Options::getTransitionOutTime() {return 1;}