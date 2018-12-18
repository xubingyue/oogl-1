//
// Created by xiaozhuai on 2018/12/11.
//
#include <SFML/Graphics.hpp>
#include <oogl/oogl.h>

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

int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(1280, 720), __EXAMPLE_TARGET__, sf::Style::Default, sf::ContextSettings(32));

    oogl::FPSCounter fpsCounter;
    fpsCounter.setFpsChangedListener([&window](int fps) {
        window.setTitle(__EXAMPLE_TARGET__ "  fps: " + std::to_string(fps));
    });

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

    oogl::VBO vertexCoordVBO;
    vertexCoordVBO.create();
    vertexCoordVBO.setData(12, vertexCoord, GL_STATIC_DRAW);

    oogl::VBO textureCoordVBO;
    textureCoordVBO.create();
    textureCoordVBO.setData(12, textureCoord, GL_STATIC_DRAW);

    positionAttr.setVBO(vertexCoordVBO);
    inputTextureCoordinateAttr.setVBO(textureCoordVBO);
    inputImageTexture.set(imgTexture, 0);

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
        oogl::clearColor(1.0f, 1.0f, 1.0f, 1.0f);

        oogl::drawTriangleArrays(6);
        window.display();
        fpsCounter.update();
    }

    return 0;
}

