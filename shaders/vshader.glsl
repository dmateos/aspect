#version 400

in vec3 vp;
in vec2 tex;
out vec2 tex_out;
uniform mat4 translate;
uniform mat4 camera;

void main() {
  tex_out = tex;
	gl_Position =  camera * translate * vec4(vp, 1.0);
}
