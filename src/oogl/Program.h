//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_PROGRAM_H
#define OOGL_PROGRAM_H

#include "gl.h"
#include "Object.h"
#include "Shader.h"
#include "Attribute.h"
#include "Uniform.h"

namespace oogl {

class Program : public Object {

    public:

        Program() : Object() {}

        inline void create() {
            mId = glCreateProgram();
            if (!mId) {
                OOGL_LOGE("glCreateProgram err");
            } else {
                OOGL_LOGI("glCreateProgram suc, id: %u", mId);
            }
        }

        inline void release() {
            glDeleteProgram(mId);
            mId = INVALID_GL_ID;
        }

        inline void attach(const VertexShader &vs) {
            glAttachShader(mId, vs.getId());
        }

        inline void attach(const FragmentShader &fs) {
            glAttachShader(mId, fs.getId());
        }

        inline void attach(const VertexShader &vs, const FragmentShader &fs) {
            attach(vs);
            attach(fs);
        }

        inline void detach(const VertexShader &vs) {
            glDetachShader(mId, vs.getId());
        }

        inline void detach(const FragmentShader &fs) {
            glDetachShader(mId, fs.getId());
        }

        inline void detach(const VertexShader &vs, const FragmentShader &fs) {
            detach(vs);
            detach(fs);
        }

        inline void link() {
            glLinkProgram(mId);
            if (!getLinkStatus()) {
                OOGL_LOGE("glLinkProgram err");
                OOGL_LOGE("%s", getInfoLog().c_str());
            } else {
                OOGL_LOGI("glLinkProgram suc");
            }
        }

        inline void validate() {
            glValidateProgram(mId);
            std::string log = getInfoLog();
            if (log.length() > 0) {
                OOGL_LOGE("%s", log.c_str());
            }
        }

        inline void use() const {
            glUseProgram(mId);
        }

        static inline void unuse() {
            glUseProgram(0);
        }

        inline Attribute getAttribute(const std::string &name) {
            GLint index = glGetAttribLocation(mId, name.c_str());
            if (index < 0) {
                OOGL_LOGE("glGetAttribLocation err, name: %s", name.c_str());
            } else {
                OOGL_LOGI("glGetAttribLocation suc, name: %s, id: %d", name.c_str(), index);
            }
            return Attribute(index);
        }

        inline Uniform getUniform(const std::string &name) {
            GLint index = glGetUniformLocation(mId, name.c_str());
            if (index < 0) {
                OOGL_LOGE("glGetUniformLocation err, name: %s", name.c_str());
            } else {
                OOGL_LOGI("glGetUniformLocation suc, name: %s, id: %d", name.c_str(), index);
            }
            return Uniform(index);
        }

        inline std::string getInfoLog(int bufSize = 4096) {
            char logStr[bufSize];
            glGetProgramInfoLog(mId, DEFAULT_INFO_LOG_SIZE, NULL, logStr);
            return std::string(logStr);
        }

        inline void getParameter(GLenum pname, GLint *params) {
            glGetProgramiv(mId, pname, params);
        }

    protected:
        inline GLint getLinkStatus() {
            GLint linked = GL_FALSE;
            getParameter(GL_LINK_STATUS, &linked);
            return linked;
        }


};

}

#endif //OOGL_PROGRAM_H
