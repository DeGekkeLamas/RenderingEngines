#pragma once

#include <vector>
#include <glm/ext/matrix_float4x4.hpp>
#include "mesh.h"
#include "../Scripts/GameObject.hpp"

namespace core {
    class Model : public GameObject {
    private:
        std::vector<core::Mesh> meshes;
    public:
        Transform transform;
        Model(std::vector<core::Mesh> meshes) : meshes(meshes), GameObject("model") {}
        void render();

        glm::mat4 getModelMatrix() const;
    };
}
