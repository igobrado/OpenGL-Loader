#ifndef OPENGL_PBR_UNIFORM_NAMES_HXX
#define OPENGL_PBR_UNIFORM_NAMES_HXX

constexpr const char* uModel             = "uModel";
constexpr const char* uProjection        = "uProjection";
constexpr const char* uView              = "uView";
constexpr const char* uAmbientIntensity  = "uDirectionalLight.base.ambientIntensity";
constexpr const char* uColor             = "uDirectionalLight.base.color";
constexpr const char* uDiffuseIntensity  = "uDirectionalLight.base.diffuseIntensity";
constexpr const char* uDirection         = "uDirectionalLight.direction";
constexpr const char* uSpecularIntensity = "uMaterial.specularIntensity";
constexpr const char* uShininess         = "uMaterial.shininess";
constexpr const char* uEyePosition       = "uEyePosition";
constexpr const char* uPointLightCount    = "uPointLightCount";

constexpr const char* uBaseCol = ".base.color";
constexpr const char* uBaseAIntensity = ".base.ambientIntensity";
constexpr const char* uBaseDIntensity = ".base.diffuseIntensity";

constexpr const char* uPointLights = "uPointLights";
constexpr const char* uPointLightPos = ".position";
constexpr const char* uPointLightCon = ".constant";
constexpr const char* uPointLightLin = ".linear";
constexpr const char* uPointLightExp = ".exponent";

constexpr const int MAX_POINT_LIGHTS = 3;
#endif  //! OPENGL_PBR_UNIFORM_NAMES_HXX