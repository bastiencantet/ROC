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
#include <Device/PhysicalDevice.hpp>
#include <Device/LogicalDevice.hpp>
#include "Surface/Surface.hpp"
#include "DescriptorSet/Descriptor.hpp"
#include "Texture/Texture.hpp"

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

        Instance& instance = Instance::getI();


        _instance.initInstance();

        _instance.createSurface(_window);

        instance = _instance;

        Surface& surface = Surface::getInstance();
        surface.createSurface(_window, _instance.getInstance());

        PhysicalDevice& physicalDevice = PhysicalDevice::getInstance();
        physicalDevice.findPhysicalDevice(_instance.getInstance());

        LogicalDevice& logicalDevice = LogicalDevice::getInstance();
        logicalDevice.createLogicalDevice(physicalDevice.getPhysicalDevice(),  surface.getSurface(), _instance);

        SwapChain& swapChain = SwapChain::getInstance();
        swapChain.createSwapChain(logicalDevice.getLogicalDevice(), surface.getSurface(), physicalDevice, _instance , _window);
        swapChain.createImageViews(logicalDevice.getLogicalDevice());
        swapChain.createRenderPass(logicalDevice.getLogicalDevice() , physicalDevice);

        Descriptor& descriptorSet = Descriptor::getInstance();
        descriptorSet.createDescriptorSetLayout(logicalDevice.getLogicalDevice());

        swapChain.createGraphicsPipeline(logicalDevice.getLogicalDevice(), physicalDevice, descriptorSet);

        Command& command = Command::getInstance();
        command.createCommandPool(logicalDevice.getLogicalDevice(), surface.getSurface(),  physicalDevice.getPhysicalDevice());
        command.createCommandBuffers(logicalDevice.getLogicalDevice());

        swapChain.createColorResources(logicalDevice.getLogicalDevice(), physicalDevice);
        swapChain.createDepthResources(logicalDevice.getLogicalDevice(), physicalDevice);
        swapChain.createFramebuffers(logicalDevice.getLogicalDevice(), physicalDevice);

        //TEMP TODO REMOVE
        std::string path = "/Users/bastiencantet/Documents/dev/perso/vulkan/Vulkan-Tuto/viking_room.png";
        Texture texture(path);

        std::cout << "Window created" << std::endl;

    }

    Window::~Window() {
        glfwDestroyWindow(_window);
        glfwTerminate();
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




}
