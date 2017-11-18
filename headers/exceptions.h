#pragma once
#include <string>
#include <exception>

class FileIOException : std::exception {
public:

    FileIOException() = default;

    explicit FileIOException(const std::string &filename);

    const char* what() const throw() override;

private:
    std::string filename;

};

class WAVHeaderFormatException : std::exception {

public:
    WAVHeaderFormatException() = default;

    explicit WAVHeaderFormatException(const std::string &message);

    const char* what() const throw() override;

private:
    std::string message = "Wrong WAV header format.";

};