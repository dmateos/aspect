#version 400
in vec3 nm_out;
out vec4 frag_colour;

void main() {
  vec3 light_dir = vec3(1.0, 1.0, 1.0);
  float light = max(0.6, dot(nm_out, light_dir));
	frag_colour = vec4(1.0, 0.0, 0.0, 1.0) * light;
}
