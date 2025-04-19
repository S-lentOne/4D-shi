#include "Application.h"
#include <iostream>

int main() {
    try {
        Application app(1280, 720, "4D-shi");
        app.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
} 