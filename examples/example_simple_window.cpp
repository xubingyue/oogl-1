//
// Created by xiaozhuai on 2018/12/10.
//
#include <SFML/Window.hpp>
#include <oogl/oogl.h>
#include "FPSCounter.h"

int main(int argc, char **argv) {
    sf::Window window(sf::VideoMode(1280, 720), __EXAMPLE_TARGET__);

    FPSCounter fpsCounter;
    fpsCounter.setFpsChangedListener([&window](int fps) {
        window.setTitle(__EXAMPLE_TARGET__ "  fps: " + std::to_string(fps));
    });

    bool running = true;
    while (running) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::Resized:
                    oogl::viewPort(0, 0, window.getSize().x, window.getSize().y);
                    break;
                default:
                    break;
            }
        }

        oogl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        oogl::clearColor(0.0f, 1.0f, 1.0f, 1.0f);
        //or
        //oogl::clearColor(0xffffff00);

        window.display();
        fpsCounter.update();
    }

    return 0;
}