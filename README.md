# oogl

An OpenGL/ES OO wrapper for C++ (head only)

## Usage
Just embed `src/oogl` dir in your project.

And do not forget to link gl libs.

For iOS or Android, oogl use gles2 as default. If you want to use gles1, please define `OOGL_USE_GLES1` macro.

## Dependencies

* stb_image         (public domain)

All dependencies has been embedded in oogl.

## Examples

### Build

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### Dependencies (just for examples)

* SFML      (Window manage)
* OpenCV    (Capture webcam)
* glm       (Matrix transformation)

These dependencies are just for examples, it is not requires by oogl.
If your want to build examples, then you will need these.

## Quick Start

Let's draw a 2D pic use oogl

```cpp

// include SFML for window manage
#include <SFML/Graphics.hpp>

// include oogl header
#include <oogl/oogl.h>

// define a function to load texture from file
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

// vertex coordinates
GLfloat vertexCoord[12] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f
};

// texture coordinates
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

    // create vertex shader
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

    // create fragment shader
    oogl::FragmentShader fragmentShader;
    fragmentShader.create(R"EOF(
uniform sampler2D inputImageTexture;
varying vec2 textureCoordinate;
void main()
{
    gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
}
)EOF");

    // create program, attach with shaders, link, validate and use it
    oogl::Program program;
    program.create();
    program.attach(vertexShader, fragmentShader);
    program.link();
    program.validate();
    program.use();

    // get attributes
    oogl::Attribute positionAttr = program.getAttribute("position");
    oogl::Attribute inputTextureCoordinateAttr = program.getAttribute("inputTextureCoordinate");
    
    // get uniforms
    oogl::Uniform inputImageTexture = program.getUniform("inputImageTexture");

    // load texture from file
    oogl::Texture2D imgTexture = loadTexture("assets/image/test.jpg");

    // input attributes
    positionAttr.setPointer(vertexCoord);
    inputTextureCoordinateAttr.setPointer(textureCoord);
    
    // input uniforms, here input a texture, and use texture units GL_TEXTURE1
    inputImageTexture.set(imgTexture, 1);

    // render loop
    bool running = true;
    while (running) {
    
        // event loop
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::Resized:
                    // change view port on window resized
                    oogl::viewPort(0, 0, window.getSize().x, window.getSize().y);
                    break;
                default:
                    break;
            }
        }

        // draw
        oogl::Triangle::drawArrays(6);
        
        // swap buffer
        window.display();
    }

    return 0;
}

```

## Contribute

We accepted pr and issue. If oogl helps, please give me a star. 🎉