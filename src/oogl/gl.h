//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_GL_H
#define OOGL_GL_H

#include "config.h"

#include <SFML/OpenGL.hpp>

#ifdef OOGL_SYSTEM_WINDOWS
    #ifdef _MSC_VER
        #include <windows.h>
    #endif
    #include <GL/gl.h>
#endif


#ifdef OOGL_SYSTEM_FREEBSD
    #include <GL/gl.h>
#endif


#ifdef OOGL_SYSTEM_LINUX
    #include <GL/gl.h>
#endif


#ifdef OOGL_SYSTEM_MACOS
    #include <OpenGL/gl.h>
#endif


#ifdef OOGL_SYSTEM_IOS
    #ifdef OOGL_USE_GLES1
        #include <OpenGLES/ES1/gl.h>
        #include <OpenGLES/ES1/glext.h>
    #else
        #include <OpenGLES/ES2/gl.h>
        #include <OpenGLES/ES2/glext.h>
    #endif
#endif


#ifdef OOGL_SYSTEM_ANDROID
    #ifdef OOGL_USE_GLES1
        #include <GLES/gl.h>
        #include <GLES/glext.h>
    #else
        #include <GLES2/gl2.h>
        #include <GLES2/gl2ext.h>
    #endif
#endif

#include <stdio.h>
#define OOGL_STD_OUTPUT          stdout
#define OOGL_STD_ERR_OUTPUT      stderr
#define OOGL_LOGI(format, args...) do{ fprintf(OOGL_STD_OUTPUT, "[%s:%d] ", __FILE__, __LINE__); fprintf(OOGL_STD_OUTPUT, format, ##args); fprintf(OOGL_STD_OUTPUT, "\n"); fflush(OOGL_STD_OUTPUT); } while(0)
#define OOGL_LOGE(format, args...) do{ fprintf(OOGL_STD_ERR_OUTPUT, "\033[31m[%s:%d] ", __FILE__, __LINE__); fprintf(OOGL_STD_ERR_OUTPUT, format, ##args); fprintf(OOGL_STD_ERR_OUTPUT, "\033[0m\n"); fflush(OOGL_STD_ERR_OUTPUT); } while(0)

#define INVALID_GL_ID           (0)
#define DEFAULT_INFO_LOG_SIZE   (4096)
#define GL_TEXTURES_SIZE        (12)

static GLenum GL_TEXTURES[GL_TEXTURES_SIZE] = {
        GL_TEXTURE0,
        GL_TEXTURE1,
        GL_TEXTURE2,
        GL_TEXTURE3,
        GL_TEXTURE4,
        GL_TEXTURE5,
        GL_TEXTURE6,
        GL_TEXTURE7,
        GL_TEXTURE8,
        GL_TEXTURE9,
        GL_TEXTURE10,
        GL_TEXTURE11,
};

#endif //OOGL_GL_H
