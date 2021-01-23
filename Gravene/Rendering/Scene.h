#ifndef SCENE_H
#define SCENE_h

#include "GameObject.h"
#include "Camera.h"

#include <vector>

class Scene {
    private:
        std::vector<GameObject> m_GameObjects;
    public:
        void Draw(const Camera& camera) 
        {
            
        }
};

#endif