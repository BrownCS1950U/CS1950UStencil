#include "core.h"

Core::Core(){
    m_camera = std::make_shared<Camera>();
    Global::graphics.addShape("test", "Resources/Meshes/ceiling.obj");
    m_test = Global::graphics.getShape("test");
    m_trans = std::make_shared<ModelTransform>();
    m_trans->translate(glm::vec3(0, 0, 30));
    Global::graphics.setGlobalData(glm::vec3(0.5, 0.5, 0.5));
}

Core::~Core(){

}

void Core::update(){

}

void Core::draw(){
    Global::graphics.clearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Global::graphics.bindShader("text");
    Global::graphics.drawUIText(Global::graphics.getFont("opensans"), "Welcome to CS1950U!", glm::ivec2(0, 200), AnchorPoint::TopLeft, Global::graphics.getFramebufferSize().x, 1.f, 0.1f, glm::vec3(1, 0, 1));
    Global::graphics.bindShader("phong");
    Global::graphics.setCameraData(m_camera);
    Global::graphics.drawShape(m_test, m_trans);
    Debug::checkGLError();
    m_trans->rotate(0.001f, glm::normalize(glm::vec3(1, 1, 1)));
}

void Core::keyEvent(int key, int action){

}

void Core::mousePosEvent(double xpos, double ypos){

}

void Core::mouseButtonEvent(int button, int action){

}

void Core::scrollEvent(double distance){
    
}

void Core::framebufferResizeEvent(int width, int height){
    Global::graphics.setFramebufferSize(glm::ivec2(width, height));
}

void Core::windowResizeEvent(int width, int height){
    Global::graphics.setWindowSize(glm::ivec2(width, height));
}
