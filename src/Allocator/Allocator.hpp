/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Allocator
*/

#include <vulkan/vulkan.h>
#include "Device/PhysicalDevice.hpp"
#include <vk_mem_alloc.h>

#ifndef BB_ROC_ALLOCATOR_HPP
#define BB_ROC_ALLOCATOR_HPP

namespace Rc {
    class Allocator {
    public:
        Allocator(VkInstance &instance, VkPhysicalDevice &physicalDevice, VkDevice &device) : m_device(device) {
            VmaAllocatorCreateInfo allocatorInfo = {};
            allocatorInfo.physicalDevice = physicalDevice;
            allocatorInfo.device = device;
            allocatorInfo.instance = instance;

            if (vmaCreateAllocator(&allocatorInfo, &m_allocator) != VK_SUCCESS) {
                throw std::runtime_error("failed to create VMA allocator!");
            }
        }

        ~Allocator() {
            vmaDestroyAllocator(m_allocator);
        }

        void allocateMemory(VkMemoryRequirements memRequirements, VkMemoryPropertyFlags properties, VkDeviceMemory& memory) {
            VmaAllocationCreateInfo allocInfo = {};
            allocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
            if (properties & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
                allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
            }
            if (properties & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                allocInfo.flags |= VMA_ALLOCATION_CREATE_MAPPED_BIT;
            }

            VmaAllocation allocation;
            if (vmaAllocateMemory(m_allocator, &memRequirements, &allocInfo, &allocation, nullptr) != VK_SUCCESS) {
                throw std::runtime_error("failed to allocate memory with VMA!");
            }

            // Optional: set debug name for the memory allocation
            // vmaSetAllocationUserData(m_allocator, allocation, &debugName);
            // vmaSetAllocationName(m_allocator, allocation, debugName.c_str());
        }

        void createBuffer(VkBufferCreateInfo bufferInfo, VmaMemoryUsage memoryUsage, VkBuffer& buffer, VmaAllocation& allocation, const char* debugName = nullptr) {
            VmaAllocationCreateInfo allocInfo = {};
            allocInfo.usage = memoryUsage;

            if (vmaCreateBuffer(m_allocator, &bufferInfo, &allocInfo, &buffer, &allocation, nullptr) != VK_SUCCESS) {
                throw std::runtime_error("failed to create buffer with VMA!");
            }

            // Optional: set debug name for the memory allocation
            // vmaSetAllocationUserData(m_allocator, allocation, &debugName);
            // vmaSetAllocationName(m_allocator, allocation, debugName.c_str());

        }

        void destroyBuffer(VkBuffer buffer, VmaAllocation allocation) {
            vmaDestroyBuffer(m_allocator, buffer, allocation);
        }

        void freeMemory(VmaAllocation memory) {
            vmaFreeMemory(m_allocator, memory);
        }

        void* mapMemory(VmaAllocation allocation) {
            void* data;
            vmaMapMemory(m_allocator, allocation, &data);
            return data;
        }

        void unmapMemory(VmaAllocation memory) {
            vmaUnmapMemory(m_allocator, memory);
        }

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
            VkPhysicalDeviceMemoryProperties memProperties;
            PhysicalDevice &physicalDevice = PhysicalDevice::getInstance();
            vkGetPhysicalDeviceMemoryProperties(physicalDevice.getPhysicalDevice(), &memProperties);

            for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
                if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                    return i;
                }
            }

            throw std::runtime_error("failed to find suitable memory type!");
        }

        VmaAllocator getAllocator();

    private:
        VmaAllocator m_allocator;
        VkDevice m_device;
    };
}


#endif //BB_ROC_ALLOCATOR_HPP
