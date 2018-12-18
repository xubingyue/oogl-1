//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_EBO_H
#define OOGL_EBO_H

#include "Object.h"

namespace oogl {

/**
 * Element Buffer Object
 */
class EBO : public Object {
    public:
        EBO() : Object() {}

        inline void create() {
            glGenBuffers(1, &mId);
            if (!mId) {
                OOGL_LOGE("glGenBuffers err");
            } else {
                OOGL_LOGI("glGenBuffers suc, id: %u", mId);
            }
        }

        inline void release() {
            glDeleteBuffers(1, &mId);
            mId = INVALID_GL_ID;
        }

        inline void bind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
        }

        inline void unbind() const {
            unbindAll();
        }

        inline static void unbindAll() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        inline void setData(GLsizeiptr size, const GLuint *data, GLenum usage) {
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, usage);
            unbind();
        }

        inline void setData(GLsizeiptr size, const GLushort *data, GLenum usage) {
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLushort), data, usage);
            unbind();
        }

        inline void setData(GLsizeiptr size, const GLubyte *data, GLenum usage) {
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLubyte), data, usage);
            unbind();
        }

        inline void setSubData(GLintptr offset, GLsizeiptr size, const GLushort *data) {
            bind();
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(GLushort), size * sizeof(GLushort), data);
            unbind();
        }

};

}


#endif //OOGL_EBO_H
