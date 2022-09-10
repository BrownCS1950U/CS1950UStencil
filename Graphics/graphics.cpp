#include "graphics.h"
#include "shapes.h"

Graphics::Graphics(){
    m_camera = std::make_shared<Camera>();
}

Graphics::~Graphics(){

}

void Graphics::initializeGLEW(){
    glewExperimental = GL_TRUE;
    std::cout<<"GLEWInit status: "<<glewInit()<<std::endl;
    initialize();
}

void Graphics::initialize(){
    addShape("cube", cubeVertexBufferData, VAOAttrib::POS | VAOAttrib::NORM | VAOAttrib::UV);
    addShape("sphere", sphereVertexBufferData, VAOAttrib::POS | VAOAttrib::NORM | VAOAttrib::UV);
    addShape("cylinder", cylinderVertexBufferData, VAOAttrib::POS | VAOAttrib::NORM | VAOAttrib::UV);
    addShape("cone", coneVertexBufferData, VAOAttrib::POS | VAOAttrib::NORM | VAOAttrib::UV);
    addShader("default", {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}, {"C:/Users/Logan/course/CS1950UCourseDev/CS1950UStencil/Resources/Shaders/default.vert", "C:/Users/Logan/course/CS1950UCourseDev/CS1950UStencil/Resources/Shaders/default.frag"});
}

void Graphics::clearScreen(GLbitfield mask){
    glClear(mask);
}

std::shared_ptr<Camera> Graphics::getCamera(){
    return m_camera;
}

void Graphics::addShader(std::string shaderName, std::vector<GLenum> shaderTypes, std::vector<const char*> filepaths){
    m_shaders.insert({shaderName, std::make_shared<Shader>(shaderTypes, filepaths)});
}

void Graphics::removeShader(std::string shaderName){
    m_shaders.erase(shaderName);
}

void Graphics::bindShader(std::string shaderName){
    m_shaders.at(shaderName)->bind();
    m_active_shader = m_shaders.at(shaderName);
}

void Graphics::addShape(std::string shapeName, std::vector<float> data, VAOAttrib attribs){
    m_shapes.insert({shapeName, std::make_shared<VAO>(std::make_shared<VBO>(data), attribs)});
}

void Graphics::removeShape(std::string shapeName){
    m_shapes.erase(shapeName);
}

void Graphics::drawShape(std::string shapeName){
    m_shapes.at(shapeName)->draw();
}

void Graphics::addMaterial(std::string materialName, std::shared_ptr<Material> material){
    m_materials.insert({materialName, material});
}

void Graphics::removeMaterial(std::string materialName){
    if(materialName != "default"){
        m_materials.erase(materialName);
    }
}

void Graphics::useMaterial(std::string materialName){
    m_materials.at(materialName)->use(m_active_shader);
}