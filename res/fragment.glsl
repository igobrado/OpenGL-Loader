#version 330

in vec2 oTexCoord;
in vec3 oNormal;
in vec3 oFragPos;

const int MAX_POINT_LIGHTS = 3;

struct Light
{
    vec3  color;
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
    vec3  position;

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
uniform int              uPointLightCount;
uniform sampler2D        textureSampler;
uniform DirectionalLight uDirectionalLight;
uniform Material         uMaterial;
uniform PointLight       uPointLights[MAX_POINT_LIGHTS];
uniform vec3             uEyePosition;

vec4 calculateLightByDirection(Light light, vec3 direction)
{
    vec4 ambientColour = vec4(light.color, 1.0f) * light.ambientIntensity;

    float diffuseFactor = max(dot(normalize(oNormal), normalize(direction)), 0.0f);
    vec4  diffuseColour = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);

    vec4 specularColour = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0.0f)
    {
        vec3 fragToEye       = normalize(uEyePosition - oFragPos);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(oNormal)));

        float specularFactor = dot(fragToEye, reflectedVertex);
        if (specularFactor > 0.0f)
        {
            specularFactor = pow(specularFactor, uMaterial.shininess);
            specularColour = vec4(light.color * uMaterial.specularIntensity * specularFactor, 1.0f);
        }
    }

    return (ambientColour + diffuseColour + specularColour);
}

vec4 calculatePointLights()
{
    vec4 totalColor = vec4(0, 0, 0, 0);
    for (int i = 0; i < uPointLightCount; i++)
    {
        vec3  direction = oFragPos - uPointLights[i].position;
        float distance  = length(direction);
        direction       = normalize(direction);

        vec4  color       = calculateLightByDirection(uPointLights[i].base, direction);
        float attenuation = uPointLights[i].exponent * distance * distance + uPointLights[i].linear * distance
                            + uPointLights[i].constant;

        totalColor += (color / attenuation);
    }

    return totalColor;
}

void main()
{

    vec4 finalColor = calculateLightByDirection(uDirectionalLight.base, uDirectionalLight.direction);
    finalColor += calculatePointLights();

    color = texture(textureSampler, oTexCoord) * finalColor;
}
