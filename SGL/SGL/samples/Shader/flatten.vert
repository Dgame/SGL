uniform float time;

void main() {
	vec4 v = vec4(gl_Vertex);
	//v.z = sin(5.0 * v.x + time) * 0.5;
	v.y = v.y * time * 0.005;
	//v.x = v.x * time * 0.5;
	
	gl_Position = gl_ModelViewProjectionMatrix * v;
}