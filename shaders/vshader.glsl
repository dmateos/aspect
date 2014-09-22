#version 400

in vec3 vp;
out vec3 nm_out;
uniform mat4 camera;

void main() {
	gl_Position =  camera * vec4(vp, 1.0);
}
