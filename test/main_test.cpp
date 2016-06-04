#include "cpplib/common/file.hpp"
#include "cpplib/draw/sdlWindow.hpp"
#include "cpplib/draw/gl/drawDevice.hpp"
#include <SDL/SDL.h>

#include <unistd.h>


using GL::DrawDevice;

SDLWindow *window;
DrawDevice *drawDevice;

int main(int argc, char **argv) {
    window = new SDLWindow(320, 320, "test");
    drawDevice = new DrawDevice(320, 320);
    File f("cube.msh");
    Mesh *m = Mesh::load(&f);
    GL::Model *glm = GL::Model::fromMesh(m);
    GL::RGBATexture glt(1,1);
    float tick = 0.0;
    for(int i = 0; i < 200; i++) {
        tick += 0.01;
        Mat4 mat;
        mat.rotate(tick, Vec4(1, 2, 1));
        mat.translate(Vec4(0, 0, -5));
        drawDevice->clear();
        drawDevice->clearFramebuffer();
        drawDevice->drawModel(glm, &glt, mat);
        drawDevice->blitFramebuffer();
        window->SwapBuffers();
        usleep(10);
    }
    return 0;
}
