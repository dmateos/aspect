#version 400

in vec3 vp;
in vec2 tex;
in vec3 nm;
out vec2 tex_out;
out vec3 nm_out;
uniform mat4 translate;
uniform mat4 camera;

void main() {
  tex_out = tex;
  nm_out = nm;
	gl_Position =  camera * translate * vec4(vp, 1.0);
}
