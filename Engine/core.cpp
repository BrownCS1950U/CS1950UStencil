#include "core.h"

Core::Core(){

}

Core::~Core(){

}

void Core::update(){

}

void Core::draw(){

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