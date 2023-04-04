/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Window
*/

#include "Window.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>


#ifdef __APPLE__
extern "C" void disableMinimizeButton(GLFWwindow *window);
extern "C" void disableMaximizeButton(GLFWwindow *window);
extern "C" void disableCloseButton(GLFWwindow *window);
extern "C" void hideMinimizeButton(GLFWwindow *window);
extern "C" void hideMaximizeButton(GLFWwindow *window);
extern "C" void hideCloseButton(GLFWwindow *window);
extern "C" void setAppIcon(GLFWwindow *window, const char *iconFilePath);
extern "C" void makeWindowNonResizable(GLFWwindow *window);
extern "C" void makeWindowWithoutDecorations(GLFWwindow *window);
#endif


const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

namespace Rc {

    Window::Window(int width, int height, const char *title) {
        _width = width;
        _height = height;
        _title = title;
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        _window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
        glfwSetWindowUserPointer(_window, this);
        glfwSetFramebufferSizeCallback(_window, framebufferResizeCallback);
        initInstance();
    }

    Window::~Window() {
        std::cout << "Window destroyed" << std::endl;
    }


    void Window::close() {
        std::cout << "Window closed" << std::endl;
    }

    bool Window::isOpen() {
        return true;
    }

    GLFWwindow *Window::getWindow() {
        return _window;
    }

    void Window::framebufferResizeCallback(GLFWwindow *window, int width, int height) {

    }

    int Window::shouldClose() {
        return glfwWindowShouldClose(_window);
    }

    void Window::pollEvents() {
        glfwPollEvents();
    }

    void Window::setIcon(IconImage &icon) {
        setAppIcon(_window, icon.getPath());
    }

    void Window::setProperty(WindowProperty property, int value) {
        glfwMakeContextCurrent(_window);
        switch (property) {
            case CLOSE_BUTTON:
                if (value == 1) {
                    disableCloseButton(_window);
                } else if (value == 0) {
                    hideCloseButton(_window);
                }
                break;
            case MINIMIZE_BUTTON:
                if (value == 1) {
                    disableMinimizeButton(_window);
                } else if (value == 0) {
                    hideMinimizeButton(_window);
                }
                break;
            case MAXIMIZE_BUTTON:
                if (value == 1) {
                    disableMaximizeButton(_window);
                } else if (value == 0) {
                    hideMaximizeButton(_window);
                }
                break;

            case RESIZABLE:
                if (value == 0) {
                    makeWindowNonResizable(_window);
                }
                break;

            case DECORATED:
                if (value == 0) {
                    makeWindowWithoutDecorations(_window);
                }
                break;
        }
    }

    void Window::setTitle(const char *title) {
        glfwSetWindowTitle(_window, title);
    }

    bool Window::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char *layerName: validationLayers) {
            bool layerFound = false;

            for (const auto &layerProperties: availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }


    std::vector<const char *> Window::getRequiredExtensions() const {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        //add debug extension

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (_validationLayersEnabled) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
            extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        }

        //print extensions
        for (const auto &extension: extensions) {
            //LOG(INFO) << "Required extension: " << extension;
        }

        return extensions;
    }

    bool Window::checkMissingExtensions() const {
        // Check for missing extensions
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::vector<const char *> missingExtensions;
        for (const auto &extension: getRequiredExtensions()) {
            bool found = false;
            for (const auto &availableExtension: extensions) {
                if (strcmp(extension, availableExtension.extensionName) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                missingExtensions.push_back(extension);
            }
        }
        if (!missingExtensions.empty()) {
            //  LOG(ERROR) << "Missing extensions:";
            for (const auto &extension: missingExtensions) {
                // LOG(ERROR) << extension;
            }
            return false;
        }
        return true;
    }

    void Window::initInstance() {
        if (_validationLayersEnabled && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        if (!checkMissingExtensions()) {
            throw std::runtime_error("Missing extension");
        }

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (_validationLayersEnabled) {
            debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            createInfo.pNext = &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

    }



}
