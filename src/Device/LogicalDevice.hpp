/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** LogicalDevice
*/

#include <vulkan/vulkan.h>
#include <optional>
#include <vector>
#include <set>
#include "Instance/Instance.hpp"
#include "Device/PhysicalDevice.hpp"

#ifndef BB_ROC_LOGICALDEVICE_HPP
#define BB_ROC_LOGICALDEVICE_HPP

namespace Rc {


    class LogicalDevice {
    public:
        static LogicalDevice& getInstance() {
            static LogicalDevice instance;
            return instance;
        }
        [[nodiscard]] VkDevice &getLogicalDevice() const;
        void createLogicalDevice(VkPhysicalDevice &physicalDevice, VkSurfaceKHR &surface, Rc::Instance &instance);

    private:
        VkDevice _logicalDevice;
        ~LogicalDevice() = default;
        LogicalDevice() = default;
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device , VkSurfaceKHR &surface);
        const bool _enableValidationLayers = true;
    };
}


#endif //BB_ROC_LOGICALDEVICE_HPP
