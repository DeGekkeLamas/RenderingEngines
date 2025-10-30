#include "model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

namespace core {
    void Model::render() {
        for (int i = 0; i < meshes.size(); ++i) {
            meshes[i].render();
        }
    }

    void Model::translate(glm::vec3 translation) {
        modelMatrix = glm::translate(modelMatrix, translation);
    }

    void Model::rotate(glm::vec3 axis, float radians) {
        modelMatrix = glm::rotate(modelMatrix, radians, axis);
        glm::vec3 right = column(modelMatrix,0);
        // printf("Right vector is (%f,%f,%f)\n", right.x, right.y, right.z);
    }

    void Model::scale(glm::vec3 scale) {
        modelMatrix = glm::scale(modelMatrix, scale);
    }

    glm::mat4 Model::getModelMatrix() const {
        return this->modelMatrix;
    }
}