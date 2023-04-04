/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** IconImage
*/

#include "IconImage.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

namespace Rc {
    IconImage::IconImage(const char *path) {
        stbi_set_flip_vertically_on_load(true);
        _data = stbi_load(path, &_width, &_height, &_nrChannels, 0);
        if (_data) {
            std::cout << "Image loaded" << std::endl;
        } else {
            std::cout << "Failed to load image" << std::endl;
        }
        _path = path;
    }

    IconImage::~IconImage() {
        stbi_image_free(_data);
    }

    int IconImage::getWidth() const {
        return _width;
    }

    int IconImage::getHeight() const {
        return _height;
    }

    int IconImage::getNrChannels() const {
        return _nrChannels;
    }

    unsigned char *IconImage::getData() const {
        return _data;
    }

    const char *IconImage::getPath() const {
        return _path.c_str();
    }
}

