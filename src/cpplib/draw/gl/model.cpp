#include "model.hpp"

using GL::Model;

Model::Model() {
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    nelems = 0;
}

Model::~Model() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void Model::uploadVertexData(Vertex *verts, int nverts) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * nverts,
                 verts, GL_STATIC_DRAW);
}

void Model::uploadFaceData(Face *faces, int nfaces) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Face) * nfaces,
                 faces, GL_STATIC_DRAW);
    nelems = nfaces * 3;
}

void Model::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Model::draw() {
     glDrawElements(GL_TRIANGLES, nelems, GL_UNSIGNED_SHORT, NULL);
}

#include <stdio.h>
Model *Model::fromMesh(Mesh *mesh) {
    Model *gm = new Model;
    GL::Face *f = new GL::Face[mesh->header.nfaces];
    GL::Vertex *v = new GL::Vertex[mesh->header.nuvs];

    Slice<MeshFaceData> meshFaces = mesh->getFaces();
    for(int i = 0; i < meshFaces.length(); i++) {
        for(int j = 0; j < 3; j++) {
            f[i].vertex_ids[j] = meshFaces[i].uvs[j];
        }
    }

    Slice<MeshVertexData> meshVertices = mesh->getVertices();
    Slice<MeshUvData> meshUvs = mesh->getUvs();
    for(int i = 0; i < meshUvs.length(); i++) {
        MeshVertexData &mvert = meshVertices[meshUvs[i].vert_id];
        v[i].position[0] = mvert.position[0];
        v[i].position[1] = mvert.position[1];
        v[i].position[2] = mvert.position[2];
        v[i].normal[0] = mvert.normal[0];
        v[i].normal[1] = mvert.normal[1];
        v[i].normal[2] = mvert.normal[2];
        v[i].uv[0] = meshUvs[i].uv[0];
        v[i].uv[1] = meshUvs[i].uv[1];
        v[i].color[0] = 0;
        v[i].color[1] = 0;
        v[i].color[2] = 0;
        v[i].material = 0;
        v[i].boneid[0] = mvert.bone_id[0];
        v[i].boneid[1] = mvert.bone_id[1];
        v[i].boneweight[0] = mvert.bone_weight[0];
        v[i].boneweight[1] = mvert.bone_weight[1];
    }

    gm->uploadVertexData(v, meshUvs.length());
    gm->uploadFaceData(f, meshFaces.length());

    delete[] v;
    delete[] f;
    return gm;
}
