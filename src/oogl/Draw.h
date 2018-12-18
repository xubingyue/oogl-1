//
// Created by xiaozhuai on 2018/12/18.
//
#ifndef OOGL_DRAW_H
#define OOGL_DRAW_H

#include "gl.h"
#include "EBO.h"

namespace oogl {

template<GLenum mode>
class Draw {
    public:
        static inline void drawArrays(GLsizei count, GLint first = 0) {
            glDrawArrays(mode, first, count);
        }

        static inline void drawElements(GLsizei count, GLenum type, const void *indices) {
            UByteEBO::unbindAll(); // any XXXEBO::unbindAll() is ok
            glDrawElements(mode, count, type, indices);
        }

        static inline void drawElements(const UByteEBO &ebo, GLsizei count = EQUAL_TO_EBO_INDEXED_COUNT) {
            if (count == EQUAL_TO_EBO_INDEXED_COUNT) count = ebo.getIndexesCount();

            ebo.bind();
            glDrawElements(mode, count, ebo.getType(), NULL);
            ebo.unbind();
        }

        static inline void drawElements(const UShortEBO &ebo, GLsizei count = EQUAL_TO_EBO_INDEXED_COUNT) {
            if (count == EQUAL_TO_EBO_INDEXED_COUNT) count = ebo.getIndexesCount();

            ebo.bind();
            glDrawElements(mode, count, ebo.getType(), NULL);
            ebo.unbind();
        }

        static inline void drawElements(const UIntEBO &ebo, GLsizei count = EQUAL_TO_EBO_INDEXED_COUNT) {
            if (count == EQUAL_TO_EBO_INDEXED_COUNT) count = ebo.getIndexesCount();

            ebo.bind();
            glDrawElements(mode, count, ebo.getType(), NULL);
            ebo.unbind();
        }

    protected:
        static const GLsizei EQUAL_TO_EBO_INDEXED_COUNT = -1;
};

typedef Draw<GL_POINTS> Point;
typedef Draw<GL_LINES> Line;
typedef Draw<GL_LINE_STRIP> LineStrip;
typedef Draw<GL_LINE_LOOP> LineLoop;
typedef Draw<GL_TRIANGLES> Triangle;
typedef Draw<GL_TRIANGLE_STRIP> TriangleStrip;
typedef Draw<GL_TRIANGLE_FAN> TriangleFan;

}


#endif //OOGL_DRAW_H
