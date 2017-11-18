#include "../headers/exceptions.h"

FileIOException::FileIOException(const std::string &filename) {
    this->filename = filename;
}

const char *FileIOException::what() const throw() {

    if (this->filename.empty()) {
        return "Error while process file";
    }

    std::string message = "Error while process \"" + this->filename + "\" file";

    return message.c_str();
}

WAVHeaderFormatException::WAVHeaderFormatException(const std::string &message) {

    this->message = message;

}

const char *WAVHeaderFormatException::what() const throw() {
    return this->message.c_str();
}
