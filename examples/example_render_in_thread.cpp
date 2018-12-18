//
// Created by xiaozhuai on 2018/12/11.
//
#include <SFML/Graphics.hpp>
#include <oogl/oogl.h>
#include <thread>
#include "FPSCounter.h"

oogl::Texture2D loadTexture(const std::string &file) {
    oogl::Texture2D texture;
    texture.create(
            {
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR,
                    GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE,
                    GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE
            }
    );
    texture.loadFromFile(file);
    return texture;
}

GLfloat vertexCoord[12] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
};

GLfloat textureCoord[12] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
};

bool running = true;
int fps = 0;
bool fpsChanged = false;

void threadEntry(sf::Window *window) {
    FPSCounter fpsCounter;
    fpsCounter.setFpsChangedListener([&](int f) {
        fps = f;
        fpsChanged = true;
    });

    // share context
    window->setActive(true);

    oogl::VertexShader vertexShader;
    vertexShader.create(R"EOF(
attribute vec4 position;
attribute vec2 inputTextureCoordinate;
varying vec2 textureCoordinate;
void main() {
    gl_Position = position;
    textureCoordinate = inputTextureCoordinate;
}
)EOF");

    oogl::FragmentShader fragmentShader;
    fragmentShader.create(R"EOF(
uniform sampler2D inputImageTexture;
varying vec2 textureCoordinate;
void main()
{
    gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
}
)EOF");

    oogl::Program program;
    program.create();
    program.attach(vertexShader, fragmentShader);
    program.link();
    program.validate();
    program.use();

    oogl::Attribute positionAttr = program.getAttribute("position");
    oogl::Attribute inputTextureCoordinateAttr = program.getAttribute("inputTextureCoordinate");
    oogl::Uniform inputImageTexture = program.getUniform("inputImageTexture");

    oogl::Texture2D imgTexture = loadTexture("assets/image/test.png");

    positionAttr.setPointer(vertexCoord);
    inputTextureCoordinateAttr.setPointer(textureCoord);
    inputImageTexture.set(imgTexture, 0);

    while (running) {
        oogl::viewPort(0, 0, window->getSize().x, window->getSize().y);
        oogl::Triangle::drawArrays(6);

        // swap buffer
        window->display();
        fpsCounter.update();
    }
}

int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(1280, 720), __EXAMPLE_TARGET__, sf::Style::Default, sf::ContextSettings(32));
    window.setActive(false);

    std::thread thread(threadEntry, &window);

    while (running) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }

        if (fpsChanged) { // fps changed
            fpsChanged = false;
            window.setTitle(__EXAMPLE_TARGET__ "  fps: " + std::to_string(fps));
        }
    }

    thread.join();
    return 0;
}

