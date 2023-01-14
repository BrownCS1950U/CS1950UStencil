#include "core.h"

Core::Core(){

}

Core::~Core(){

}

void Core::update(double seconds){

}

void Core::draw(double timeSinceLastUpdate){
    Global::graphics.clearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::shared_ptr<ModelTransform> testModel = std::make_shared<ModelTransform>();
    testModel->translate(glm::vec3(0, 0, 2));
    std::shared_ptr<Camera> testCamera = std::make_shared<Camera>();
    Global::graphics.setCameraData(testCamera);
    Global::graphics.setGlobalData();
    Global::graphics.drawShape(Global::graphics.getShape("cube"), testModel);
}

void Core::keyEvent(int key, int action){

}

void Core::mousePosEvent(double xpos, double ypos){

}

void Core::mouseButtonEvent(int button, int action){

}

void Core::framebufferResizeEvent(int width, int height){
    glViewport(0, 0, width, height);
    Debug::checkGLError();
}

void Core::windowResizeEvent(int width, int height){

}