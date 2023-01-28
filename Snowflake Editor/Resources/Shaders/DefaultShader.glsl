#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Position;

void main() 
{
    v_Position = a_Position;
    
    gl_Position = vec4(a_Position, 1.0);
}

#type fragment
#version 460 core

out vec4 o_FragmentColor;

in vec3 v_Position;

void main()
{
    o_FragmentColor = vec4(v_Position * 0.5 + 0.9, 1.0);
}