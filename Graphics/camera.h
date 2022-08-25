#pragma once

#include "glm/glm.hpp"
#include "glm/ext.hpp"

enum ProjectionMode{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera
{
public:
    Camera(glm::vec2 screenSize = glm::vec2(1.0, 1.0),
    glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 look = glm::vec3(0, -1, 0), 
    glm::vec3 up = glm::vec3(0, 1, 0), float fov = 1.f, 
    float nearPlane = 0.1f, float farPlane = 100.f, float orthoDepth = 10.f,
    ProjectionMode mode = ProjectionMode::PERSPECTIVE);
    ~Camera();

    // Functions to get camera data for drawing
    glm::mat4 getProjection();
    glm::mat4 getView();

    // Functions to edit camera
    void resize(glm::vec2 screenSize);
    void translate(glm::vec3 move);
    void setPos(glm::vec3 newPos);
    void rotate(float angle, glm::vec3 axis);
    void setLook(glm::vec3 newLook);
    void setProjectionMode(ProjectionMode newMode);

private:
    // Internal functions to update projection and view matrices
    void setProjection();
    void setView();

    glm::vec2 m_screenSize;
    glm::vec3 m_pos;
    glm::vec3 m_look;
    glm::vec3 m_up;
    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;
    float m_orthoDepth;
    ProjectionMode m_mode;

    glm::mat4 m_proj;
    glm::mat4 m_view;
};