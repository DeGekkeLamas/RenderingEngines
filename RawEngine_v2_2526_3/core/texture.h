#pragma once

#include "gladHelper.hpp"
#include <string>

namespace core {

    class Texture {
    private:
        GLuint id;

    public:
        Texture(const std::string& path);

        GLuint getId();
    };

}
