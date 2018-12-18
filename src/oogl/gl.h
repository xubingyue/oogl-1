//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_GL_H
#define OOGL_GL_H

// **************************************
// replace below with your implementation
#include <SFML/OpenGL.hpp>
#include <stdio.h>
#define OOGL_STD_OUTPUT          stdout
#define OOGL_STD_ERR_OUTPUT      stderr
#define OOGL_LOGI(format, args...) do{ fprintf(OOGL_STD_OUTPUT, "[%s:%d] ", __FILE__, __LINE__); fprintf(OOGL_STD_OUTPUT, format, ##args); fprintf(OOGL_STD_OUTPUT, "\n"); fflush(OOGL_STD_OUTPUT); } while(0)
#define OOGL_LOGE(format, args...) do{ fprintf(OOGL_STD_ERR_OUTPUT, "\033[31m[%s:%d] ", __FILE__, __LINE__); fprintf(OOGL_STD_ERR_OUTPUT, format, ##args); fprintf(OOGL_STD_ERR_OUTPUT, "\033[0m\n"); fflush(OOGL_STD_ERR_OUTPUT); } while(0)
// replace above with your implementation
// **************************************

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
