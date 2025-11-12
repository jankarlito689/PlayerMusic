// Models/song.hpp
#pragma once
#include <string>

using namespace std;

struct Song {
    int id;
    string name;
    string artist;
    string album;
    string duration;
    string path;
};
