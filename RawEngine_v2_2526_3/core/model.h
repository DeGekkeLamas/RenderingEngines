#pragma once

#include <vector>
#include "mesh.h"
#include "Scripts/Transform.hpp"

namespace core {
    class Model {
    private:
        std::vector<core::Mesh> meshes;
    public:
        Transform transform;
        Model(std::vector<core::Mesh> meshes) : meshes(meshes) {}
        void render();

        glm::mat4 getModelMatrix() const;
    };
}
