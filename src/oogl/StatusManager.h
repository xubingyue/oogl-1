//
// Created by xiaozhuai on 2018/12/18.
//
#ifndef OOGL_STATUSMANAGER_H
#define OOGL_STATUSMANAGER_H

#include "gl.h"
#include "Functions.h"

namespace oogl {

class BlendStatusManager {
    public:
        static inline void backup() {
            sIsBlendEnabled = isEnabled(GL_BLEND);
            sSFactor = (GLenum) getIntegerValue(GL_BLEND_SRC);
            sDFactor = (GLenum) getIntegerValue(GL_BLEND_DST);
        }

        static inline void restore() {
            if (sIsBlendEnabled) {
                enable(GL_BLEND);
            } else {
                disable(GL_BLEND);
            }
            blendFunc(sSFactor, sDFactor);
        }

    protected:
        static bool sIsBlendEnabled;
        static GLenum sSFactor;
        static GLenum sDFactor;
};

bool BlendStatusManager::sIsBlendEnabled;
GLenum BlendStatusManager::sSFactor;
GLenum BlendStatusManager::sDFactor;

class ProgramStatusManager {
    public:
        static inline void backup() {
            sProgram = (GLuint) getIntegerValue(GL_CURRENT_PROGRAM);
        }

        static inline void restore() {
            glUseProgram(sProgram);
        }

    protected:
        static GLuint sProgram;
};

GLuint ProgramStatusManager::sProgram;

}


#endif //OOGL_STATUSMANAGER_H
