#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 colorPos;
layout (location = 2) in vec2 aTexCord;

out vec4 ourColor;
out vec2 TexCord;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	ourColor = vec4(colorPos, 1.0);
	TexCord = aTexCord;
}