#pragma once

#include "global.h"

#include <GLFW/glfw3.h>

#include "Graphics/GLWrappers/fbo.h"

class Core
{
public:
    Core();
    ~Core();
    void update(float seconds);
    void keyEvent(int key, int action);
    void resizeEvent(int width, int height);

private:
    float m_angle;
    std::vector<std::shared_ptr<Light>> m_lights;

    std::shared_ptr<Shape> m_triangle;
    std::shared_ptr<Shape> m_cone;
    std::shared_ptr<ModelTransform> m_triangleModelTransform;
    std::shared_ptr<ModelTransform> m_coneModelTransform;
    std::shared_ptr<Material> m_perVertexMaterial;
    std::shared_ptr<Material> m_grassMaterial;
};