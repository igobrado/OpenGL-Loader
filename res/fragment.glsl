#version 330

in vec2 oTexCoord;
in vec4 vColor;

out vec4 color;
uniform sampler2D textureSampler;

void main()
{
    color = texture(textureSampler, oTexCoord);
}
