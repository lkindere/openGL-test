//Shapes
float circleshape(vec2 position, float radius){
	return step(radius, length(position - vec2(0.5)));
}
float rectshape(vec2 position, vec2 scale){
	scale = vec2(0.5) - scale * 0.5;
	vec2 shaper = vec2(step(scale.x, position.x), step(scale.y, position.y));
	shaper *= vec2(step(scale.x, 1.0 - position.x), step(scale.y, 1.0 - position.y));
	return shaper.x * shaper.y;
}
float polygonshape(vec2 position, float radius, float sides){
	position = position * 2.0 - 1.0;
	float angle = atan(position.x, position.y);
	float slice = PI * 2.0 / sides;
	return step(radius, cos(floor(0.5 + angle / slice) * slice - angle) * length(position));
}

//Transformations
mat2 scale(vec2 scale){
	return mat2(scale.x, 0.0, 0.0, scale.y);
}
mat2 rotate(float angle){
	return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}