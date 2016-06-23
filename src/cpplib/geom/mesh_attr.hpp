#ifndef _GEOM_MESH_ATTR_HPP
#define _GEOM_MESH_ATTR_HPP

#include "cpplib/geom/vec.hpp"

class Mesh;
class MeshVertexData;
class MeshFaceData;
class MeshEdgeData;

class MeshAttr {
    protected:
    Mesh *mesh;
    int index;

    public:
    MeshAttr(Mesh *_mesh, int _index);
    Mesh *getMesh() { return mesh; }
    int getIndex() { return index; }
};

class Vertex;
class Face;
class Uv;
class Edge;

class Vertex : public MeshAttr {
    public:
    Vertex(Mesh *_mesh, int _index) : MeshAttr(_mesh, _index) {}
    MeshVertexData &getVertexData();
    Vec4 getPosition();
    Vec4 getNormal();
    Edge getIncidentEdge();
};

class Face : public MeshAttr {

    public:
    Face(Mesh *_mesh, int _index) : MeshAttr(_mesh, _index) {}
    MeshFaceData &getFaceData();
    Edge getIncidentEdge();
};

class Edge : public MeshAttr {
    public:
    Edge(Mesh *_mesh, int _index) : MeshAttr(_mesh, _index) {}
    MeshEdgeData &getEdgeData();
    Vertex front();
    Vertex back();
    Vertex other(Vertex &v);
    Face left();
    Face right();
    Edge cwFrom(Vertex &v);
    Edge ccwFrom(Vertex &v);
};

#endif
