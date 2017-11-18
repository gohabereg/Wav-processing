#pragma once

#include <vector>
#include "WAVHeader.h"

class WAV {

public:

    void open(const std::string& filename) throw(FileIOException);

    void mono();

    void reverb(double delay, float decay);

    void info() const;

    int getSampleRate() const;
    int getChannelsCount() const;
    bool isStereo() const;

    void saveToFile(const std::string& filename);

    void save();


private:
    WAVHeader header;

    std::string filename;

    std::vector<std::vector<short>> channelsData;

    void extractChannelsData(const std::string& filename) throw(FileIOException);

};

