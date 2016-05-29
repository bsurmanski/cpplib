#ifndef _DRAW_GL_MESH_HPP
#define _DRAW_GL_MESH_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <stdint.h>

#include "cpplib/geom/mesh.hpp"

namespace GL {

struct Vertex {
    float position[3];
    int16_t normal[3];
    uint16_t uv[2];
    uint8_t color[3];
    uint8_t material;
    uint8_t boneid[2];
    uint8_t boneweight[2];
    uint16_t incident_edge_id; // some incident edge of vertex
};

struct Face {
    uint16_t vertex_ids[3];
};

// Model representation in GPU memory
class Model {
    GLuint ibo;
    GLuint vbo;
    int nelems;

    public:
    Model();
    ~Model();
    static Model *fromMesh(Mesh *mesh);
    void uploadVertexData(Vertex *verts, int nverts);
    void uploadFaceData(Face *faces, int nfaces);
    void bind();
    void draw();
};

};

#endif
