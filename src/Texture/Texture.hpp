/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Texture
*/

#include <string>
#include <vulkan/vulkan.h>

#ifndef BB_ROC_TEXTURE_HPP
#define BB_ROC_TEXTURE_HPP

namespace Rc {
    class Texture {
    public:
        explicit Texture(std::string path);
        ~Texture() = default;
    private:
        std::string _path;
        void loadTexture();
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;
    };
}


#endif //BB_ROC_TEXTURE_HPP
