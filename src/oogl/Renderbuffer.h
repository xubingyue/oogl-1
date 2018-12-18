//
// Created by xiaozhuai on 2018/12/17.
//
#ifndef OOGL_RENDERBUFFER_H
#define OOGL_RENDERBUFFER_H

#include "Object.h"

namespace oogl {

class Renderbuffer : public Object {
    public:
        Renderbuffer() : Object(), mWidth(0), mHeight(0) {}

        inline void create() {
            glGenRenderbuffers(1, &mId);
            if (!mId) {
                OOGL_LOGE("glGenRenderbuffers err");
            } else {
                OOGL_LOGI("glGenRenderbuffers suc, id: %u", mId);
            }
        }

        inline void release() {
            glDeleteRenderbuffers(1, &mId);
            mId = INVALID_GL_ID;
        }

        inline void bind() const {
            glBindRenderbuffer(GL_RENDERBUFFER, mId);
        }

        inline void unbind() const {
            unbindAll();
        }

        static inline void unbindAll() {
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }

        inline void setStorage(GLsizei width, GLsizei height, GLenum internalformat = GL_RGBA) {
            mWidth = width;
            mHeight = height;
            bind();
            glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
            unbind();
        }

        GLsizei getWidth() const {
            return mWidth;
        }

        GLsizei getHeight() const {
            return mHeight;
        }

    protected:
        GLsizei mWidth;
        GLsizei mHeight;
};

}


#endif //OOGL_RENDERBUFFER_H
