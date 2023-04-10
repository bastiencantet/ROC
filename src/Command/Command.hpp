/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Command
*/

#include <vulkan/vulkan_core.h>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <Device/PhysicalDevice.hpp>

#ifndef BB_ROC_COMMAND_HPP
#define BB_ROC_COMMAND_HPP

namespace Rc {
    class Command {
    public:
        static Command &getInstance() {
            static Command instance;
            return instance;
        }

        void createCommandPool(VkDevice &device, VkSurfaceKHR &surface, VkPhysicalDevice &physicalDevice);

        void createCommandBuffers(VkDevice &device);

        void createSyncObjects(VkDevice &device, std::vector<VkSemaphore> &imageAvailableSemaphores,
                               std::vector<VkSemaphore> &renderFinishedSemaphores, std::vector<VkFence> &inFlightFences,
                               std::vector<VkFence> &imagesInFlight);

        void cleanup(VkDevice &device, VkCommandPool &commandPool, std::vector<VkSemaphore> &imageAvailableSemaphores,
                     std::vector<VkSemaphore> &renderFinishedSemaphores, std::vector<VkFence> &inFlightFences);

        VkCommandPool &getCommandPool();

        std::vector<VkCommandBuffer> &getCommandBuffers();

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR &surface);

    private:
        VkCommandPool _commandPool;
        std::vector<VkCommandBuffer> _commandBuffers;

        Command() = default;

        ~Command() = default;
    };
}


#endif //BB_ROC_COMMAND_HPP
