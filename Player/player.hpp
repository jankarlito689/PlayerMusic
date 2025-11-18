#pragma once
#include <string>
#include "../Models/song.hpp"
#include <SFML/Audio.hpp>

using namespace std;

class Player {
private:
    sf::Music music;
    sf::Music temp;
    Song currentSong;

public:
    bool play(const Song &song);
    void stop();
    void pause();
    void resume();
    bool isPlaying();
    float getPlayingOffset();
    float getDuration();
    string getCurrentSong() const;
};