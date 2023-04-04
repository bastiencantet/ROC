/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** IconImage
*/

#include <iostream>
#include <GLFW/glfw3.h>



#ifndef BB_ROC_ICONIMAGE_HPP
#define BB_ROC_ICONIMAGE_HPP


namespace Rc {
    class IconImage {
        public:
            explicit IconImage(const char *path);
            ~IconImage();
            [[nodiscard]] int getWidth() const;
            [[nodiscard]] int getHeight() const;
            [[nodiscard]] int getNrChannels() const;
            [[nodiscard]] unsigned char *getData() const;
            [[nodiscard]] const char *getPath() const;
        private:
            int _width;
            int _height;
            int _nrChannels;
            unsigned char *_data;
            std::string _path;

    };
}


#endif //BB_ROC_ICONIMAGE_HPP
