/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Window
*/

#include <GLFW/glfw3.h>
#include "Images/IconImage.hpp"
#include <Vulkan/vulkan.h>

#ifndef BB_ROC_WINDOW_HPP
#define BB_ROC_WINDOW_HPP





namespace Rc {


    enum  WindowProperty {
        CLOSE_BUTTON = 0,
        MINIMIZE_BUTTON = 1,
        MAXIMIZE_BUTTON = 2,
        RESIZABLE = 3,
        DECORATED = 4,
    };

    class Window {
        public:
            Window(int width, int height, const char *title);
            ~Window();
            int shouldClose();
            void pollEvents();
            void close();
            GLFWwindow *getWindow();
            bool isOpen();
            void setIcon(IconImage &icon);
            void setProperty(WindowProperty property, int value);
            void setTitle(const char *title);


        private:
            static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
            static bool checkValidationLayerSupport();
            bool checkMissingExtensions() const;
            [[nodiscard]] std::vector<const char *> getRequiredExtensions() const;
            void initInstance();

            int _width;
            int _height;
            const char *_title;
            GLFWwindow *_window;
            VkInstance _instance;





            bool _validationLayersEnabled = true;
    };
}


#endif //BB_ROC_WINDOW_HPP
