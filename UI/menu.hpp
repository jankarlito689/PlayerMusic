#pragma once
#include <iostream>
#include <string>
#include "../List/circularList.hpp"
using namespace std;

namespace Ui {
    void drawHeader();
    void drawMenu();
    void drawFooter();
    void drawProgressBar(float current, float total);
    void drawPlayListMenu();
    void showPlayingInfo(const string &name, const string &artist, const string &duration);
    void drawPlaylist(const CircularList &playlist, Node *currentPlaying);
}
