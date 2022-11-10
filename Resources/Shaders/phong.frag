#version 330 core
// Uniforms for shape information
in vec4 camSpace_pos;
in vec4 camSpace_norm;
in vec2 tex_coord;

// Object Material Data
uniform int colorSource; // 0 = solid color (objColor), 1 = texture color (objTexture), 2 = per-vertex color (vertColor)
uniform vec3 objColor;
uniform sampler2D objTexture;
in vec3 vertColor;
uniform float shininess;

// Uniforms for coordinate space transforms
uniform mat4 model, view, projection;

// Global Data
uniform vec3 coeffs; // vec3(ka, kd, ks)

// Light Data
uniform int lightType[8]; // 0 = point light, 1 = directional light, 2 = spot light
uniform vec3 lightColor[8];
uniform vec3 lightFunction[8]; // Attenuation coefficients
uniform vec3 camSpace_lightPos[8]; //Light Positions
uniform vec3 camSpace_lightDir[8]; //Light Directions
uniform int numLights; // Max number of lights = 8

out vec4 fragColor;

vec4 getToLight(int lightIndex) {
    int LIGHT_POINT = 0;
    int LIGHT_DIRECTIONAL = 1;
    int LIGHT_SPOT = 2;

    if (lightType[lightIndex] == LIGHT_POINT) {
        return vec4(normalize(camSpace_lightPos[lightIndex] - vec3(camSpace_pos)), 0);
    }
    else if (lightType[lightIndex] == LIGHT_DIRECTIONAL) {
        return vec4(normalize(-camSpace_lightDir[lightIndex]), 0);
    }

    return vec4(0);
}

float attenuationFactor(int lightIndex) {
    int LIGHT_POINT = 0;

    if (lightType[lightIndex] == LIGHT_POINT) {
        vec3 coeffs = lightFunction[lightIndex];
        float d = length(camSpace_lightPos[lightIndex] - vec3(camSpace_pos));
        return 1.0 / (coeffs.x + coeffs.y * d + coeffs.z * d * d);
    }

    return 1;
}

float computeDiffuseIntensity(vec3 camSpace_toLight) {
    // Dot product to get diffuse intensity
    return max(dot(camSpace_toLight, normalize(vec3(camSpace_norm))), 0);
}

float computeSpecularIntensity(vec3 camSpace_toLight, vec3 camSpace_toEye) {
    // Guard against pow weirdness when exponent is 0
    if (shininess < 0.0001) {
        return 0;
    }

    //reflect toLight
    vec3 camSpace_toLightReflected = reflect(-camSpace_toLight, normalize(vec3(camSpace_norm)));

    //Compute specular intensity using toEye, reflected light, and shininess
    return pow(max(dot(camSpace_toLightReflected, camSpace_toEye), 0), shininess);
}

void main() {
    // Declare ambient, diffuse, and specular terms
    vec3 ambi = vec3(coeffs.x);
    vec3 diff = vec3(0.0);
    vec3 spec = vec3(0.0);


    // Compute camSpace_toEye Vector for specular intensity computation;
    vec4 camSpace_toEye = vec4(normalize(vec3(-camSpace_pos)), 0);


    // Compute per-light diffuse and specular contribution
    for(int i = 0; i<numLights; i+= 1){

        // get direction vector to light based on light type
        vec4 camSpace_toLight = getToLight(i);

        float diffuse_intensity = computeDiffuseIntensity(vec3(camSpace_toLight));
        float specular_intensity = computeSpecularIntensity(vec3(camSpace_toLight), vec3(camSpace_toEye));

        float att = attenuationFactor(i);


        diff = diff + diffuse_intensity * vec3(lightColor[i]) * att;
        spec = spec + specular_intensity * vec3(lightColor[i]) * att;
    }

    // Apply global coefficients and object color to the diffuse and specular components
    diff = diff * vec3(coeffs.y);
    spec = spec * vec3(coeffs.z);

    // Color generated only from light intensities and colors
    vec3 tempColor = clamp(ambi + diff + spec, 0, 1);

    // Apply correct object color
    if (colorSource == 0 ) {
        fragColor = vec4(tempColor * objColor, 1.0);
    } 
    else if (colorSource == 1){
        fragColor = vec4(tempColor * vec3(texture(objTexture, tex_coord)), 1.0);
    }
    else if (colorSource == 2) {
        fragColor = vec4(tempColor * vertColor, 1.0);
    }
    else{
        fragColor = vec4(tempColor, 1.0);
    }
}