#pragma once

#include <cstdint>
#include <string>
#include "exceptions.h"

class WAVHeader {
public:
    void read(const std::string& filename) throw(FileIOException);

    void setToZero();

    void print() const;

    void fill(int channelsCount, int sampleRate, int samplesCountPerChannel) throw(WAVHeaderFormatException);

    void check(size_t fileSize) const throw(WAVHeaderFormatException);

    struct HeaderData {

        char chunkId[4];

        uint32_t chunkSize;

        char format[4];

        char subchunk1Id[4];

        uint32_t subchunk1Size;

        uint16_t audioFormat;

        uint16_t numChannels;

        uint32_t sampleRate;

        uint32_t byteRate;

        uint16_t blockAlign;

        uint16_t bitsPerSample;

        char subchunk2Id[4];

        uint32_t subchunk2Size;

    };

    HeaderData* data = new HeaderData;

    const int supportedBitsPerSample = 16;
    const int subchunk1Size = 16;
    const int supportedAudioFormat = 1;
    const int headerSize = 44;

};
