#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace Ui {
    void drawHeader();
    void drawMenu();
    void drawFooter();
    void drawPlayListMenu();
    void showPlayingInfo(const string &name, const string &artist, const string &duration);
}
