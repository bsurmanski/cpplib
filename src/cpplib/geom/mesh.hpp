#ifndef _DRAW_MDL_HPP
#define _DRAW_MDL_HPP

#include "cpplib/common/input.hpp"
#include "cpplib/common/array.hpp"
#include "cpplib/geom/geometry.hpp"

#include <stdint.h>

class Mesh;

struct MeshHeader {
    uint8_t magic[3];
    uint8_t version;
    uint16_t nverts;
    uint16_t nuvs;
    uint16_t nfaces;
    uint16_t nedges;
    uint8_t nbones;
    uint8_t PADDING1[2];
    uint8_t name[16];
};

struct MeshVertex {
    float position[3];
    int16_t normal[3]; //normalized -32768 to 32767
    uint8_t PADDING1[8];
    uint8_t bone_id[2];
    uint8_t bone_weight[2];
    uint16_t edge_id;

    Vec4 getPosition();
};

struct MeshUv {
    uint16_t uv[2]; // normalized 0 to 65535
    uint16_t vert_id;
    uint16_t PADDING1;
};

struct MeshFace {
    uint16_t uvs[3];
    uint16_t edge_id;

    Vec4 getNormal(Mesh *mesh);
    MeshVertex *getVertex(Mesh *mesh, int i);
};

struct MeshEdge {
    uint16_t vert_id[2];
    uint16_t face_id[2];
    uint16_t left_edge_id[2]; // cw, ccw edge ids from first vertex
    uint16_t right_edge_id[2]; // cw, ccw edge ids from second vertex
};

struct Mesh {
    MeshHeader header;
    Array<MeshVertex> verts;
    Array<MeshUv> uvs;
    Array<MeshFace> faces;
    Array<MeshEdge> edges;

    enum Convexity {
        UNKNOWN,
        CONVEX,
        CONCAVE,
    };

    Convexity convexity;

    public:
    Mesh(MeshHeader &header, MeshVertex *v, MeshUv *u, MeshFace *f, MeshEdge *e);
    ~Mesh();

    Slice<MeshVertex> getVertices();
    Slice<MeshUv> getUvs();
    Slice<MeshFace> getFaces();
    Slice<MeshEdge> getEdges();

    static Mesh *load(Input *in);

    bool isConvex();
    virtual bool contains(Vec4 &o);
    virtual Vec4 closestPointTo(Vec4 &o);
    virtual Vec4 surfaceTangent(Vec4 &n);
};

#endif
