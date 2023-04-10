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
        void createColorResources(VkDevice &device, PhysicalDevice &physicalDevice);
        void createDepthResources(VkDevice &device, PhysicalDevice &physicalDevice);
        void createFramebuffers(VkDevice &device, PhysicalDevice &physicalDevice);
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
        static VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, u_int32_t mipLev, VkDevice &device);


        //Pipeline
        VkPipelineLayout _pipelineLayout;
        VkPipeline _graphicsPipeline;

        //Color

        void createImage(uint32_t width, uint32_t height, u_int32_t mipLev , VkSampleCountFlagBits numSamples ,VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, VkDevice &device);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, PhysicalDevice &physicalDevice);
        VkImageView colorImageView;
        VkImage colorImage;
        VkDeviceMemory colorImageMemory;
        VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

        //Depth
        VkImageView depthImageView;
        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkDevice &device, PhysicalDevice &physicalDevice);


        //Framebuffers
        std::vector<VkFramebuffer> _swapChainFramebuffers;



        VkShaderModule createShaderModule(const std::vector<char> &code , VkDevice &device);
    };
}


#endif //BB_ROC_SWAPCHAIN_HPP
