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

template<GLenum type>
class EBO : public Object {
    public:
        EBO() : Object(), mBytesPerIndex(0), mType(0), mIndexesCount(0) {
            mType = type;
            switch (mType) {
                case GL_UNSIGNED_INT:
                    mBytesPerIndex = sizeof(GLuint);
                    break;
                case GL_UNSIGNED_SHORT:
                    mBytesPerIndex = sizeof(GLushort);
                    break;
                case GL_UNSIGNED_BYTE:
                    mBytesPerIndex = sizeof(GLubyte);
                    break;
                default:
                    OOGL_LOGE("EBO type %d not supported by oogl", type);
                    return;
            }
        }

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

        inline void setData(GLsizei size, const void *data, GLenum usage) {
            bind();
            mIndexesCount = size;
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * mBytesPerIndex, data, usage);
            unbind();
        }

        inline void setSubData(GLintptr offset, GLsizei size, const GLubyte *data) {
            bind();
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * mBytesPerIndex, size * mBytesPerIndex, data);
            unbind();
        }

        inline GLenum getType() const {
            return mType;
        }

        inline GLsizei getIndexesCount() const {
            return mIndexesCount;
        }

    protected:
        int mBytesPerIndex;
        GLenum mType;
        GLsizei mIndexesCount;

};

typedef EBO<GL_UNSIGNED_BYTE> UByteEBO;
typedef EBO<GL_UNSIGNED_SHORT> UShortEBO;
typedef EBO<GL_UNSIGNED_INT> UIntEBO;

}


#endif //OOGL_EBO_H
