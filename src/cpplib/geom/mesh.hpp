#ifndef _GEOM_MESH_HPP
#define _GEOM_MESH_HPP

#include "cpplib/common/input.hpp"
#include "cpplib/common/array.hpp"
#include "cpplib/geom/geometry.hpp"
#include "cpplib/geom/feature.hpp"

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

struct MeshVertexData {
    float position[3];
    int16_t normal[3]; //normalized -32768 to 32767
    uint8_t PADDING1[8];
    uint8_t bone_id[2];
    uint8_t bone_weight[2];
    uint16_t edge_id;

    Vec4 getPosition();
};

struct MeshUvData {
    uint16_t uv[2]; // normalized 0 to 65535
    uint16_t vert_id;
    uint16_t PADDING1;
};

struct MeshFaceData {
    uint16_t uvs[3];
    uint16_t edge_id;

    Vec4 getNormal(Mesh *mesh);
    MeshVertexData *getVertex(Mesh *mesh, int i);
};

struct MeshEdgeData {
    uint16_t vert_id[2];
    uint16_t face_id[2];
    uint16_t left_edge_id[2]; // cw, ccw edge ids from first vertex
    uint16_t right_edge_id[2]; // cw, ccw edge ids from second vertex
};


// for collision stuff, Mesh must be a convex mesh that contains the origin.
struct Mesh {
    MeshHeader header;
    Array<MeshVertexData> verts;
    Array<MeshUvData> uvs;
    Array<MeshFaceData> faces;
    Array<MeshEdgeData> edges;

    enum Convexity {
        UNKNOWN,
        CONVEX,
        CONCAVE,
    };

    Convexity convexity;

    public:
    Mesh(MeshHeader &header, MeshVertexData *v, MeshUvData *u, MeshFaceData *f, MeshEdgeData *e);
    ~Mesh();

    Slice<MeshVertexData> getVertices();
    Slice<MeshUvData> getUvs();
    Slice<MeshFaceData> getFaces();
    Slice<MeshEdgeData> getEdges();

    static Mesh *load(Input *in);

    // given a vertex index 'base', What is the next vertex,
    // connected to 'base' by edges, that is closer to point 'p' than base?
    // If 'base' is the closest vertex, return 'base'.
    Vertex nextClosestVertex(Vec4 &p, Vertex base);
    Vertex closestVertex(Vec4 &p, Vertex start);

    bool isConvex();
    virtual bool contains(Vec4 &o);
    virtual Vec4 closestPointTo(Vec4 &o);
    virtual Face closestFaceTo(Vec4 &o); // by voronoi mapping of face normals
    bool collides(Mesh *o);
};

#endif
