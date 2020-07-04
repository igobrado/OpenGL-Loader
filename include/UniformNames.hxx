#ifndef OPENGL_PBR_UNIFORM_NAMES_HXX
#define OPENGL_PBR_UNIFORM_NAMES_HXX

constexpr const char* uModel             = "uModel";
constexpr const char* uProjection        = "uProjection";
constexpr const char* uView              = "uView";
constexpr const char* uAmbientIntensity  = "directionalLight.ambientIntensity";
constexpr const char* uColor             = "directionalLight.color";
constexpr const char* uDiffuseIntensity  = "directionalLight.diffuseIntensity";
constexpr const char* uDirection         = "directionalLight.direction";
constexpr const char* uSpecularIntensity = "uMaterial.specularIntensity";
constexpr const char* uShininess         = "uMaterial.shininess";
constexpr const char* uEyePosition       = "uEyePosition";

#endif  //! OPENGL_PBR_UNIFORM_NAMES_HXX