#ifdef GL_ES
precision mediump float;
#endif

const float PI = 3.1415926535;

uniform vec2 u_resolution;
uniform float u_time;

//Main
void main(){

	//Cool waves and stuff
	vec2 position = 6.0 * gl_FragCoord.xy / u_resolution;
	vec3 color = vec3(0.0);

	for (int n = 1; n < 100; n++){
		float i = float(n);
		position += vec2(0.7 / i * sin(i * position.y + u_time + 0.3 * i) + 0.8, 0.4 / i * sin(position.x + u_time + 0.3 * i) + 1.6);
	}
	color += vec3(0.4 * sin(position.x) + 0.5, 0.5 * sin(position.y) + 0.5, sin(position.x + position.y));
	
	//Weirdness generator
	// color += sin(position.x * cos(u_time / 30.0) * 60.0) + sin(position.y * cos(u_time / 15.0) * 10.0);
	// color += cos(position.y * sin(u_time / 40.0) * 60.0) + cos(position.x * sin(u_time / 30.0) * 10.0);

	//Move shapes in the screen
	// vec2 translate = vec2(sin(u_time / 2.0), cos(u_time / 4.0));
	// position += translate * 0.5;

	//Shrinks and expands
	// position -= vec2(0.5);
	// position = scale(vec2(sin(u_time) + 2.0)) * position;
	// position += vec2(0.5);

	//Rotate
	// position -= vec2(0.5);
	// position = rotate(sin(u_time)) * position;
	// position += vec2(0.5);

	// float circle = circleshape(position, 0.1);
	// float rectangle = rectshape(position, vec2(0.1));
	// float polygon = polygonshape(position, 0.3, 5.0);

	// color = vec3(circle);
	// color = vec3(rectangle);
	// color += vec3(polygon);

	gl_FragColor = vec4(color, 1.0);
}

