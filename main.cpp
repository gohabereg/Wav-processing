#include <iostream>

#include "headers/WAV.h"

using namespace std;

int main(int argc, char *argv[])
{

    std::string input_fname  = "../0.wav";
    std::string output_fname = "../out.wav";

    WAV wav1;
    wav1.open(input_fname);
    wav1.info();
    wav1.mono();
    wav1.reverb( 0.500, 0.6f );
    wav1.saveToFile(output_fname);

    return 0;
}
