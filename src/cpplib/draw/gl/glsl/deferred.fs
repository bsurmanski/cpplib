#version 130

uniform sampler2D t_color;

smooth in vec2 fuv;

out vec4 out_color;

void main()
{
    out_color = texture(t_color, fuv); 
}
