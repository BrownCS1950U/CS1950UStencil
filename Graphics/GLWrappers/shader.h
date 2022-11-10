#pragma once

#include "../shaderloader.h"
#include "../camera.h"
#include "../material.h"
#include "../modeltransform.h"
#include "../light.h"

class Shader{
public:
    Shader(std::vector<GLenum> shaderTypes, std::vector<const char*> filepaths);
    ~Shader();

    void bind();
    void unbind();
    GLuint getHandle();
    void setMaterial(std::shared_ptr<Material> material);
    void setCamera(std::shared_ptr<Camera> camera);
    void setModelTransform(std::shared_ptr<ModelTransform> modelTransform);
    void setGlobalCoeffs(glm::vec3 coeffs);
    void setLights(std::vector<std::shared_ptr<Light>> lights, std::shared_ptr<Camera> camera);
    void clearLights();

private:
    GLuint m_handle;
};