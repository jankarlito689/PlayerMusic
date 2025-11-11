#include "player.hpp"
#include <iostream>

using namespace std;

bool Player::play(const string &songPath) {
    if (!music.openFromFile(songPath)) {
            cerr << "⚠️  No se pudo abrir: " << songPath << endl;
        return false;
    }

    currentSong = songPath;
    music.play();
    cout << "▶️  Reproduciendo: " << songPath << endl;
    return true;
}

void Player::stop() {
    music.stop();
    cout << "⏹️  Reproducción detenida." << endl;
}

void Player::pause() {
    music.pause();
    cout << "⏸️  Pausa." << endl;
}

void Player::resume() {
    music.play();
    cout << "⏯️  Reanudando..." << endl;
}

bool Player::isPlaying() {
    return music.getStatus() == sf::Music::Playing;
}

string Player::getCurrentSong() const {
    return currentSong;
}
