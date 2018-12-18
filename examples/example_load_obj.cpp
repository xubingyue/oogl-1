//
// Created by xiaozhuai on 2018/12/10.
//
#include <SFML/Graphics.hpp>
#include <oogl/oogl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "obj_loader_with_objl.h"
#include "FPSCounter.h"

int main() {

    sf::RenderWindow window;
    window.create(sf::VideoMode(1600, 900), __EXAMPLE_TARGET__, sf::Style::Default, sf::ContextSettings(32));

    FPSCounter fpsCounter;
    fpsCounter.setFpsChangedListener([&window](int fps) {
        window.setTitle(__EXAMPLE_TARGET__ "  fps: " + std::to_string(fps));
    });

    std::string objDir = "assets/model/tails/tails.obj";
//    std::string objDir = "assets/model/nanosuit/nanosuit.obj";

    Model model;
    if (!model.load(objDir)) {
        printf("Model load failed\n");
        return 1;
    }

    printf("Model loaded, mesh count: %d\n", model.meshCount);

    oogl::VertexShader vertexShader;
    vertexShader.createFromFile("assets/shader/" + std::string(__EXAMPLE_TARGET__) + ".vert");

    oogl::FragmentShader fragmentShader;
    fragmentShader.createFromFile("assets/shader/" + std::string(__EXAMPLE_TARGET__) + ".frag");

    oogl::Program program;
    program.create();
    program.attach(vertexShader, fragmentShader);
    program.link();
    program.validate();
    program.use();

    oogl::Attribute positionAttr = program.getAttribute("position");
    oogl::Attribute inputTextureCoordinateAttr = program.getAttribute("inputTextureCoordinate");

    oogl::Uniform diffuseTextureUniform = program.getUniform("diffuseTexture");
    oogl::Uniform projectionUniform = program.getUniform("projection");
    oogl::Uniform viewUniform = program.getUniform("view");
    oogl::Uniform modelUniform = program.getUniform("model");


    float fovy = 56.0f;
    float aspect = (float) window.getSize().x / (float) window.getSize().y;
    float zNear = 0.1f;
    float zFar = 100.0f;
    glm::mat4 projectionMat = glm::perspective(
            fovy,
            aspect,
            zNear,
            zFar
    );
    projectionUniform.setMatrix4fv(1, glm::value_ptr(projectionMat));


    glm::vec3 cameraVec(0.0f, 0.6f, 0.8f);
    float distance = 10.0f;
    glm::vec3 targetPos(0.0f, 3.0f, 0.0f);
    glm::vec3 upVec(0, 0, 1);
    glm::mat4 viewMat = glm::lookAt(
            cameraVec * distance,   //camera position
            targetPos,              //target position
            upVec                   //up vector
    );
    viewUniform.setMatrix4fv(1, glm::value_ptr(viewMat));


    float ratio = 1.0f;
    glm::mat4 modelMat = glm::scale(glm::mat4(1.0f), glm::vec3(ratio));
    modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));

    bool moving = false;
    bool rotating = false;
    float moveFromX = 0.0f;
    float moveFromY = 0.0f;

    oogl::enable(GL_DEPTH_TEST);
//    oogl::enable(GL_LINE_SMOOTH);
//    oogl::enable(GL_POINT_SMOOTH);
//    oogl::enable(GL_POLYGON_SMOOTH);

    bool running = true;
    while (running) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::MouseWheelScrolled:
                    distance += -event.mouseWheelScroll.delta * 0.3;
                    viewMat = glm::lookAt(
                            cameraVec * distance,   //camera position
                            targetPos,              //target position
                            upVec                   //up vector
                    );
                    viewUniform.setMatrix4fv(1, glm::value_ptr(viewMat));
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        rotating = true;
                        moveFromX = event.mouseButton.x;
                        moveFromY = event.mouseButton.y;
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        moveFromX = event.mouseButton.x;
                        moveFromY = event.mouseButton.y;
                        moving = true;
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        rotating = false;
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        moving = false;
                    }
                    break;
                case sf::Event::MouseMoved:
                    if (rotating) {
                        float deltaX = event.mouseMove.x - moveFromX;
                        float deltaY = -(event.mouseMove.y - moveFromY);

                        moveFromX = event.mouseMove.x;
                        moveFromY = event.mouseMove.y;

                        modelMat = glm::rotate(modelMat, glm::radians(3.0f) * deltaX * 0.1f,
                                               glm::vec3(0.0f, 1.0f, 0.0f));
                        modelMat = glm::rotate(modelMat, glm::radians(3.0f) * deltaY * 0.1f,
                                               glm::vec3(1.0f, 0.0f, 0.0f));
                        modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                    } else if (moving) {
                        float deltaX = event.mouseMove.x - moveFromX;
                        float deltaY = -(event.mouseMove.y - moveFromY);

                        moveFromX = event.mouseMove.x;
                        moveFromY = event.mouseMove.y;

                        modelMat = glm::translate(modelMat, glm::vec3(deltaX * 0.02f, deltaY * 0.02f, 0.0f));
                        modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                    }
                    break;
                case sf::Event::Resized:
                    aspect = (float) window.getSize().x / (float) window.getSize().y;
                    projectionMat = glm::perspective(
                            fovy,
                            aspect,
                            zNear,
                            zFar
                    );
                    projectionUniform.setMatrix4fv(1, glm::value_ptr(projectionMat));
                    oogl::viewPort(0, 0, window.getSize().x, window.getSize().y);
                case sf::Event::KeyPressed:
                    switch (event.key.code) {

                        case sf::Keyboard::Left:
                            modelMat = glm::rotate(modelMat, glm::radians(3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                            modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                            break;
                        case sf::Keyboard::Right:
                            modelMat = glm::rotate(modelMat, glm::radians(-3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                            modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                            break;

                        case sf::Keyboard::Up:
                            modelMat = glm::rotate(modelMat, glm::radians(3.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                            modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                            break;
                        case sf::Keyboard::Down:
                            modelMat = glm::rotate(modelMat, glm::radians(-3.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                            modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                            break;

                        case sf::Keyboard::Comma:
                            modelMat = glm::rotate(modelMat, glm::radians(3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                            modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                            break;

                        case sf::Keyboard::Period:
                            modelMat = glm::rotate(modelMat, glm::radians(-3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                            modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                            break;

                            // zoom
                        case sf::Keyboard::LBracket:
                            ratio *= 0.98;
                            modelMat = glm::scale(glm::mat4(1.0f), glm::vec3(ratio));
                            modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                            break;
                        case sf::Keyboard::RBracket:
                            ratio *= 1.02;
                            modelMat = glm::scale(glm::mat4(1.0f), glm::vec3(ratio));
                            modelUniform.setMatrix4fv(1, glm::value_ptr(modelMat));
                            break;
                        default:
                            printf("key code: %d\n", event.key.code);
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        oogl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        program.use();

        for (int meshIndex = 0; meshIndex < model.meshCount; ++meshIndex) {
            Mesh mesh = model.meshes[meshIndex];

            positionAttr.setVBO(mesh.positionVBO, 3);
            inputTextureCoordinateAttr.setVBO(mesh.textureCoordinateVBO, 2);

            diffuseTextureUniform.set(mesh.diffuseTexture, meshIndex);

            oogl::drawTriangleArrays(mesh.verticesCount);
        }

        window.display();
        fpsCounter.update();
    }

    return 0;
}

