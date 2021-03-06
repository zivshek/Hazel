#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UV;

uniform mat4 u_ViewProjMat;
uniform mat4 u_Transform;

out vec2 v_UV;

void main()
{
    v_UV = a_UV;
    gl_Position = u_ViewProjMat * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 v_UV;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_UV);
}