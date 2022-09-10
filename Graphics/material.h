#pragma once

#include "GLWrappers/texture.h"
#include "GLWrappers/shader.h"
#include <memory>

#include "glm/glm.hpp"

enum ColorSource{
    SOLID_COLOR,
    TEXTURE_COLOR,
    PER_VERTEX_COLOR
};

class Material{
public:
    Material(std::shared_ptr<Texture> tex = NULL, glm::vec3 color = glm::vec3(1), float shininess = 1.f, ColorSource colorSource = ColorSource::SOLID_COLOR);
    ~Material();

    void use(std::shared_ptr<Shader> activeShader);

private:
    ColorSource m_colorSource;
    std::shared_ptr<Texture> m_texture;
    glm::vec3 m_color;
    float m_shininess;
};