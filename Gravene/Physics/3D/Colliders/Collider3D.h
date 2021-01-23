#include "../../Collider.h"

#include "AABB3D.h"

class Collider3D : public Collider {
    private:
        
    public:
        Collider3D() = default;
    public:

    protected:
        AABB3D aabb;
};