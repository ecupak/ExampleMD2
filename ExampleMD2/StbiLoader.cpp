#include "StbiLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


namespace stbiLoader
{
    unsigned char* LoadImage(std::string filename, int& width, int& height, int& nrChannels, const bool setFlip)
    {
        // Load image and return pointer - calling method now owns the memory.
        stbi_set_flip_vertically_on_load(setFlip);
        return stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    }


    void FreeImage(unsigned char* data)
    {
        stbi_image_free(data);
    }
}