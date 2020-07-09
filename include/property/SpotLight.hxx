#ifndef OPENGL_PBR_SPOTLIGHT_HXX
#define OPENGL_PBR_SPOTLIGHT_HXX

#include "PointLight.hxx"

class SpotLight : public PointLight
{
public:
    SpotLight(
            glm::vec3                color,
            float                    aIntensity,
            std::shared_ptr<Shader>& shader,
            float                    dIntensity,
            glm::vec3                position,
            float                    constant,
            float                    linear,
            float                    exponent,
            int                      lightIndex,
            glm::vec3                direction,
            float                    edge);
    ~SpotLight();

    void setFlash(glm::vec3 pos, glm::vec3 dir);
    void use() override;

private:
    glm::vec3 mDirection;
    float     mEdge;
    float     mProcessedEdge;
};

#endif  // OPENGL_PBR_SPOTLIGHT_HXX
