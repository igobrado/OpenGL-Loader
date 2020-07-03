#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 norm;

out vec4 vColor;
out vec2 oTexCoord;
out vec3 oNormal;
out vec3 oFragPos;

uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uView;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(pos, 1.0);
    vColor      = vec4(clamp(pos, 0.0f, 1.0f), 1.0);

    oTexCoord = tex;
    oNormal   = mat3(transpose(inverse(uModel))) * norm;

    oFragPos = (uModel * vec4(pos, 1.0)).xyz;
}