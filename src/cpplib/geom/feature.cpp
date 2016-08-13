#include "feature.hpp"

#include "cpplib/geom/mesh.hpp"
#include "cpplib/common/exception.hpp"

Feature::Feature(Mesh *_mesh, int _index) : mesh(_mesh), index(_index) {}

MeshVertexData &Vertex::getVertexData() {
    return mesh->verts[index];
}

Vec4 Vertex::getPosition() {
    MeshVertexData &data = getVertexData();
    return Vec4(data.position[0], data.position[1], data.position[2]);
}

Vec4 Vertex::getNormal() {
    MeshVertexData &data = getVertexData();
    return Vec4(data.normal[0], data.normal[1], data.normal[2]).normalized();
}

Edge Vertex::getIncidentEdge() {
    MeshVertexData &data = getVertexData();
    return Edge(mesh, data.edge_id);
}

MeshFaceData &Face::getFaceData() {
    return mesh->faces[index];
}

Edge Face::getIncidentEdge() {
    MeshFaceData &data = getFaceData();
    return Edge(mesh, data.edge_id);
}

MeshEdgeData &Edge::getEdgeData() {
    return mesh->edges[index];
}

Vertex Edge::front() {
    MeshEdgeData &data = getEdgeData();
    return Vertex(mesh, data.vert_id[0]);
}

Vertex Edge::back() {
    MeshEdgeData &data = getEdgeData();
    return Vertex(mesh, data.vert_id[1]);
}

Vertex Edge::other(Vertex &v) {
    MeshEdgeData &data = getEdgeData();
    if(v.getIndex() == data.vert_id[0]) return Vertex(mesh, data.vert_id[1]);
    if(v.getIndex() == data.vert_id[1]) return Vertex(mesh, data.vert_id[0]);
    throw Exception("invalid vertex in edge lookup");
}

Edge Edge::cwFrom(Vertex &v) {
    MeshEdgeData &data = getEdgeData();
    if(v.getIndex() == front().getIndex()) {
        return Edge(mesh, data.left_edge_id[0]);
    } else if(v.getIndex() == back().getIndex()) {
        return Edge(mesh, data.right_edge_id[0]);
    }
    throw Exception("invalid vertex in cw traversal of edge");
}

Edge Edge::ccwFrom(Vertex &v) {
    MeshEdgeData &data = getEdgeData();
    if(v.getIndex() == front().getIndex()) {
        return Edge(mesh, data.left_edge_id[1]);
    } else if(v.getIndex() == back().getIndex()) {
        return Edge(mesh, data.right_edge_id[1]);
    }
    throw Exception("invalid vertex in ccw traversal of edge");
}

Face Edge::left() {
    MeshEdgeData &data = getEdgeData();
    return Face(mesh, data.face_id[0]);
}

Face Edge::right() {
    MeshEdgeData &data = getEdgeData();
    return Face(mesh, data.face_id[1]);
}

Face Edge::leftFrom(Vertex &v) {
    MeshEdgeData &data = getEdgeData();
    if(v.getIndex() == front().getIndex()) {
        return left();
    } else if(v.getIndex() == back().getIndex()) {
        return right();
    }
    throw Exception("invalid vertex in face retrieval");
}

Face Edge::rightFrom(Vertex &v) {
    MeshEdgeData &data = getEdgeData();
    if(v.getIndex() == front().getIndex()) {
        return right();
    } else if(v.getIndex() == back().getIndex()) {
        return left();
    }
    throw Exception("invalid vertex in face retrieval");
}
