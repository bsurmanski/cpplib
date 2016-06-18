#include "mesh.hpp"

#include "cpplib/common/exception.hpp"

#include <string.h>
#include <float.h>

Vec4 MeshVertex::getPosition() {
    return Vec4(position[0], position[1], position[2]);
}

MeshVertex *MeshFace::getVertex(Mesh *mesh, int i) {
    return &mesh->verts[mesh->uvs[uvs[i]].vert_id];
}

Vec4 MeshFace::getNormal(Mesh *m) {
    return (getVertex(m, 1)->getPosition() - getVertex(m, 0)->getPosition()).cross(
            getVertex(m, 2)->getPosition() - getVertex(m, 0)->getPosition());
}

Mesh::Mesh(MeshHeader &h, MeshVertex *v, MeshUv *u, MeshFace *f, MeshEdge *e) :
    header(h), verts(h.nverts, v), uvs(h.nuvs, u), faces(h.nfaces, f),
    edges(h.nedges, e), convexity(UNKNOWN) { }

Mesh::~Mesh() {
}

Slice<MeshVertex> Mesh::getVertices() {
    return verts.slice();
}

Slice<MeshUv> Mesh::getUvs() {
    return uvs.slice();
}

Slice<MeshFace> Mesh::getFaces() {
    return faces.slice();
}

Slice<MeshEdge> Mesh::getEdges() {
    return edges.slice();
}

Mesh *Mesh::load(Input *in) {
    MeshHeader header;
    in->read(&header, sizeof(MeshHeader), 1);

    if(header.magic[0] != 'M' ||
       header.magic[1] != 'D' ||
       header.magic[2] != 'L') {
        throw Exception("Wrong Magic number in MSH file format");
    }

    char sep[4];

    MeshVertex *verts;
    MeshUv *uvs;
    MeshFace *faces;
    MeshEdge *edges;

    in->read(sep, 4, 1);
    if(strncmp(sep, "VERT", 4)) {
        throw Exception("Expected Vertex header in MSH file");
    }
    verts = new MeshVertex[header.nverts];
    in->read(verts, sizeof(MeshVertex), header.nverts);

    in->read(sep, 4, 1);
    if(strncmp(sep, "UVUV", 4)) {
        delete[] verts;
        throw Exception("Expected UV header in MSH file");
    }
    uvs = new MeshUv[header.nuvs];
    in->read(uvs, sizeof(MeshUv), header.nuvs);

    in->read(sep, 4, 1);
    if(strncmp(sep, "FACE", 4)) {
        delete[] verts;
        delete[] uvs;
        throw Exception("Expected Face header in MSH file");
    }
    faces = new MeshFace[header.nfaces];
    in->read(faces, sizeof(MeshFace), header.nfaces);

    in->read(sep, 4, 1);
    if(strncmp(sep, "EDGE", 4)) {
        delete[] verts;
        delete[] uvs;
        delete[] faces;
        throw Exception("Expected Edge header in MSH file");
    }
    edges = new MeshEdge[header.nedges];
    in->read(edges, sizeof(MeshEdge), header.nedges);

    /*
    TODO: bones
    in->read(sep, 4, 1);
    if(!strncmp(sep, "BONE", 4)) {
        delete[] verts;
        delete[] uvs;
        delete[] faces;
        delete[] edges;
        throw Exception("Expected Bone header in MSH file");
    }
    in->read(bones, sizeof(MeshBone), header.nbones);
    */

    Mesh *mesh = new Mesh(header, verts, uvs, faces, edges);
    return mesh;
}

bool Mesh::isConvex() {
    if(convexity == UNKNOWN) {
        for(int i = 0; i < faces.length(); i++) {
            Vec4 norm = faces[i].getNormal(this);
            Vec4 base = faces[i].getVertex(this, 0)->getPosition();
            for(int j = 0; j < verts.length(); i++) {
                Vec4 delta = verts[j].getPosition() - base;
                if(delta.dot(norm) > FLT_EPSILON) {
                    convexity = CONCAVE;
                    return convexity;
                }
            }
        }
        convexity = CONVEX;
    }
    return convexity == CONVEX;
}

bool Mesh::contains(Vec4 &o) {
    if(!isConvex()) {
        throw Exception("Mesh must be convex to check point containment");
    }
    //TODO
}

Vec4 Mesh::closestPointTo(Vec4 &o) {
    if(!isConvex()) {
        throw Exception("Mesh must be convex to check closest point");
    }
    //TODO
}

Vec4 Mesh::surfaceTangent(Vec4 &n) {
    if(!isConvex()) {
        throw Exception("Mesh must be convex to check surface tangent");
    }
    //TODO
}
