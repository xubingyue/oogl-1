//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_UNIFORM_H
#define OOGL_UNIFORM_H

#include "Texture2D.h"
#include "Functions.h"

namespace oogl {

class Uniform {
    public:
        explicit Uniform(GLint index = -1) {
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
            if (invalid()) return;

            glUniform1f(mIndex, v0);
        }

        inline void set(GLfloat v0, GLfloat v1) {
            if (invalid()) return;

            glUniform2f(mIndex, v0, v1);
        }

        inline void set(GLfloat v0, GLfloat v1, GLfloat v2) {
            if (invalid()) return;

            glUniform3f(mIndex, v0, v1, v2);
        }

        inline void set(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
            if (invalid()) return;

            glUniform4f(mIndex, v0, v1, v2, v3);
        }

        inline void set(GLint v0) {
            if (invalid()) return;

            glUniform1i(mIndex, v0);
        }

        inline void set(GLint v0, GLint v1) {
            if (invalid()) return;

            glUniform2i(mIndex, v0, v1);
        }

        inline void set(GLint v0, GLint v1, GLint v2) {
            if (invalid()) return;

            glUniform3i(mIndex, v0, v1, v2);
        }

        inline void set(GLint v0, GLint v1, GLint v2, GLint v3) {
            if (invalid()) return;

            glUniform4i(mIndex, v0, v1, v2, v3);
        }

        inline void set(const Texture2D &v, int textureIndex) {
            if (invalid()) return;

            activeTextureIndex(textureIndex);
            v.bind();
            set(textureIndex);
//            v.unbind();
        }

        inline void set1v(const GLfloat *v, GLsizei count = 1) {
            if (invalid()) return;

            glUniform1fv(mIndex, count, v);
        }

        inline void set2v(const GLfloat *v, GLsizei count = 1) {
            if (invalid()) return;

            glUniform2fv(mIndex, count, v);
        }

        inline void set3v(const GLfloat *v, GLsizei count = 1) {
            if (invalid()) return;

            glUniform3fv(mIndex, count, v);
        }

        inline void set4v(const GLfloat *v, GLsizei count = 1) {
            if (invalid()) return;

            glUniform4fv(mIndex, count, v);
        }

        inline void set1v(const GLint *v, GLsizei count = 1) {
            if (invalid()) return;

            glUniform1iv(mIndex, count, v);
        }

        inline void set2v(const GLint *v, GLsizei count = 1) {
            if (invalid()) return;

            glUniform2iv(mIndex, count, v);
        }

        inline void set3v(const GLint *v, GLsizei count = 1) {
            if (invalid()) return;

            glUniform3iv(mIndex, count, v);
        }

        inline void set4v(const GLint *v, GLsizei count = 1) {
            if (invalid()) return;

            glUniform4iv(mIndex, count, v);
        }

        inline void setMatrix2fv(GLsizei count, const GLfloat *v, GLboolean transpose = GL_FALSE) {
            if (invalid()) return;

            glUniformMatrix2fv(mIndex, count, transpose, v);
        }

        inline void setMatrix3fv(GLsizei count, const GLfloat *v, GLboolean transpose = GL_FALSE) {
            if (invalid()) return;

            glUniformMatrix3fv(mIndex, count, transpose, v);
        }

        inline void setMatrix4fv(GLsizei count, const GLfloat *v, GLboolean transpose = GL_FALSE) {
            if (invalid()) return;

            glUniformMatrix4fv(mIndex, count, transpose, v);
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

#endif //OOGL_UNIFORM_H
