#version 330 core

in vec3 outPos;
in vec2 outTex;
in vec3 outNor;

out vec4 FragColor;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

uniform sampler2D texDiffuse1;


void main() {
    vec3 objectColor            = texture(texDiffuse1, outTex).xyz;
    // ambient lighting
    float ambientStrength       = 0.1;
    vec3 ambient                = ambientStrength * lightColor;
    // diffuse lighting
    vec3 norm                   = normalize(outNor);
    vec3 lightDir               = normalize(lightPos - outPos);
    float diff                  = max(dot(norm, lightDir), 0.0);
    vec3 diffuse                = diff * lightColor;
    // specular lighting
    float specularStrength      = 0.5;
    vec3 viewDir                = normalize(viewPos - outPos);
    vec3 reflectDir             = reflect(-lightDir, norm);  
    float spec                  = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular               = specularStrength * spec * lightColor;  
    vec3 result                 = (ambient + diffuse + specular) * objectColor;
    FragColor                   = vec4(result, 1.0);
}
