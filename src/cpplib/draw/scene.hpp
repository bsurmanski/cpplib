#ifndef _DRAW_SCENE_HPP
#define _DRAW_SCENE_HPP

#include "cpplib/common/input.hpp"
#include "cpplib/common/string.hpp"
#include "cpplib/draw/gl/model.hpp"
#include "cpplib/draw/gl/texture.hpp"
#include "cpplib/draw/entity.hpp"
#include "cpplib/geom/mat.hpp"

#include <map>
#include <vector>

class Scene {
    std::map<String, GL::Model*> models;
    std::map<String, GL::Texture*> textures;
    std::vector<Entity*> entities;

    public:
    void registerModel(const String &k, GL::Model *m);
    void registerTexture(const String &k, GL::Texture *t);
    void loadModelFromFile(const String &k, const String &filenm);
    void loadTextureFromFile(const String &k, const String &filenm);
    GL::Model *getModel(const String &k);
    GL::Texture *getTexture(const String &k);
    Entity *addEntity(const String &k);
    Entity *addEntity(const String &mk, const String &tk);
};

void loadScn(Scene *s, Input *in);

#endif
