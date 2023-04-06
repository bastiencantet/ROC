/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Surface
*/

#include "Surface.hpp"
#include <iostream>

VkSurfaceKHR Rc::Surface::getSurface() const {
    return _surface;
}

void Rc::Surface::createSurface(GLFWwindow *window, VkInstance &instance) {
    if (glfwCreateWindowSurface(instance, window, nullptr, &_surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }

}
