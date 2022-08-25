#include "camera.h"

Camera::Camera(glm::vec2 screenSize, glm::vec3 pos, glm::vec3 look, 
    glm::vec3 up, float fov, float nearPlane, float farPlane, float orthoDepth, 
    ProjectionMode mode):
    m_screenSize(screenSize),
    m_pos(pos),
    m_look(look),
    m_up(up),
    m_fov(fov),
    m_aspect(m_screenSize.x/m_screenSize.y),
    m_near(nearPlane),
    m_far(farPlane),
    m_orthoDepth(orthoDepth),
    m_mode(mode)
{
    setProjection();
    setView();
}

Camera::~Camera(){
    
}

glm::mat4 Camera::getProjection(){
    return m_proj;
}

glm::mat4 Camera::getView(){
    return m_view;
}

void Camera::resize(glm::vec2 screenSize){
    m_screenSize = screenSize;
    m_aspect = m_screenSize.x/m_screenSize.y;

    setProjection();
}

void Camera::translate(glm::vec3 move){
    m_pos += move;

    setView();
}

void Camera::setPos(glm::vec3 newPos){
    m_pos = newPos;

    setView();
}

void Camera::rotate(float angle, glm::vec3 axis){
    m_look = glm::vec3(glm::rotate(glm::mat4(1), angle, axis) * glm::vec4(m_look, 0));

    setView();
}

void Camera::setLook(glm::vec3 newLook){
    m_look = newLook;

    setView();
}

void Camera::setProjectionMode(ProjectionMode newMode){
    m_mode = newMode;

    setProjection();
}

void Camera::setProjection(){
    switch(m_mode){
        case ProjectionMode::PERSPECTIVE:
            m_proj = glm::perspective(m_fov, m_aspect, m_near, m_far);
            break;
        case ProjectionMode::ORTHOGRAPHIC:
            float ratio_size_per_depth = atan(glm::radians(m_fov/2.0f) * 2.0f);
            float size_y = ratio_size_per_depth * m_orthoDepth;
            float size_x = ratio_size_per_depth * m_orthoDepth * m_aspect;
            m_proj = glm::ortho(-size_x, size_x, -size_y, size_y, 0.0f, m_far);
            break;
    }
}

void Camera::setView(){
    m_view = glm::lookAt(m_pos, m_pos+m_look, m_up);
}