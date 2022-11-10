#include "camera.h"

Camera::Camera(int width, int height, glm::vec3 pos, glm::vec3 look, 
    glm::vec3 up, float fov, float nearPlane, float farPlane):
    m_width(width),
    m_height(height),
    m_pos(pos),
    m_look(look),
    m_up(up),
    m_fov(fov),
    m_aspect(width/float(height)),
    m_near(nearPlane),
    m_far(farPlane)
{
    calculateProjection();
    calculateView();
}

Camera::~Camera(){
    
}

glm::mat4 Camera::getProjection(){
    return m_proj;
}

glm::mat4 Camera::getView(){
    return m_view;
}

void Camera::resize(int width, int height){
    m_width = width;
    m_height = height;
    m_aspect = width/float(height);

    calculateProjection();
}

void Camera::translate(glm::vec3 move){
    m_pos += move;

    calculateView();
}

void Camera::setPos(glm::vec3 newPos){
    m_pos = newPos;

    calculateView();
}

void Camera::rotate(float angle, glm::vec3 axis){
    m_look = glm::vec3(glm::rotate(glm::mat4(1), angle, axis) * glm::vec4(m_look, 0));

    calculateView();
}

void Camera::setLook(glm::vec3 newLook){
    m_look = newLook;

    calculateView();
}

void Camera::calculateProjection(){
    m_proj = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void Camera::calculateView(){
    m_view = glm::lookAt(m_pos, m_pos+m_look, m_up);
}