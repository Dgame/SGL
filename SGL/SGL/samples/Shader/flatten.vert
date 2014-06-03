uniform float time;
uniform float wnd_height;

void main() {
	vec4 v = vec4(gl_Vertex);
	v.y = v.y + 0.91 * time;

	if (v.y < wnd_height)
		gl_Position = gl_ModelViewProjectionMatrix * v;
	else
		gl_Position = ftransform();
}