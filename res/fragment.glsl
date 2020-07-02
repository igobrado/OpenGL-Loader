#version 330

in vec2 oTexCoord;
in vec3 oNormal;

struct DirectionalLight
{
    vec3  color;
    float ambientIntensity;
    vec3  direction;
    float diffuseIntensity;
};

out vec4                 color;
uniform sampler2D        textureSampler;
uniform DirectionalLight directionalLight;

void main()
{
    vec4  ambientColor  = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;
    float diffuseFactor = max(dot(normalize(oNormal), normalize(directionalLight.direction)), 0.0f);
    vec4  diffuseColor  = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
    color               = texture(textureSampler, oTexCoord) * (ambientColor + diffuseColor);
}
