#include "mesh.hpp"

#include "cpplib/common/exception.hpp"

#include <string.h>

Mesh::Mesh(MeshHeader &h, MeshVertex *v, MeshUv *u, MeshFace *f, MeshEdge *e) :
    header(h), verts(v), uvs(u), faces(f), edges(e) { }

Mesh::~Mesh() {
    delete[] verts;
    delete[] uvs;
    delete[] faces;
    delete[] edges;
}

Slice<MeshVertex> Mesh::getVertices() {
    return Slice<MeshVertex>(header.nverts, verts);
}

Slice<MeshUv> Mesh::getUvs() {
    return Slice<MeshUv>(header.nuvs, uvs);
}

Slice<MeshFace> Mesh::getFaces() {
    return Slice<MeshFace>(header.nfaces, faces);
}

Slice<MeshEdge> Mesh::getEdges() {
    return Slice<MeshEdge>(header.nedges, edges);
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
