#version 400

in vec3 vp;
uniform mat4 translate;
uniform mat4 camera;

void main() {
	gl_Position =  camera * translate * vec4(vp, 1.0);
}
