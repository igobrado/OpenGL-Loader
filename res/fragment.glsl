#version 330

in vec2 oTexCoord;
in vec3 oNormal;
in vec3 oFragPos;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS  = 3;

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

struct SpotLight
{
    PointLight base;
    vec3       direction;
    float      edge;
};

struct Material
{
    float specularIntensity;
    float shininess;
};

out vec4                 color;
uniform int              uPointLightCount;
uniform int              uSpotLightCount;
uniform sampler2D        textureSampler;
uniform DirectionalLight uDirectionalLight;
uniform Material         uMaterial;
uniform PointLight       uPointLights[MAX_POINT_LIGHTS];
uniform SpotLight        uSpotLights[MAX_SPOT_LIGHTS];
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

vec4 calculatePointLight(PointLight pLight)
{
    vec3  direction = oFragPos - pLight.position;
    float distance  = length(direction);
    direction       = normalize(direction);

    vec4  color       = calculateLightByDirection(pLight.base, direction);
    float attenuation = pLight.exponent * distance * distance + pLight.linear * distance + pLight.constant;

    return (color / attenuation);
}

vec4 calculateOneSpotLight(SpotLight sLight)
{
    vec3  rayDirection    = normalize(oFragPos - sLight.base.position);
    float spotLightFactor = dot(rayDirection, sLight.direction);

    if (spotLightFactor > sLight.edge)
    {
        vec4 color = calculatePointLight(sLight.base);
        return color * (1.0f - (1.0f - spotLightFactor) * (1.0f / (1.0f - sLight.edge)));
    }
    else
    {
        return vec4(0, 0, 0, 0);
    }
}

vec4 calculatePointLights()
{
    vec4 totalColor = vec4(0, 0, 0, 0);
    for (int i = 0; i < uPointLightCount; i++)
    {
        totalColor += calculatePointLight(uPointLights[i]);
    }
    return totalColor;
}

vec4 calculateSpotLights()
{
    vec4 totalColor = vec4(0, 0, 0, 0);
    for (int i = 0; i < uSpotLightCount; i++)
    {
        totalColor += calculateOneSpotLight(uSpotLights[i]);
    }
    return totalColor;
}

void main()
{

    vec4 finalColor = calculateLightByDirection(uDirectionalLight.base, uDirectionalLight.direction);
    finalColor += calculatePointLights();
    finalColor += calculateSpotLights();

    color = texture(textureSampler, oTexCoord) * finalColor;
}
