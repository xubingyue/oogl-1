//
// Created by xiaozhuai on 2018/12/11.
//
#include <SFML/Graphics.hpp>
#include <oogl/oogl.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include "FPSCounter.h"

oogl::Texture2D newTexture(GLsizei width, GLsizei height) {
    oogl::Texture2D texture;
    texture.create(
            {
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR,
                    GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE,
                    GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE
            }
    );
    texture.setData(width, height, NULL);
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
    cv::Mat frameBGR;
    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    cv::VideoCapture capture(deviceID + apiID);
    if (!capture.isOpened()) {
        printf("Error: initialize camera capture failed");
        return 1;
    }

    GLsizei width = static_cast<GLsizei>(capture.get(cv::CAP_PROP_FRAME_WIDTH));
    GLsizei height = static_cast<GLsizei>(capture.get(cv::CAP_PROP_FRAME_HEIGHT));

    cv::Mat frameRGBA = cv::Mat(height, width, CV_8UC4);
    cv::Mat frameRGBAFlipped = cv::Mat(height, width, CV_8UC4);

    sf::RenderWindow window;
    window.create(sf::VideoMode(width, height), __EXAMPLE_TARGET__, sf::Style::Default, sf::ContextSettings(32));

    FPSCounter fpsCounter;
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

    oogl::Texture2D imgTexture = newTexture(width, height);

    positionAttr.setPointer(vertexCoord);
    inputTextureCoordinateAttr.setPointer(textureCoord);

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

        capture.read(frameBGR);
        if (frameBGR.empty()) {
            printf("Error: blank frameBGR grabbed");
            continue;
        }

        cv::cvtColor(frameBGR, frameRGBA, CV_BGR2RGBA);
        cv::flip(frameRGBA, frameRGBAFlipped, 0);

        imgTexture.setData(width, height, frameRGBAFlipped.data);
        inputImageTexture.set(imgTexture, 0);

        oogl::drawTriangleArrays(6);
        window.display();
        fpsCounter.update();
    }

    return 0;
}

