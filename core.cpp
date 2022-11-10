#include "core.h"

Core::Core(){
    m_angle = 0.f;

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);

    std::vector<GLfloat> triangleData =
    {   //    POSITIONS    //    COLORS    //
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    //std::cout<<"ADD SHAPE FROM CORE"<<std::endl;
    m_triangle = Global::graphics.addShape("triangle", triangleData, VAOAttrib::POS | VAOAttrib::COLOR);

    m_triangleModelTransform = std::make_shared<ModelTransform>();

    m_cone = Global::graphics.getShape("cone");

    m_coneModelTransform = std::make_shared<ModelTransform>();

    Global::graphics.getCamera()->translate(glm::vec3(0, 0, -2));

    m_perVertexMaterial = Global::graphics.addMaterial("per-vertex color");

    m_grassMaterial = Global::graphics.addMaterial("grass", "Resources/Images/grass.png");
    Debug::checkGLError();

    m_lights.push_back(std::make_shared<Light>(LightType::DIRECTIONAL, glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)));
}

Core::~Core(){

}

void Core::update(float seconds){
    m_angle += 400 * seconds;

    Global::graphics.clearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Debug::checkGLError();

    Global::graphics.bindShader();
    Debug::checkGLError();

    Global::graphics.clearLights();
    Debug::checkGLError();

    Global::graphics.setGlobalData();
    Debug::checkGLError();

    Global::graphics.setCamera();

    m_coneModelTransform->clear();
    m_coneModelTransform->rotate(glm::radians(m_angle), glm::vec3(0, 1, 1));
    Debug::checkGLError();
    Global::graphics.drawShape(m_cone, m_coneModelTransform, m_grassMaterial);
    Debug::checkGLError();

    m_triangleModelTransform->clear();
    m_triangleModelTransform->rotate(glm::radians(2*m_angle), glm::vec3(0, 0, 1));
    Global::graphics.drawShape(m_triangle, m_triangleModelTransform, m_perVertexMaterial);
    Debug::checkGLError();
}

void Core::keyEvent(int key, int action){
    
}

void Core::resizeEvent(int width, int height){
    glViewport(0, 0, width, height);
    Global::graphics.getCamera()->resize(width, height);
}