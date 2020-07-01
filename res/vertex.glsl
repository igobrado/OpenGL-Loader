#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec4 vColor;
out vec2 oTexCoord;

uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uView;
void main()
{
    gl_Position = uProjection * uView * uModel * vec4(pos, 1.0);
    vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0);

    oTexCoord = tex;
}