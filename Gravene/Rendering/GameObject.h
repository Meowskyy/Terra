#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../Physics/Transform.h"

class GameObject {
    protected: 

    private:

    public:
        Transform* transform;

        GameObject() : transform(new Transform()) {}
        GameObject(glm::vec3 position) : transform(new Transform(position)) {}

        ~GameObject() { delete transform; }
};

#endif