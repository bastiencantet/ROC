/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** shared
*/

#ifndef BB_ROC_SHARED_HPP
#define BB_ROC_SHARED_HPP

#include <iostream>
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

#endif //BB_ROC_SHARED_HPP
