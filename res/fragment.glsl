#version 330

in vec2 oTexCoord;
in vec3 oNormal;
in vec3 oFragPos;

struct Light
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight
{
    Light base;
    vec3  direction;
};

struct PointLight
{
    Light base;
    vec3 position;

    float constant;
    float linear;
    float exponent;
};

struct Material
{
    float specularIntensity;
    float shininess;
};

out vec4                 color;
uniform sampler2D        textureSampler;
uniform DirectionalLight directionalLight;
uniform Material         uMaterial;

uniform vec3 uEyePosition;

void main()
{
    vec4  ambientColor  = vec4(directionalLight.base.color, 1.0f) * directionalLight.base.ambientIntensity;
    float diffuseFactor = max(dot(normalize(oNormal), normalize(directionalLight.direction)), 0.0f);
    vec4  diffuseColor  = vec4(directionalLight.base.color, 1.0f) * directionalLight.base.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (diffuseFactor > 0.0f)
    {
        vec3  fragToEye       = normalize(uEyePosition - oFragPos);
        vec3  reflectedVertex = normalize(reflect(directionalLight.direction, normalize(oNormal)));
        float specularFactor  = dot(fragToEye, reflectedVertex);

        if (specularFactor > 0.0f)
        {
            specularFactor = pow(specularFactor, uMaterial.shininess);
            specularColor  = vec4(directionalLight.base.color * uMaterial.specularIntensity * specularFactor, 1.0f);
        }
    }

    color = texture(textureSampler, oTexCoord) * (ambientColor + diffuseColor + specularColor);
}
