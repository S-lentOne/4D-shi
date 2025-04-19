#include "Application.h"
#include <stdexcept>

Application::Application(int width, int height, const char* title) {
    initWindow(width, height, title);
    vulkanContext = std::make_unique<VulkanContext>(window);
}

Application::~Application() {
    vulkanContext.reset();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initWindow(int width, int height, const char* title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // Render frame
    }

    // Wait for the device to finish operations before cleanup
    vkDeviceWaitIdle(vulkanContext->getDevice());
} 