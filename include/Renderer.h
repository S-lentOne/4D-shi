#pragma once

#include "Window.h"
#include "Grid4D.h"
#include <vulkan/vulkan.h>
#include <vector>

class Renderer {
public:
    Renderer(const Window& window);
    ~Renderer();
    
    void beginFrame();
    void renderGrid(const Grid4D& grid);
    void endFrame();
    
private:
    void createInstance();
    void createSurface();
    void createDevice();
    void createSwapchain();
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    
    const Window& window;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    VkRenderPass renderPass;
    std::vector<VkFramebuffer> swapchainFramebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    size_t currentFrame = 0;
}; 