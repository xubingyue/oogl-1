//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_VBO_H
#define OOGL_VBO_H

#include "Object.h"

namespace oogl {

/**
 * Vertex Buffer Object
 */
class VBO : public Object {
    public:
        VBO() : Object() {}

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
            glBindBuffer(GL_ARRAY_BUFFER, mId);
        }

        inline void unbind() const {
            unbindAll();
        }

        inline static void unbindAll() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        inline void setData(GLsizeiptr size, const GLfloat *data, GLenum usage) {
            bind();
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, usage);
            unbind();
        }

        inline void setSubData(GLintptr offset, GLsizeiptr size, const GLfloat *data) {
            bind();
            glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(GLfloat), size * sizeof(float), data);
            unbind();
        }

};

}


#endif //OOGL_VBO_H
