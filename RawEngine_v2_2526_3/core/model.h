#pragma once

#include <vector>
#include "mesh.h"
#include "../Scripts/Engine/Transform.hpp"

namespace core {
    class Model {
    private:
        std::vector<core::Mesh> meshes;
    public:
        Model(std::vector<core::Mesh> meshes) : meshes(meshes) {}
        void render();
    };
}
