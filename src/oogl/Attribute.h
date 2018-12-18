//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_ATTRIBUTE_H
#define OOGL_ATTRIBUTE_H

#include "Object.h"
#include "VBO.h"

namespace oogl {

class Attribute {
    public:
        explicit Attribute(GLint index = -1) {
            if (index < 0) {
                mIndexInvalid = true;
                mIndex = INVALID_GL_ID;
            } else {
                mIndexInvalid = false;
                mIndex = (GLuint) index;
            }
        }

        inline GLuint getIndex() const {
            return mIndex;
        }

        inline void set(GLfloat v0) {
            if(invalid()) return;

            glVertexAttrib1f(mIndex, v0);
        }

        inline void set(GLfloat v0, GLfloat v1) {
            if(invalid()) return;

            glVertexAttrib2f(mIndex, v0, v1);
        }

        inline void set(GLfloat v0, GLfloat v1, GLfloat v2) {
            if(invalid()) return;

            glVertexAttrib3f(mIndex, v0, v1, v2);
        }

        inline void set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
            if(invalid()) return;

            glVertexAttrib4f(mIndex, v0, v1, v2, v3);
        }

        inline void set1v(const GLfloat *v) {
            if(invalid()) return;

            glVertexAttrib1fv(mIndex, v);
        }

        inline void set2v(const GLfloat *v) {
            if(invalid()) return;

            glVertexAttrib2fv(mIndex, v);
        }

        inline void set3v(const GLfloat *v) {
            if(invalid()) return;

            glVertexAttrib3fv(mIndex, v);
        }

        inline void set4v(const GLfloat *v) {
            if(invalid()) return;

            glVertexAttrib4fv(mIndex, v);
        }

        inline void setPointer(
                const void *pointer, GLint vecSize = 2,
                GLenum type = GL_FLOAT,
                GLboolean normalized = GL_FALSE,
                GLsizei stride = 0) {

            if(invalid()) return;

            VBO::unbindAll();
            glVertexAttribPointer(mIndex, vecSize, type, normalized, stride, pointer);
            glEnableVertexAttribArray(mIndex);
        }

        inline void setVBO(
                const VBO &v, GLint vecSize = 2,
                GLenum type = GL_FLOAT,
                GLboolean normalized = GL_FALSE,
                GLsizei stride = 0) {

            if(invalid()) return;

            v.bind();
            glVertexAttribPointer(mIndex, vecSize, type, normalized, stride, NULL);
            glEnableVertexAttribArray(mIndex);
        }

        inline bool valid() {
            return !mIndexInvalid;
        }

        inline bool invalid() {
            return mIndexInvalid;
        }

    protected:
        GLuint mIndex;
        bool mIndexInvalid;


};

}

#endif //OOGL_ATTRIBUTE_H
