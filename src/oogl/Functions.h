//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_FUNCTIONS_H
#define OOGL_FUNCTIONS_H

#include "gl.h"

namespace oogl {

inline void drawTriangleArrays(GLsizei count, GLint first = 0) {
    glDrawArrays(GL_TRIANGLES, first, count);
}

inline void drawRectangleArrays(GLsizei count, GLint first = 0) {
    glDrawArrays(GL_TRIANGLE_STRIP, first, count);
}

inline void drawTriangleElements(GLsizei count, GLenum type, const void *indices = NULL) {
    glDrawElements(GL_TRIANGLES, count, type, indices);
}

inline void drawRectangleElements(GLsizei count, GLenum type, const void *indices = NULL) {
    glDrawElements(GL_TRIANGLE_STRIP, count, type, indices);
}

inline void clear(GLbitfield mask) {
    glClear(mask);
}

inline void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glClearColor(red, green, blue, alpha);
}

inline void clearColor(uint32_t color) {
    unsigned char *pixel = (unsigned char *) &color;
    GLfloat red = (float) pixel[0] / 255.0f;
    GLfloat green = (float) pixel[1] / 255.0f;
    GLfloat blue = (float) pixel[2] / 255.0f;
    GLfloat alpha = (float) pixel[3] / 255.0f;
    clearColor(red, green, blue, alpha);
}

inline void activeTexture(GLenum texture) {
    glActiveTexture(texture);
}

inline void activeTextureIndex(int index) {
    if (index >= GL_TEXTURES_SIZE) {
        OOGL_LOGE("Active texture index %d exceeded limit", index);
        return;
    }
    activeTexture((GLenum) (GL_TEXTURE0 + index));
}

inline void viewPort(GLint x, GLint y, GLsizei width, GLsizei height) {
    glViewport(x, y, width, height);
}

inline void enable(GLenum cap) {
    glEnable(cap);
}

inline void disable(GLenum cap) {
    glDisable(cap);
}

inline bool isEnabled(GLenum cap) {
    return glIsEnabled(cap) == GL_TRUE;
}

inline void blendFunc(GLenum sfactor, GLenum dfactor) {
    glBlendFunc(sfactor, dfactor);
}

inline void flush() {
    glFlush();
}

inline void finish() {
    glFinish();
}

inline int getIntegerValue(GLenum pname) {
    int val;
    glGetIntegerv(pname, &val);
    return val;
}

inline GLfloat getFloatValue(GLenum pname) {
    GLfloat val;
    glGetFloatv(pname, &val);
    return val;
}

inline GLboolean getBooleanValue(GLenum pname) {
    GLboolean val;
    glGetBooleanv(pname, &val);
    return val;
}


}


#endif //OOGL_FUNCTIONS_H
