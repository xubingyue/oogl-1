//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_TEXTURE_H
#define OOGL_TEXTURE_H

#include <string>
#include "Object.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

namespace oogl {

class Texture2D : public Object {
    protected:
        explicit Texture2D(GLuint id) : Object(id), mWidth(0), mHeight(0) {}

    public:
        Texture2D() : Object(), mWidth(0), mHeight(0) {}

        inline void create() {
            glGenTextures(1, &mId);
            if (!mId) {
                OOGL_LOGE("glGenTextures err");
            } else {
                OOGL_LOGI("glGenTextures suc, id: %u", mId);
            }
        }

        inline void release() {
            glDeleteTextures(1, &mId);
            mId = INVALID_GL_ID;
        }

        inline void bind() const {
            glBindTexture(GL_TEXTURE_2D, mId);
        }

        inline void unbind() const {
            unbindAll();
        }

        inline static void unbindAll() {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        inline void genMipmap() const {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        inline void setParameter(GLenum pname, GLfloat param) {
            glTexParameterf(GL_TEXTURE_2D, pname, param);
        }

        inline void setParameter(GLenum pname, GLint param) {
            glTexParameteri(GL_TEXTURE_2D, pname, param);
        }

        inline void setData(
                GLsizei width, GLsizei height, const void *pixels,
                GLint level = 0,
                GLint internalFormat = GL_RGBA,
                GLint border = 0,
                GLenum format = GL_RGBA,
                GLenum type = GL_UNSIGNED_BYTE) {

            mWidth = width;
            mHeight = height;
            glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, border, format, type, pixels);
        }

        inline void loadFromFile(
                const std::string &file,
                bool flipVertical = true,
                GLint level = 0,
                GLint internalFormat = GL_RGBA,
                GLint border = 0) {

            int width, height, channels;
            int desiredChannels = 4;

            switch (internalFormat) {
                case GL_RGBA:
                    desiredChannels = 4;
                    break;
                case GL_RGB:
                    desiredChannels = 3;
                    break;
                case GL_RED:
                case GL_GREEN:
                case GL_BLUE:
                case GL_ALPHA:
                    desiredChannels = 1;
                    break;
                default:
                    break;
            }

            uint8_t *pixels = stbi_load(file.c_str(), &width, &height, &channels, desiredChannels);
            if (pixels == NULL) {
                OOGL_LOGE("Load image err, file: %s, reason: %s", file.c_str(), stbi_failure_reason());
                return;
            }

            OOGL_LOGI("Load image suc, file: %s, width: %d, height: %d, channels: %d", file.c_str(), width, height,
                      channels);

            if (flipVertical) {
                stbi__vertical_flip(pixels, width, height, desiredChannels);
            }

            setData(
                    width, height, pixels,
                    level,
                    internalFormat,
                    border,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE
            );

            stbi_image_free(pixels);
        }

        GLsizei getWidth() const {
            return mWidth;
        }

        GLsizei getHeight() const {
            return mHeight;
        }

    public:
        static const Texture2D EMPTY;

    protected:
        GLsizei mWidth;
        GLsizei mHeight;

};

const Texture2D Texture2D::EMPTY = Texture2D(0);

}

#endif //OOGL_TEXTURE_H
