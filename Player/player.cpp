#include "player.hpp"
#include <iostream>

using namespace std;

bool Player::play(const Song &song) {
    //Verificamos la ruta de la canción
    if(song.path.empty()){
        cerr << "⚠️  Ruta vacía para la canción: " << song.name << endl;
        return false;
    }
    if (!music.openFromFile(song.path)) {
            cerr << "⚠️  No se pudo abrir: " << song.path << endl;
        return false;
    }// Obtener duración de la canción
    if (temp.openFromFile(song.path)) {
            sf::Time t = temp.getDuration();
            int s = (int)t.asSeconds();
            int min = s / 60;
            s %= 60;
            const_cast<Song&>(song).duration = to_string(min) + ":" + (s < 10 ? "0" : "") + to_string(s);
        } else {
            const_cast<Song&>(song).duration = "00:00";
        }
    currentSong = song;
    music.play();
    cout << "▶️  Reproduciendo: " << song.name << " - " << song.artist << " (" << song.duration << ")" << endl;
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
    return currentSong.name;
}
