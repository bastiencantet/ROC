#include <iostream>
#include <filesystem>
#include "src/Window/Window.hpp"
#include "enums.hpp"

int main() {
    Rc::IconImage icon("../classique_large.png");

    Rc::Window window(800, 600, "Window test");
    window.setIcon(icon);
    while (!window.shouldClose()) {
        window.pollEvents();
    }
    return 0;
}