//
// Created by xiaozhuai on 2018/12/11.
//
#ifndef OOGL_FRAMEBUFFER_H
#define OOGL_FRAMEBUFFER_H

#include "Object.h"
#include "Texture2D.h"

namespace oogl {

class Framebuffer : public Object {
    protected:
        explicit Framebuffer(GLuint id) : Object(id), mWidth(0), mHeight(0) {}

    public:
        Framebuffer() : Object(), mWidth(0), mHeight(0) {}

        inline void create() {
            glGenFramebuffers(1, &mId);
            if (!mId) {
                OOGL_LOGE("glGenFramebuffers err");
            } else {
                OOGL_LOGI("glGenFramebuffers suc, id: %u", mId);
            }
        }

        inline void release() {
            glDeleteFramebuffers(1, &mId);
            mId = INVALID_GL_ID;
        }

        inline void bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, mId);
        }

        inline void unbind() const {
            unbindAll();
        }

        inline static void unbindAll() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        inline void attach(const Texture2D &texture, GLenum attachment = GL_COLOR_ATTACHMENT0, GLint level = 0) {
            mTexture = texture;
            mWidth = mTexture.getWidth();
            mHeight = mTexture.getHeight();
            bind();
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, mTexture.getId(), level);
            unbind();
        }

        inline void readPixels(
                void *data,
                GLint x = 0,
                GLint y = 0,
                GLsizei width = DEPEND_ON_FRAMEBUFFER_SIZE,
                GLsizei height = DEPEND_ON_FRAMEBUFFER_SIZE) {

            bind();
            glReadPixels(
                    0, 0,
                    width == DEPEND_ON_FRAMEBUFFER_SIZE ? mWidth : width,
                    height == DEPEND_ON_FRAMEBUFFER_SIZE ? mHeight : height,
                    GL_RGBA, GL_UNSIGNED_BYTE, data
            );
            unbind();
        }

        inline GLsizei getWidth() const {
            return mWidth;
        }

        inline GLsizei getHeight() const {
            return mHeight;
        }

        inline Texture2D getTexture() {
            return mTexture;
        }

        inline GLuint getTextureId() {
            return mTexture.getId();
        }

    public:
        static const Framebuffer SCREEN;
        static const GLsizei DEPEND_ON_FRAMEBUFFER_SIZE = -1;

    protected:
        Texture2D mTexture;
        GLsizei mWidth;
        GLsizei mHeight;

};

const Framebuffer Framebuffer::SCREEN = Framebuffer(0);

}

#endif //OOGL_FRAMEBUFFER_H
