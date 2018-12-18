# oogl

oogl是一个OpenGL/ES的c++面向对象的封装. oogl仅包含头文件以方便使用.

## 使用方法
将`src/oogl`目录嵌入你的工程内即可, 推荐将包含目录设置为`oogl`目录的上一级目录.

别忘了你还需要链接gl库.

对于iOS和安卓, oogl默认使用gles2, 如果你想要使用gles1, 请定义`OOGL_USE_GLES1`宏.

## 依赖

* stb_image         (public domain)

所有依赖都已经被集成在项目中.

## 示例

### 编译

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### 依赖

* SFML      (窗口管理)
* OpenCV    (获取摄像头数据)
* glm       (矩阵变换)

示例依赖以上库, 对于oogl, 它们不是必须的, 但如果你需要编译示例, 则需要这些库.

## 快速开始

让我们使用oogl绘制一张2D图片

```cpp

// 包含 SFML 以进行窗口管理
#include <SFML/Graphics.hpp>

// 包含 oogl 头文件
#include <oogl/oogl.h>

// 定义一个函数, 用来加载从图片文件加载纹理
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

// 顶点坐标
GLfloat vertexCoord[12] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
};

// 纹理坐标
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

    // 创建顶点着色器
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

    // 创建片元着色器
    oogl::FragmentShader fragmentShader;
    fragmentShader.create(R"EOF(
uniform sampler2D inputImageTexture;
varying vec2 textureCoordinate;
void main()
{
    gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
}
)EOF");

    // 创建程序, 附着着色器, 链接程序, 验证程序, 使用程序
    oogl::Program program;
    program.create();
    program.attach(vertexShader, fragmentShader);
    program.link();
    program.validate();
    program.use();

    // 获得 attributes
    oogl::Attribute positionAttr = program.getAttribute("position");
    oogl::Attribute inputTextureCoordinateAttr = program.getAttribute("inputTextureCoordinate");
    
    // 获得 uniforms
    oogl::Uniform inputImageTexture = program.getUniform("inputImageTexture");

    // 从图片文件加载纹理
    oogl::Texture2D imgTexture = loadTexture("assets/image/test.jpg");

    // 输入 attributes
    positionAttr.setPointer(vertexCoord);
    inputTextureCoordinateAttr.setPointer(textureCoord);
    
    // 输入 uniforms, 这里输入了一个纹理, 并使用纹理单元 GL_TEXTURE1
    inputImageTexture.set(imgTexture, 1);

    // 渲染循环
    bool running = true;
    while (running) {
    
        // 事件循环
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::Resized:
                    // 当窗口大小改变时, 改变视口大小
                    oogl::viewPort(0, 0, window.getSize().x, window.getSize().y);
                    break;
                default:
                    break;
            }
        }

        // 绘制
        oogl::Triangle::drawArrays(6);
        
        // 交换缓冲区
        window.display();
    }

    return 0;
}

```

## 贡献

欢迎提交pr或issue, 如果你觉得oogl有用, 请给颗星. 🎉