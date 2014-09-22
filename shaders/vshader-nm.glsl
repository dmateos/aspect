#version 400

in vec3 vp;
in vec3 nm;
out vec3 nm_out;
uniform mat4 transform;
uniform mat4 camera;

void main() {
  nm_out = nm;
	gl_Position =  camera * transform * vec4(vp, 1.0);
}
