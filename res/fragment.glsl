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
uniform DirectionalLight uDirectionalLight;
uniform Material         uMaterial;
uniform PointLight       uPointLight;
uniform vec3             uEyePosition;

vec4 calculateLightByDirection(Light light, vec3 direction)
{
    vec4  ambientColor  = vec4(light.color, 1.0f) * light.ambientIntensity;
    float diffuseFactor = max(dot(normalize(oNormal), normalize(direction)), 0.0f);
    vec4  diffuseColor  = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (diffuseFactor > 0.0f)
    {
        vec3  fragToEye       = normalize(uEyePosition - oFragPos);
        vec3  reflectedVertex = normalize(reflect(direction, normalize(oNormal)));
        float specularFactor  = dot(fragToEye, reflectedVertex);

        if (specularFactor > 0.0f)
        {
            specularFactor = pow(specularFactor, uMaterial.shininess);
            specularColor  = vec4(light.color * uMaterial.specularIntensity * specularFactor, 1.0f);
        }
    }
    return (ambientColor + diffuseColor + specularColor);
}

void main()
{

    vec4 totalLight = calculateLightByDirection(uDirectionalLight.base, uDirectionalLight.direction);
    color = texture(textureSampler, oTexCoord) * totalLight;
}
