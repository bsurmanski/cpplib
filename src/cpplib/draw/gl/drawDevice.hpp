#ifndef _DRAW_GL_DRAWDEVICE_HPP
#define _DRAW_GL_DRAWDEVICE_HPP

#include "cpplib/draw/gl/framebuffer.hpp"
#include "cpplib/draw/gl/texture.hpp"
#include "cpplib/draw/gl/model.hpp"
#include "cpplib/draw/gl/program.hpp"
#include "cpplib/geom/mat.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

namespace GL {

class DrawDevice {
    Framebuffer *main_buffer;
    Texture *color_texture;
    Texture *normal_texture;
    Texture *depth_texture;

    Program *simple_program;
    Program *deferred_program;

    Model *plane;

    int w,h;

    void bindStandardAttributes(Program *program);

    public:
    DrawDevice(int w, int h);
    void clear();
    void clearFramebuffer();
    void drawModel(Model *m, Texture *t, const Mat4 &mv);
    void blitFramebuffer();
};
}

#endif
