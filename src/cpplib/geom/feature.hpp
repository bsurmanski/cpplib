#ifndef _GEOM_MESH_ATTR_HPP
#define _GEOM_MESH_ATTR_HPP

#include "cpplib/geom/vec.hpp"

class Mesh;
class MeshVertexData;
class MeshFaceData;
class MeshEdgeData;

class Feature {
    protected:
    Mesh *mesh;
    int index;

    public:
    Feature(Mesh *_mesh, int _index);
    Mesh *getMesh() { return mesh; }
    int getIndex() { return index; }
    virtual bool isVertex() { return false; }
    virtual bool isFace() { return false; }
    virtual bool isEdge() { return false; }
};

class Vertex;
class Face;
class Uv;
class Edge;

class Vertex : public Feature {
    public:
    Vertex(Mesh *_mesh, int _index) : Feature(_mesh, _index) {}
    virtual bool isVertex() { return true; }
    MeshVertexData &getVertexData();
    Vec4 getPosition();
    Vec4 getNormal();
    Edge getIncidentEdge();
};

class Face : public Feature {
    public:
    Face(Mesh *_mesh, int _index) : Feature(_mesh, _index) {}
    virtual bool isFace() { return true; }
    MeshFaceData &getFaceData();
    Edge getIncidentEdge();
};

class Edge : public Feature {
    public:
    Edge(Mesh *_mesh, int _index) :
        Feature(_mesh, _index) {}
    virtual bool isEdge() { return true; }
    MeshEdgeData &getEdgeData();
    Vertex front();
    Vertex back();
    Vertex other(Vertex &v);
    Edge cwFrom(Vertex &v);
    Edge ccwFrom(Vertex &v);
    Face left();
    Face right();
    Face leftFrom(Vertex &v);
    Face rightFrom(Vertex &v);
};

#endif
