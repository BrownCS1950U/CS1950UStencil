#include "core.h"

Core::Core(){
    Global::graphics.addShape("test", "Resources/Meshes/ceiling.obj");
}

Core::~Core(){
}

void Core::update(double deltaTime){
}

void Core::draw(){
    Global::graphics.clearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Global::graphics.bindShader("text");
    Global::graphics.drawUIText(Global::graphics.getFont("opensans"), "Welcome to CS1950U!", glm::ivec2(80, 260), AnchorPoint::TopLeft, Global::graphics.getFramebufferSize().x, 1.f, 0.1f, glm::vec3(1, 0, 1));
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
