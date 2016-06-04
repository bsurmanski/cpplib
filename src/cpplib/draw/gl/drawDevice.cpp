#include "drawDevice.hpp"

#include <stdio.h>

#include "cpplib/common/stringInput.hpp"


using GL::DrawDevice;
using GL::Framebuffer;
using GL::Texture;
using GL::RGBATexture;
using GL::DepthTexture;
using GL::Model;
using GL::Program;

static bool GLEW_INITIALIZED = false;

DrawDevice::DrawDevice(int _w, int _h) : w(_w), h(_h) {
    if(!GLEW_INITIALIZED) {
        glewInit();
        GLEW_INITIALIZED = true;
    }

#include "build/cpplib/draw/gl/glsl/simple.vs"
#include "build/cpplib/draw/gl/glsl/simple.fs"
    StringInput simplevs(String((const char*) src_cpplib_draw_gl_glsl_simple_vs,
                                src_cpplib_draw_gl_glsl_simple_vs_len));
    StringInput simplefs(String((const char*) src_cpplib_draw_gl_glsl_simple_fs,
                                src_cpplib_draw_gl_glsl_simple_fs_len));

#include "build/cpplib/draw/gl/glsl/deferred.vs"
#include "build/cpplib/draw/gl/glsl/deferred.fs"
    StringInput deferredvs(String((const char*) src_cpplib_draw_gl_glsl_deferred_vs,
                                  src_cpplib_draw_gl_glsl_deferred_vs_len));
    StringInput deferredfs(String((const char*) src_cpplib_draw_gl_glsl_deferred_fs,
                                  src_cpplib_draw_gl_glsl_deferred_fs_len));

    simple_program = new StdProgram(&simplevs, &simplefs);
    deferred_program = new StdProgram(&deferredvs, &deferredfs);

#include "build/cpplib/draw/gl/res/plane.msh"
    StringInput plane_f(String((const char*) src_cpplib_draw_gl_res_plane_msh,
                               src_cpplib_draw_gl_res_plane_msh_len));
    Mesh *plane_mesh = Mesh::load(&plane_f);
    plane = Model::fromMesh(plane_mesh);
    delete plane_mesh;

    main_buffer = new Framebuffer;
    color_texture = new RGBATexture(w, h);
    normal_texture = new RGBATexture(w, h);
    depth_texture = new DepthTexture(w, h);
    main_buffer->addTarget(color_texture);
    main_buffer->addTarget(normal_texture);
    main_buffer->addTarget(depth_texture);


    glFrontFace(GL_CW);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    frustum = Mat4::createFrustumMatrix(-1, 1, -1, 1, 2, 1000);
}

void DrawDevice::bindStandardAttributes(Program *prog) {
    GLint pos = glGetAttribLocation(prog->program, "position");
    GLint norm = glGetAttribLocation(prog->program, "normal");
    GLint uv = glGetAttribLocation(prog->program, "uv");
    GLint color = glGetAttribLocation(prog->program, "color");

    if(pos >= 0) {
        glEnableVertexAttribArray(pos);
        glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 32, NULL);
    }

    if(norm >= 0) {
        glEnableVertexAttribArray(norm);
        glVertexAttribPointer(norm, 3, GL_SHORT, GL_TRUE, 32, (void*) 12);
    }

    if(uv >= 0) {
        glEnableVertexAttribArray(uv);
        glVertexAttribPointer(uv, 2, GL_UNSIGNED_SHORT, GL_TRUE, 32, (void*) 18);
    }

    if(color >= 0) {
        glEnableVertexAttribArray(color);
        glVertexAttribPointer(color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 32, (void*) 22);
    }
}

void DrawDevice::clear() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void DrawDevice::clearFramebuffer() {
    main_buffer->bind();
    glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void DrawDevice::drawModel(Model *m, Texture *t, const Mat4 &mv) {
    glEnable(GL_DEPTH_TEST);
    main_buffer->bind();

    t->bind();
    simple_program->bind();
    m->bind();
    bindStandardAttributes(simple_program);
    Mat4 f = frustum * mv;
    simple_program->setUniform("mvp", f);

    static float tick = 0.0f;
    tick += 0.01f;
    simple_program->setUniformFloat("tick", tick);

    m->draw();
}

void DrawDevice::blitFramebuffer() {
    glDisable(GL_DEPTH_TEST);
    color_texture->bind(0);
    normal_texture->bind(1);
    depth_texture->bind(2);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, w, h);
    deferred_program->bind();
    plane->bind();
    bindStandardAttributes(deferred_program);
    deferred_program->setUniformInt("t_color", 0);
    deferred_program->setUniformInt("t_normal", 1);
    deferred_program->setUniformInt("t_depth", 2);
    plane->draw();

    int err = glGetError();
    if(err) {
        printf("ERR %d\n", err);
    }
}
