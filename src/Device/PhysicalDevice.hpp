/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** PhysicalDevice
*/

#ifndef BB_ROC_PHYSICALDEVICE_HPP
#define BB_ROC_PHYSICALDEVICE_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include "shared.hpp"

namespace Rc {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class PhysicalDevice {
    public:
        static PhysicalDevice& getInstance() {
            static PhysicalDevice instance;
            return instance;
        }

        [[nodiscard]] VkPhysicalDevice getPhysicalDevice() const;
        void findPhysicalDevice(VkInstance &instance);
    private:
        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        [[nodiscard]] int rateDeviceSuitability(VkPhysicalDevice device) const;
        [[nodiscard]] VkSampleCountFlagBits getMaxUsableSampleCount() const;
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice pT);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        ~PhysicalDevice() = default;
        PhysicalDevice() = default;


        VkPhysicalDevice _physicalDevice{};


    };
}

#endif //BB_ROC_PHYSICALDEVICE_HPP
