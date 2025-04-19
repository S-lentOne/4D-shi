#pragma once

#include <glm/glm.hpp>
#include <vector>

class Grid4D {
public:
    Grid4D(float size, float resolution);
    
    void update();
    const std::vector<glm::vec4>& getPoints() const { return points; }
    
private:
    float size;
    float resolution;
    std::vector<glm::vec4> points;
    float wOffset = 0.0f;
    const float wSpeed = 0.01f;
    
    void generateGrid();
    glm::vec3 projectTo3D(const glm::vec4& point4D) const;
}; 