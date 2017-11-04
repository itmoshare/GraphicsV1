#version 330 core
#extension GL_ARB_separate_shader_objects : enable

in vec3 vertexPosition_modelspace;
uniform mat4 MVP;

void main(){

    // Выходная позиция нашей вершины: MVP * position
    vec4 v = vec4(vertexPosition_modelspace,1);
    gl_Position = MVP * v;
}