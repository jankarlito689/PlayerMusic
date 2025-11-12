#pragma once
#include <string>
#include <vector>
#include "../Models/song.hpp"
using namespace std;

class File {
public:
        vector<Song> readPlaylist(const string &path);
};