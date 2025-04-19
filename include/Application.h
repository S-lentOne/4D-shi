#pragma once

#include "VulkanContext.h"
#include <memory>

class Application {
public:
    Application(int width, int height, const char* title);
    ~Application();

    void run();

private:
    GLFWwindow* window;
    std::unique_ptr<VulkanContext> vulkanContext;

    void initWindow(int width, int height, const char* title);
}; 