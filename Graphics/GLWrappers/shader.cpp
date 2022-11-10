#include "shader.h"

Shader::Shader(std::vector<GLenum> shaderTypes, std::vector<const char*> filepaths){
    m_handle = ShaderLoader::createShaderProgram(shaderTypes, filepaths);  
    unbind();
}

Shader::~Shader(){
    glDeleteProgram(m_handle);
}

void Shader::bind(){
    glUseProgram(m_handle);
}

void Shader::unbind(){
    glUseProgram(0);
}

GLuint Shader::getHandle(){
    return m_handle;
}

void Shader::setMaterial(std::shared_ptr<Material> material){
    ColorSource color_source = material->getColorSource();
    switch(color_source){
        case ColorSource::SOLID_COLOR:
            glUniform1i(glGetUniformLocation(m_handle, "colorSource"), 0);
            glUniform3f(glGetUniformLocation(m_handle, "objColor"), material->getColor().r, material->getColor().g, material->getColor().b);
            break;
        case ColorSource::TEXTURE_COLOR:
            glUniform1i(glGetUniformLocation(m_handle, "colorSource"), 1);
            material->getTexture()->bind();
            glUniform1i(glGetUniformLocation(m_handle, "objTexture"), material->getTexture()->getTexUnitUint());
            break;
        case ColorSource::PER_VERTEX_COLOR:
            glUniform1i(glGetUniformLocation(m_handle, "colorSource"), 2);
            break;
    }
    float shininess = material->getShininess();
    glUniform1f(glGetUniformLocation(m_handle, "shininess"), shininess);
}

void Shader::setCamera(std::shared_ptr<Camera> camera){
    glUniformMatrix4fv(glGetUniformLocation(m_handle, "view"), 1, GL_FALSE, glm::value_ptr(camera->getView()[0]));
    glUniformMatrix4fv(glGetUniformLocation(m_handle, "projection"), 1, GL_FALSE, glm::value_ptr(camera->getProjection()[0]));
}

void Shader::setModelTransform(std::shared_ptr<ModelTransform> modelTransform){
    glUniformMatrix4fv(glGetUniformLocation(m_handle, "model"), 1, GL_FALSE, glm::value_ptr(modelTransform->getModelMatrix()[0]));
}

void Shader::setGlobalCoeffs(glm::vec3 coeffs){
    glUniform3f(glGetUniformLocation(m_handle, "coeffs"), coeffs.x, coeffs.y, coeffs.z);
}

void Shader::setLights(std::vector<std::shared_ptr<Light>> lights, std::shared_ptr<Camera> camera){
    int numLights = std::min(int(lights.size()), 16);
    std::vector<int> lightType;
    std::vector<float> lightColor;
    std::vector<float> lightFunction;
    std::vector<float> camSpace_lightPos;
    std::vector<float> camSpace_lightDir;
    lightType.resize(numLights);
    lightColor.resize(numLights*3);
    lightFunction.resize(numLights*3);
    camSpace_lightPos.resize(numLights*3);
    camSpace_lightDir.resize(numLights*3);
    for(int i = 0; i<numLights; i++){
        lightColor[i*3] = lights[i]->getColor().r;
        lightColor[i*3+1] = lights[i]->getColor().g;
        lightColor[i*3+2] = lights[i]->getColor().b;
        glm::vec3 camLightData;
        switch(lights[i]->getType()){
            case LightType::POINT:
                lightType[i] = 0;
                lightFunction[i*3] = lights[i]->getAttenuation().x;
                lightFunction[i*3+1] = lights[i]->getAttenuation().y;
                lightFunction[i*3+2] = lights[i]->getAttenuation().z;
                camLightData = glm::vec3(camera->getView()*glm::vec4(lights[i]->getPos(), 1));
                camSpace_lightPos[i*3] = camLightData.x;
                camSpace_lightPos[i*3+1] = camLightData.y;
                camSpace_lightPos[i*3+2] = camLightData.z;
                break;
            case LightType::DIRECTIONAL:
                lightType[i] = 1;
                camLightData = glm::vec3(camera->getView()*glm::vec4(lights[i]->getDir(), 0));
                camSpace_lightPos[i*3] = camLightData.x;
                camSpace_lightPos[i*3+1] = camLightData.y;
                camSpace_lightPos[i*3+2] = camLightData.z;
                break;
        }
    }
    glUniform1i(glGetUniformLocation(m_handle, "numLights"), numLights);
    glUniform1iv(glGetUniformLocation(m_handle, "lightType"), numLights, lightType.data());
    glUniform3fv(glGetUniformLocation(m_handle, "lightColor"), numLights, lightColor.data());
    glUniform3fv(glGetUniformLocation(m_handle, "lightFunction"), numLights, lightFunction.data());
    glUniform3fv(glGetUniformLocation(m_handle, "camSpace_lightPos"), numLights, camSpace_lightPos.data());
    glUniform3fv(glGetUniformLocation(m_handle, "camSpace_lightDir"), numLights, camSpace_lightDir.data());
}

void Shader::clearLights(){
    glUniform1i(glGetUniformLocation(m_handle, "numLights"), 0);
}