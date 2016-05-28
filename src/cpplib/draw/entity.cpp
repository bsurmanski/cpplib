#include "entity.hpp"

Entity::Entity(GL::Model *_model, GL::Texture *_texture) :
    model(_model),
    texture(_texture),
    scale(Vec4(1.0, 1.0, 1.0, 0.0)) {
}

Mat4 Entity::getModelMatrix() {
    Mat4 mat;
    mat.scale(scale.x, scale.y, scale.z);
    mat = mat * rotation;
    mat.translate(position);
    return mat;
}
