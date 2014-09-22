#version 400
in vec3 nm_out;
out vec4 frag_colour;

void main() {
	frag_colour = vec4(nm_out,1.0);
}
