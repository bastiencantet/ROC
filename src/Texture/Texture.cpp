/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Texture
*/

#include "Texture.hpp"
#include "stb_image.h"
#include <cmath>
#include <iostream>
#include "Device/LogicalDevice.hpp"
#include "Device/PhysicalDevice.hpp"
#include "Allocator/Allocator.hpp"
#include "Instance/Instance.hpp"

void Rc::Texture::loadTexture() {
    int texWidth, texHeight, texChannels;

    LogicalDevice& logicalDevice = LogicalDevice::getInstance();
    VkDevice device = logicalDevice.getLogicalDevice();
    PhysicalDevice& physicalDevice = PhysicalDevice::getInstance();
    Instance &instance = Instance::getI();

    if (device == nullptr) {
        throw std::runtime_error("device is null");
    }

    if (physicalDevice.getPhysicalDevice() == nullptr) {
        throw std::runtime_error("physical device is null");
    }

    if (logicalDevice.getLogicalDevice() == nullptr) {
        throw std::runtime_error("logical device is null");
    }
    if (instance.getInstance() == nullptr) {
        throw std::runtime_error("instance is null");
    }


    stbi_uc* pixels = stbi_load(_path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
   // mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;
    VkDeviceSize imageSize = texWidth * texHeight * 4;

    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

// Create an instance of the Allocator class
    Allocator allocator(instance.getInstance(), physicalDevice.getPhysicalDevice() , device);

// Create a staging buffer
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferMemory;
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = imageSize;
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    allocator.createBuffer(bufferInfo, VMA_MEMORY_USAGE_CPU_ONLY, stagingBuffer, stagingBufferMemory);

// Copy pixel data to the staging buffer
    void* data;
    vmaMapMemory(allocator.getAllocator(), stagingBufferMemory, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vmaUnmapMemory(allocator.getAllocator(), stagingBufferMemory);

// Free staging buffer memory using the Allocator class
    allocator.destroyBuffer(stagingBuffer, stagingBufferMemory);

}

Rc::Texture::Texture(std::string path) {
    _path = path;
    loadTexture();
}
