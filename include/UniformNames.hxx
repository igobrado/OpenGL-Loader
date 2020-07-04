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

#endif  //! OPENGL_PBR_UNIFORM_NAMES_HXX