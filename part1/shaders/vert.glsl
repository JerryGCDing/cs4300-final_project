#version 330 core
// Position of the mesh - x, y, z
layout(location=0) in vec3 vertPosition;
// Offset of each particle - x, y, z, (size)
layout(location=1) in vec4 offset;
// Particle color - R, G, B, A
layout(location=2) in vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fragColor;

void main() {
	vec3 position = vertPosition + vec3(offset.x, offset.y, offset.z);
	gl_Position = projection * view * model * vec4(position, 1.0f);

	fragColor = color;
}
