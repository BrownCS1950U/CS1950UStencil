#include "material.h"

Material::Material(std::shared_ptr<Texture> tex, glm::vec3 color, float shininess, ColorSource colorSource):
    m_colorSource(colorSource),
    m_texture(tex),
    m_color(color),
    m_shininess(shininess)
{

}

Material::~Material(){

}

void Material::use(std::shared_ptr<Shader> activeShader){
    GLuint shader = activeShader->getHandle();
    switch(m_colorSource){
        case ColorSource::SOLID_COLOR:
            glUniform1i(glGetUniformLocation(shader, "colorSource"), 0);
            glUniform3f(glGetUniformLocation(shader, "objColor"), m_color.r, m_color.g, m_color.b);
            break;
        case ColorSource::TEXTURE_COLOR:
            glUniform1i(glGetUniformLocation(shader, "colorSource"), 1);
            m_texture->bind();
            glUniform1i(glGetUniformLocation(shader, "objTexture"), m_texture->getTexUnit());
            break;
        case ColorSource::PER_VERTEX_COLOR:
            glUniform1i(glGetUniformLocation(shader, "colorSource"), 2);
            break;
    }
    glUniform1f(glGetUniformLocation(shader, "shininess"), m_shininess);
}