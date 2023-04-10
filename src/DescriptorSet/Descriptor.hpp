/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** DescriptorSet
*/

#ifndef BB_ROC_DESCRIPTOR_HPP
#define BB_ROC_DESCRIPTOR_HPP

#include <vulkan/vulkan_core.h>
#include <vector>
#include <iostream>

namespace Rc {
    class Descriptor {
        public:
          static Descriptor& getInstance() {
              static Descriptor instance;
              return instance;
          }
            void createDescriptorSetLayout(VkDevice &device);
            void createDescriptorPool(VkDevice &device, uint32_t swapChainImagesSize);
            void createDescriptorSets(VkDevice &device, VkDescriptorSetLayout &descriptorSetLayout, VkDescriptorPool &descriptorPool, std::vector<VkImageView> &swapChainImageViews, VkImageLayout &imageLayout, VkSampler &textureSampler, VkBuffer &uniformBuffer, VkDeviceMemory &uniformBufferMemory, uint32_t swapChainImagesSize);
            void cleanup(VkDevice &device, VkDescriptorPool &descriptorPool, VkDescriptorSetLayout &descriptorSetLayout);
            VkDescriptorSetLayout &getDescriptorSetLayout();
            VkDescriptorPool &getDescriptorPool();
            std::vector<VkDescriptorSet> &getDescriptorSets();
        private:
            VkDescriptorSetLayout _descriptorSetLayout;
            VkDescriptorPool _descriptorPool;
            std::vector<VkDescriptorSet> _descriptorSets;
            Descriptor() = default;
            ~Descriptor() = default;
    };
}



#endif //BB_ROC_DESCRIPTOR_HPP
