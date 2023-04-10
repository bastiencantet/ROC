/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Instance
*/

#ifndef BB_ROC_INSTANCE_HPP
#define BB_ROC_INSTANCE_HPP

#include <iostream>
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <cstring>
#include <GLFW/glfw3.h>


namespace Rc {
class Instance {
    public:
        static Instance &getI() {
            static Instance instance;
            return instance;
        }
        Instance() = default;
        ~Instance() = default;
    void initInstance();
    void createSurface(GLFWwindow *window);
    VkInstance &getInstance();
    VkSurfaceKHR &getSurface();
    VkQueue &getGraphicsQueue();
    VkQueue &getPresentQueue();
private:
    static bool checkValidationLayerSupport();
    [[nodiscard]] bool checkMissingExtensions() const;
    [[nodiscard]] std::vector<const char *> getRequiredExtensions() const;

    void setupDebugMessenger();
    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger);
    static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) ;
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData);




        VkInstance _instance;
        VkDebugUtilsMessengerEXT _debugMessenger{};
        bool _validationLayersEnabled = true;
        VkSurfaceKHR _surface;
        VkQueue _graphicsQueue;
        VkQueue _presentQueue;
};
}


#endif //BB_ROC_INSTANCE_HPP
