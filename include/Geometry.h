#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <array>

struct Vertex {
    glm::vec4 pos;     // Position in 4D space (x, y, z, w)
    glm::vec4 color;   // Color (r, g, b, a)
    glm::vec2 texCoord;// Texture coordinates (u, v)

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        // Position
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        // Color
        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        // Texture coordinates
        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

class Tesseract {
public:
    static std::vector<Vertex> getVertices() {
        // Tesseract vertices
        // A tesseract has 16 vertices in 4D space
        return {
            // Front cube (w = -0.5)
            {{-0.5f, -0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // 0
            {{ 0.5f, -0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},  // 1
            {{ 0.5f,  0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},  // 2
            {{-0.5f,  0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},  // 3
            {{-0.5f, -0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},  // 4
            {{ 0.5f, -0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},  // 5
            {{ 0.5f,  0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},  // 6
            {{-0.5f,  0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}},  // 7

            // Back cube (w = 0.5)
            {{-0.5f, -0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // 8
            {{ 0.5f, -0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},  // 9
            {{ 0.5f,  0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},  // 10
            {{-0.5f,  0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},  // 11
            {{-0.5f, -0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},  // 12
            {{ 0.5f, -0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},  // 13
            {{ 0.5f,  0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},  // 14
            {{-0.5f,  0.5f,  0.5f,  0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}}   // 15
        };
    }

    static std::vector<uint16_t> getIndices() {
        // Tesseract indices
        // We'll draw it as a wireframe initially
        return {
            // Front cube
            0, 1,  1, 2,  2, 3,  3, 0,  // Front face edges
            4, 5,  5, 6,  6, 7,  7, 4,  // Back face edges
            0, 4,  1, 5,  2, 6,  3, 7,  // Connecting edges

            // Back cube
            8, 9,  9, 10, 10, 11, 11, 8,  // Front face edges
            12, 13, 13, 14, 14, 15, 15, 12,  // Back face edges
            8, 12, 9, 13, 10, 14, 11, 15,  // Connecting edges

            // Connections between cubes
            0, 8,  1, 9,  2, 10, 3, 11,  // Front face connections
            4, 12, 5, 13, 6, 14, 7, 15   // Back face connections
        };
    }
}; 