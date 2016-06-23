#include "mesh.hpp"

#include "cpplib/geom/mesh_attr.hpp"
#include "cpplib/common/exception.hpp"

#include <string.h>
#include <float.h>

Vec4 MeshVertexData::getPosition() {
    return Vec4(position[0], position[1], position[2]);
}

MeshVertexData *MeshFaceData::getVertex(Mesh *mesh, int i) {
    return &mesh->verts[mesh->uvs[uvs[i]].vert_id];
}

Vec4 MeshFaceData::getNormal(Mesh *m) {
    return (getVertex(m, 1)->getPosition() - getVertex(m, 0)->getPosition()).cross(
            getVertex(m, 2)->getPosition() - getVertex(m, 0)->getPosition());
}

/*
MeshEdge &MeshEdge::cwEdge(Mesh *m, int base_vertex) {
    if(vert_id[0] == base_vertex) return m->edges[left_edge_id[0]];
    if(vert_id[1] == base_vertex) return m->edges[right_edge_id[0]];
    throw Exception("Invalid vertex index when cw traversing edge");
}

MeshEdge &MeshEdge::ccwEdge(Mesh *m, int base_vertex) {
    if(vert_id[0] == base_vertex) return m->edges[left_edge_id[1]];
    if(vert_id[1] == base_vertex) return m->edges[right_edge_id[1]];
    throw Exception("Invalid vertex index when ccw traversing edge");
}
*/

Mesh::Mesh(MeshHeader &h, MeshVertexData *v, MeshUvData *u, MeshFaceData *f, MeshEdgeData *e) :
    header(h), verts(h.nverts, v), uvs(h.nuvs, u), faces(h.nfaces, f),
    edges(h.nedges, e), convexity(UNKNOWN) { }

Mesh::~Mesh() {
}

Slice<MeshVertexData> Mesh::getVertices() {
    return verts.slice();
}

Slice<MeshUvData> Mesh::getUvs() {
    return uvs.slice();
}

Slice<MeshFaceData> Mesh::getFaces() {
    return faces.slice();
}

Slice<MeshEdgeData> Mesh::getEdges() {
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

    MeshVertexData *verts;
    MeshUvData *uvs;
    MeshFaceData *faces;
    MeshEdgeData *edges;

    in->read(sep, 4, 1);
    if(strncmp(sep, "VERT", 4)) {
        throw Exception("Expected Vertex header in MSH file");
    }
    verts = new MeshVertexData[header.nverts];
    in->read(verts, sizeof(MeshVertexData), header.nverts);

    in->read(sep, 4, 1);
    if(strncmp(sep, "UVUV", 4)) {
        delete[] verts;
        throw Exception("Expected UV header in MSH file");
    }
    uvs = new MeshUvData[header.nuvs];
    in->read(uvs, sizeof(MeshUvData), header.nuvs);

    in->read(sep, 4, 1);
    if(strncmp(sep, "FACE", 4)) {
        delete[] verts;
        delete[] uvs;
        throw Exception("Expected Face header in MSH file");
    }
    faces = new MeshFaceData[header.nfaces];
    in->read(faces, sizeof(MeshFaceData), header.nfaces);

    in->read(sep, 4, 1);
    if(strncmp(sep, "EDGE", 4)) {
        delete[] verts;
        delete[] uvs;
        delete[] faces;
        throw Exception("Expected Edge header in MSH file");
    }
    edges = new MeshEdgeData[header.nedges];
    in->read(edges, sizeof(MeshEdgeData), header.nedges);

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

Vertex Mesh::nextClosestVertex(Vec4 &p, Vertex base) {
    Vertex closest = base;
    float dist_sq = base.getPosition().distsq(p);

    Edge start = base.getIncidentEdge();
    Edge iter = start;

    int i = 0;
    while(i++ < edges.length()) { // if we search more edges than there are, then theres a problem
        Vertex o = iter.other(base);

        if(o.getPosition().distsq(p) < dist_sq) {
            closest = o;
            dist_sq = o.getPosition().distsq(p);
        }

        iter = iter.cwFrom(base);
        if(iter.getIndex() == start.getIndex()) {
            return closest;
        }
    }
    throw Exception("Too many iterations while looking for next closest vertex");
}

Vertex Mesh::closestVertex(Vec4 &p, Vertex start) {
    Vertex closest = start;
    int i = 0;
    while(i++ < verts.length()) { // if we search more verts than there are
        Vertex o = nextClosestVertex(p, closest);
        if(o.getIndex() == closest.getIndex()) return closest;
        closest = o;
    }
    throw Exception("Too many iterations while looking for closest vertex");
}

bool Mesh::isConvex() {
    if(convexity == UNKNOWN) {
        for(int i = 0; i < faces.length(); i++) {
            Vec4 norm = faces[i].getNormal(this);
            Vec4 base = faces[i].getVertex(this, 0)->getPosition();
            for(int j = 0; j < verts.length(); j++) {
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
    for(int i = 0; i < faces.length(); i++) {
        Vec4 norm = faces[i].getNormal(this);
        Vec4 base = faces[i].getVertex(this, 0)->getPosition();
        if(norm.dot(base - o) > FLT_EPSILON) {
            return false;
        }
    }
    return true;
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
