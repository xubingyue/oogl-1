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

## 贡献

欢迎提交pr或issue, 如果你觉得oogl有用, 请给颗星. 🎉