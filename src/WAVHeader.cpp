#include "../headers/WAVHeader.h"
#include "../headers/exceptions.h"
#include <fstream>
#include <iostream>

void WAVHeader::read(const std::string &filename) throw(FileIOException) {

    this->setToZero();

    int headerDataSize = sizeof(HeaderData);

    std::ifstream input(filename, std::ifstream::binary);

    if (!input.good()) {
        throw FileIOException(filename);
    }

    input.read((char *)this->data, headerDataSize);

    input.seekg(0, input.end);

    size_t length = input.tellg();

    this->check(length);

}

void WAVHeader::setToZero() {
    memset(this->data, 0, sizeof(HeaderData));
}

void WAVHeader::print() const {

    std::cout << "ChunkID: " << this->data->chunkId << std::endl;
    std::cout << "ChunkSize: " << this->data->chunkSize << std::endl;
    std::cout << "Format: " << this->data->format << std::endl;
    std::cout << "Subchunk1ID: " << this->data->subchunk1Id << std::endl;
    std::cout << "Subchunk1Size: " << this->data->subchunk1Size << std::endl;
    std::cout << "AudioFormat: " << this->data->audioFormat << std::endl;
    std::cout << "NumChannels: " << this->data->numChannels << std::endl;
    std::cout << "SampleRate: " << this->data->sampleRate << std::endl;
    std::cout << "ByteRate: " << this->data->byteRate << std::endl;
    std::cout << "BlockAlign: " << this->data->blockAlign << std::endl;
    std::cout << "BitsPerSample: " << this->data->bitsPerSample << std::endl;
    std::cout << "Subchunk2ID: " << this->data->subchunk2Id << std::endl;
    std::cout << "Subchunk2Size: " << this->data->subchunk2Size << std::endl;

}

void WAVHeader::check(size_t fileSize) const throw(WAVHeaderFormatException) {

    if ( this->data->chunkId[0] != 0x52 ||
         this->data->chunkId[1] != 0x49 ||
         this->data->chunkId[2] != 0x46 ||
         this->data->chunkId[3] != 0x46 )
    {
        throw WAVHeaderFormatException("Header RIFF Error");
    }

    if ( this->data->chunkSize != fileSize - 8 ) {
        throw WAVHeaderFormatException("Invalid WAV header size");
    }

    if ( this->data->format[0] != 0x57 ||
         this->data->format[1] != 0x41 ||
         this->data->format[2] != 0x56 ||
         this->data->format[3] != 0x45 )
    {
        throw WAVHeaderFormatException("Header WAVE Error");
    }

    if ( this->data->subchunk1Id[0] != 0x66 ||
         this->data->subchunk1Id[1] != 0x6d ||
         this->data->subchunk1Id[2] != 0x74 ||
         this->data->subchunk1Id[3] != 0x20 )
    {
        throw WAVHeaderFormatException("Header FMT Error");
    }

    if ( this->data->audioFormat != this->supportedAudioFormat ) {
        throw WAVHeaderFormatException("Header is not PCM");
    }

    if ( this->data->subchunk1Size != this->subchunk1Size ) {
        throw WAVHeaderFormatException("Wrong SubChunk1 size");
    }

    if ( this->data->byteRate !=
         this->data->sampleRate * this->data->numChannels * this->data->bitsPerSample / 8 ) {
        throw WAVHeaderFormatException("Wrong ByteRate");
    }

    if ( this->data->blockAlign != this->data->numChannels * this->data->bitsPerSample / 8 ) {
        throw WAVHeaderFormatException("Wrong block align");
    }

    if ( this->data->subchunk2Id[0] != 0x64 ||
         this->data->subchunk2Id[1] != 0x61 ||
         this->data->subchunk2Id[2] != 0x74 ||
         this->data->subchunk2Id[3] != 0x61 )
    {
        throw WAVHeaderFormatException("Header FMT Error");
    }

    if ( this->data->subchunk2Size != fileSize - this->headerSize) {
        throw WAVHeaderFormatException("Wrong SubChunk2 size");
    }

    if ( this->data->bitsPerSample != this->supportedBitsPerSample ) {
        throw WAVHeaderFormatException("Unsupported Format");
    }

}

void WAVHeader::fill(int channelsCount, int sampleRate, int samplesCountPerChannel) throw(WAVHeaderFormatException) {

    if ( channelsCount < 1 ) {
        throw WAVHeaderFormatException("Bad input");
    }

    this->data->chunkId[0] = 0x52;
    this->data->chunkId[1] = 0x49;
    this->data->chunkId[2] = 0x46;
    this->data->chunkId[3] = 0x46;

    this->data->format[0] = 0x57;
    this->data->format[1] = 0x41;
    this->data->format[2] = 0x56;
    this->data->format[3] = 0x45;

    this->data->subchunk1Id[0] = 0x66;
    this->data->subchunk1Id[1] = 0x6d;
    this->data->subchunk1Id[2] = 0x74;
    this->data->subchunk1Id[3] = 0x20;

    this->data->subchunk2Id[0] = 0x64;
    this->data->subchunk2Id[1] = 0x61;
    this->data->subchunk2Id[2] = 0x74;
    this->data->subchunk2Id[3] = 0x61;

    this->data->audioFormat   = this->supportedAudioFormat;
    this->data->subchunk1Size = this->subchunk1Size;
    this->data->bitsPerSample = this->supportedBitsPerSample;


    int fileSize = this->headerSize + channelsCount * (this->supportedBitsPerSample / 8) * samplesCountPerChannel;
    
    this->data->sampleRate = sampleRate;
    this->data->numChannels = channelsCount;

    this->data->chunkSize = fileSize - 8;
    this->data->subchunk2Size = fileSize - this->headerSize;

    this->data->byteRate = this->data->sampleRate * this->data->numChannels * this->data->bitsPerSample / 8;
    this->data->blockAlign = this->data->numChannels * this->data->bitsPerSample / 8;

}
