#pragma once

#include "GLWrappers/vao.h"
#include "camera.h"
#include "GLWrappers/shader.h"
#include "material.h"
#include <map>
#include <GL/glew.h>
#include <memory>
#include <vector>
#include "shape.h"
#include "modeltransform.h"
#include "light.h"

class Graphics
{
public:
    Graphics();
    ~Graphics();

    void initialize();
    void clearScreen(GLbitfield mask);

    std::shared_ptr<Camera> getCamera();
    void setCamera();

    void addShader(std::string shaderName, std::vector<GLenum> shaderTypes, std::vector<const char*> filepaths);
    void removeShader(std::string shaderName);
    void bindShader(std::string shaderName = "default");

    // Shape-related methods
    std::shared_ptr<Shape> addShape(std::string shapeName, std::vector<float> data, VAOAttrib attribs);
    void removeShape(std::string shapeName);
    std::shared_ptr<Shape> getShape(std::string shapeName);
    void drawShape(std::shared_ptr<Shape> myShape, std::shared_ptr<ModelTransform> modelTransform, std::shared_ptr<Material> material);
    void drawShape(std::shared_ptr<Shape> myShape, std::shared_ptr<ModelTransform> modelTransform);
    
    // Material-related methods
    std::shared_ptr<Material> addMaterial(std::string materialName, glm::vec3 color, float shininess = 1.f);
    std::shared_ptr<Material> addMaterial(std::string materialName, float shininess = 1.f);
    std::shared_ptr<Material> addMaterial(std::string materialName, std::string filePath, float shininess = 1.f);
    void removeMaterial(std::string materialName);
    std::shared_ptr<Material> getMaterial(std::string materialName);

    void setGlobalData();
    void setLights(std::vector<std::shared_ptr<Light>> lights);
    void clearLights();

    void initializeGLEW();

private:
    std::shared_ptr<Camera> m_camera;
    std::map<std::string, std::shared_ptr<Shader>> m_shaders;
    std::map<std::string, std::shared_ptr<Shape>> m_shapes;
    std::map<std::string, std::shared_ptr<Material>> m_materials;

    std::shared_ptr<Shader> m_active_shader;
    glm::vec3 m_global_coeffs;
};