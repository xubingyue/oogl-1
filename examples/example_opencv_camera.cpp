//
// Created by xiaozhuai on 2018/12/12.
//

#include <SFML/Graphics.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <oogl/oogl.h>

int main(int argc, char **argv) {
    cv::Mat frameBGR;
    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    cv::VideoCapture capture(deviceID + apiID);
    if (!capture.isOpened()) {
        printf("Error: initialize camera capture failed\n");
        return 1;
    }

    unsigned int width = static_cast<unsigned int>(capture.get(cv::CAP_PROP_FRAME_WIDTH));
    unsigned int height = static_cast<unsigned int>(capture.get(cv::CAP_PROP_FRAME_HEIGHT));

    cv::Mat frameRGBA = cv::Mat(height, width, CV_8UC4);

    sf::Texture texture;
    texture.create(width, height);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::RenderWindow window(sf::VideoMode(width, height), __EXAMPLE_TARGET__);

    oogl::FPSCounter fpsCounter;
    fpsCounter.setFpsChangedListener([&window](int fps) {
        window.setTitle(__EXAMPLE_TARGET__ "  fps: " + std::to_string(fps));
    });

    bool running = true;
    while (running) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }

        capture.read(frameBGR);
        if (frameBGR.empty()) {
            printf("Error: blank frameBGR grabbed\n");
            continue;
        }

        cv::cvtColor(frameBGR, frameRGBA, CV_BGR2RGBA);
        texture.update(frameRGBA.data);

        window.draw(sprite);
        window.display();
        fpsCounter.update();
    }

    capture.release();
    return 0;
}