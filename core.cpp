#include "core.h"
//#include "debug.h"

Core::Core(){
    std::vector<GLfloat> triangleData =
    {   //    POSITIONS    //    COLORS    //
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    //std::cout<<"ADD SHAPE FROM CORE"<<std::endl;
    Global::graphics.addShape("triangle", triangleData, VAOAttrib::POS | VAOAttrib::COLOR);

    glClearColor(0.0, 0.0, 0.0, 1.0);
}

Core::~Core(){

}

void Core::update(float seconds){
    Global::graphics.clearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Debug::checkGLError();

    Global::graphics.bindShader();
    Debug::checkGLError();

    Global::graphics.drawShape("cube");
    Debug::checkGLError();

    Global::graphics.drawShape("triangle");
    Debug::checkGLError();
}

void Core::keyEvent(int key, int action){
    
}