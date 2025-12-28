// File: SoundManager.h
// Brief: Declares the SoundManager component.
#pragma once
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

// SoundManager encapsulates related behavior and state.

class SoundManager {
public:
    
    
    // Plays a sound effect.
    
    
    static void play(const std::string& path, bool loop = true, float volume = 1.0f);
    // Stops playback.
    static void stop();
    // TODO: Add a brief description.
    static void pause();
    // TODO: Add a brief description.
    static void resume();

    
    
    // Plays a sound effect.

    
    
    static int playSfx(const std::string& path, float volume = 1.0f);

    
    
    // Plays a sound effect.

    
    
    static int playSfxRandom(const std::string& key, float volume = 1.0f);

    
    // Sets the Volume.

    
    static void setVolume(float v);
    // Returns the Volume.
    static float getVolume();

    
    // Sets the BgmBaseVolume.

    
    static void setBgmBaseVolume(float v);
    // Returns the BgmBaseVolume.
    static float getBgmBaseVolume();
private:
    // Initializes the object.
    static void initFromUserDefault();
    static int _audioId;
    static float _masterVolume;
    static float _bgmBaseVolume;
    static bool _inited;
};
