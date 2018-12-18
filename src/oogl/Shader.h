//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_SHADER_H
#define OOGL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include "gl.h"
#include "Object.h"

namespace oogl {

template<GLenum type>
class Shader : public Object {

    public:
        Shader() : Object() {}

        inline void create(const std::string &code) {
            mId = glCreateShader(type);
            if (!mId) {
                OOGL_LOGE("glCreateShader err");
            } else {
                OOGL_LOGI("glCreateShader suc, id: %u", mId);
            }

            const char *str = code.c_str();
            GLint len = static_cast<GLint>(code.length());
            glShaderSource(mId, 1, &str, &len);
            glCompileShader(mId);

            if (!getCompileStatus()) {
                OOGL_LOGE("glCompileShader err");
                OOGL_LOGE("%s", getInfoLog().c_str());
            } else {
                OOGL_LOGI("glCompileShader suc");
            }
        }

        inline void createFromFile(const std::string &glslFile) {
            std::ifstream file;
            file.open(glslFile);
            if (!file) {
                OOGL_LOGE("Open glsl file err, file: %s", glslFile.c_str());
                return;
            }
            std::stringstream ss;
            ss << file.rdbuf();
            file.close();
            std::string code = ss.str();
//            OOGL_LOGI("Read glsl file suc, code: \n%s", code.c_str());
            create(code);
        }

        inline void release() {
            glDeleteShader(mId);
            mId = INVALID_GL_ID;
        }

        inline void getParameter(GLenum pname, GLint *params) {
            glGetShaderiv(mId, pname, params);
        }

        inline std::string getInfoLog(int bufSize = 4096) {
            char logStr[bufSize];
            glGetShaderInfoLog(mId, DEFAULT_INFO_LOG_SIZE, NULL, logStr);
            return std::string(logStr);
        }

    protected:
        inline GLint getCompileStatus() {
            GLint compiled = GL_FALSE;
            getParameter(GL_COMPILE_STATUS, &compiled);
            return compiled;
        }

};

typedef Shader<GL_VERTEX_SHADER> VertexShader;
typedef Shader<GL_FRAGMENT_SHADER> FragmentShader;

}


#endif //OOGL_SHADER_H
