//
// Created by xiaozhuai on 2018/12/10.
//
#ifndef OOGL_OBJECT_H
#define OOGL_OBJECT_H

#include "gl.h"

namespace oogl {

class Object {

    public:
        Object() : mId(INVALID_GL_ID) {}

        explicit Object(GLuint id) : mId(id) {}

        inline GLuint getId() const {
            return mId;
        }

    protected:
        GLuint mId;
};

}


#endif //OOGL_OBJECT_H
