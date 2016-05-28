#include "model.hpp"

using GL::Model;
using GL::Vertex;
using GL::Face;

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

    printf("FACE\n");
    for(int i = 0; i < mesh->header.nfaces; i++) {
        for(int j = 0; j < 3; j++) {
            f[i].vertex_ids[j] = mesh->faces[i].uvs[j];
            printf("%d,", mesh->faces[i].uvs[j]);
        }
        printf("\n");
    }

    printf("VERT\n");
    for(int i = 0; i < mesh->header.nuvs; i++) {
        MeshVertex *mvert = &mesh->verts[mesh->uvs[i].vert_id];
        printf("%d\n", mesh->uvs[i].vert_id);
        printf("%f, %f, %f\n", mvert->position[0], mvert->position[1], mvert->position[2]);
        v[i].position[0] = mvert->position[0];
        v[i].position[1] = mvert->position[1];
        v[i].position[2] = mvert->position[2];
        v[i].normal[0] = mvert->normal[0];
        v[i].normal[1] = mvert->normal[1];
        v[i].normal[2] = mvert->normal[2];
        printf("%d %d\n", mesh->uvs[i].uv[0], mesh->uvs[i].uv[1]);
        v[i].uv[0] = mesh->uvs[i].uv[0];
        v[i].uv[1] = mesh->uvs[i].uv[1];
        v[i].color[0] = 0;
        v[i].color[1] = 0;
        v[i].color[2] = 0;
        v[i].material = 0;
        v[i].boneid[0] = mvert->bone_id[0];
        v[i].boneid[1] = mvert->bone_id[1];
        v[i].boneweight[0] = mvert->bone_weight[0];
        v[i].boneweight[1] = mvert->bone_weight[1];
    }

    gm->uploadVertexData(v, mesh->header.nuvs);
    gm->uploadFaceData(f, mesh->header.nfaces);

    delete[] v;
    delete[] f;
    return gm;
}
