#include "Sound.h"
#include "Global.h"

Sound* Sound::instance = 0;

Sound* Sound::getInstance()
{
    if (instance == 0)
    {
        instance = new Sound();
    }

    return instance;
}

Sound::~Sound()
{
    _sound.resetBuffer();
    _soundBuffers.clear();

    delete instance;
}

void Sound::buttonClick()
{
    _sound.setBuffer(_soundBuffers[0]);
    _sound.play();
}

void Sound::setSFXValue(float value)
{
    _sound.setVolume(value);
}

Sound::Sound() 
{
    sf::SoundBuffer uiclick;


    if (!uiclick.loadFromFile(UI_CLICK))
        std::cout << "fail to load: UI_CLICK" << std::endl;

    _soundBuffers.push_back(uiclick);
   
}
