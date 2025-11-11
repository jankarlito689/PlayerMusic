#pragma once
#include <string>
#include <SFML/Audio.hpp>

using namespace std;

class Player {
private:
    sf::Music music;
    string currentSong;

public:
    bool play(const string &songPath);
    void stop();
    void pause();
    void resume();
    bool isPlaying();
    string getCurrentSong() const;
};