/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** SwapChain
*/

#include <vulkan/vulkan.h>
#include <Device/PhysicalDevice.hpp>
#include <Surface/Surface.hpp>
#include <Instance/Instance.hpp>
#include <DescriptorSet/Descriptor.hpp>
#include "Vertex/Vertex.hpp"
#include "Utils/files.hpp"
#include <functional>

#ifndef BB_ROC_SWAPCHAIN_HPP
#define BB_ROC_SWAPCHAIN_HPP

namespace Rc {
    class SwapChain {
    public:
        static SwapChain& getInstance() {
            static SwapChain instance;
            return instance;
        }
        [[nodiscard]] std::vector<VkImage>& getSwapChainImages() const;
        [[nodiscard]] VkFormat& getSwapChainImageFormat() const;
        [[nodiscard]] VkExtent2D& getSwapChainExtent() const;
        [[nodiscard]] VkSwapchainKHR& getSwapChain() const;
        [[nodiscard]] std::vector<VkImageView> getSwapChainImageViews() const;
        [[nodiscard]] VkRenderPass& getRenderPass() const;
        void createSwapChain(VkDevice &device, VkSurfaceKHR &surface, Rc::PhysicalDevice &physicalDevice, Rc::Instance &instance, GLFWwindow *window);
        void createImageViews(VkDevice &device);
        void createRenderPass(VkDevice &device, PhysicalDevice &physicalDevice);
        void createGraphicsPipeline(VkDevice &device, PhysicalDevice &physicalDevice, Descriptor &descriptor);
    private:
        VkSwapchainKHR _swapChain;
        std::vector<VkImage> _swapChainImages;
        std::vector<VkImageView> _swapChainImageViews;
        VkFormat _swapChainImageFormat;
        VkExtent2D _swapChainExtent;
        VkRenderPass _renderPass;
        VkFormat findDepthFormat(PhysicalDevice &physicalDevice);
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, PhysicalDevice &physicalDevice);
        ~SwapChain() = default;
        SwapChain() = default;
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR &surface);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities , GLFWwindow *window);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR &surface);
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, u_int32_t mipLev, VkDevice &device);

        //Pipeline
        VkPipelineLayout _pipelineLayout;
        VkPipeline _graphicsPipeline;

        VkShaderModule createShaderModule(const std::vector<char> &code , VkDevice &device);
    };
}


#endif //BB_ROC_SWAPCHAIN_HPP
