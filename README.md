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

## Contribute

We accepted pr and issue. If oogl helps, please give me a star. 🎉