#ifndef _DRAW_GL_PROGRAM
#define _DRAW_GL_PROGRAM

#include <GL/glew.h>
#include <GL/gl.h>

#include "cpplib/common/input.hpp"
#include "cpplib/common/string.hpp"
#include "cpplib/geom/mat.hpp"
#include "cpplib/geom/vec.hpp"

namespace GL {

class DrawDevice;

class Program {
    protected:
    GLuint program;

    public:
    Program();
    virtual ~Program();
    virtual void bind();
    friend class DrawDevice;

    void setUniform(const char *name, Mat4 &m);
    void setUniform(const char *name, Vec4 &v);
    void setUniformFloat(const char *name, float f);
    void setUniformInt(const char *name, int i);
};

class StdProgram : public Program {
    GLuint vso;
    GLuint fso;

    public:
    StdProgram(Input *vs, Input *fs);
    bool hasErrors();
};

}

#endif
