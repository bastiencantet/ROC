/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Surface
*/

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#ifndef BB_ROC_SURFACE_HPP
#define BB_ROC_SURFACE_HPP

namespace Rc {
    class Surface {
    public:
        static Surface& getInstance() {
            static Surface instance;
            return instance;
        }
    [[nodiscard]] VkSurfaceKHR& getSurface() const;
    void createSurface(GLFWwindow *window , VkInstance &instance);
    private:
        VkSurfaceKHR _surface;
        ~Surface() = default;
        Surface() = default;
    };
}


#endif //BB_ROC_SURFACE_HPP
