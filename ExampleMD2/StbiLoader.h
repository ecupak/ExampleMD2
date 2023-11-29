#pragma once

#include <string>


namespace stbiLoader
{
    unsigned char* LoadImage(std::string filename, int& width, int& height, int& nrChannels, const bool setFlip);


    void FreeImage(unsigned char* data);
}