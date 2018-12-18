//
// Created by xiaozhuai on 2018/12/11.
//
#include <SFML/Graphics.hpp>
#include <oogl/oogl.h>
#include "FPSCounter.h"

oogl::Texture2D loadTexture(const std::string &file) {
    oogl::Texture2D texture;
    texture.create();
    texture.bind();
    texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    texture.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    texture.loadFromFile(file);
    texture.unbind();
    return texture;
}

oogl::Framebuffer genFramebufferWithTexture(GLsizei width, GLsizei height) {

    oogl::Texture2D texture;
    texture.create();
    texture.bind();
    texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    texture.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    texture.setData(width, height, NULL);
    texture.unbind();

    oogl::Framebuffer framebuffer;
    framebuffer.create();
    framebuffer.attach(texture);

    return framebuffer;
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

oogl::Program init_program_1() {
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

    return program;
}

oogl::Program init_program_2() {
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

    oogl::Texture2D imgTexture = oogl::Texture2D::EMPTY;

    positionAttr.setPointer(vertexCoord);
    inputTextureCoordinateAttr.setPointer(textureCoord);
    inputImageTexture.set(imgTexture, 1);

    return program;
}

int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(1280, 720), __EXAMPLE_TARGET__, sf::Style::Default, sf::ContextSettings(32));

    FPSCounter fpsCounter;
    fpsCounter.setFpsChangedListener([&window](int fps) {
        window.setTitle(__EXAMPLE_TARGET__ "  fps: " + std::to_string(fps));
    });

    oogl::Program program1 = init_program_1();
    oogl::Program program2 = init_program_2();

    oogl::Framebuffer framebuffer = genFramebufferWithTexture(1280, 720);

    program2.getUniform("inputImageTexture").set(framebuffer.getTexture(), 1);

    bool running = true;
    while (running) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }

        oogl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        oogl::clearColor(1.0f, 1.0f, 1.0f, 1.0f);

        program1.use();
        framebuffer.bind();
        oogl::viewPort(0, 0, 1280, 720);
        oogl::drawTriangleArrays(6);

        program2.use();
        oogl::Framebuffer::SCREEN.bind();
        oogl::viewPort(0, 0, window.getSize().x, window.getSize().y);
        oogl::drawTriangleArrays(6);

        window.display();
        fpsCounter.update();
    }

    return 0;
}

