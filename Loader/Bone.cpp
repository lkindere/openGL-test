#include "Bone.hpp"

Bone::Bone(const char* name) : _name(name) {}

glm::mat4 Bone::currentMatrix(float time) const {
	glm::mat4 pos = currentPos(time);
	// glm::mat4 rot = currentRot(time);
	// glm::mat4 scale = currentScale(time);
	// return (pos * rot * scale);
    return pos;
}

//Could change all 3 to keep static last pointer for faster iteration
//Not that many frames atm
glm::mat4 Bone::currentPos(float time) const {
	if (_positions.size() == 0)
		return glm::mat4(1.0f);
	if (_positions.size() == 1)
		return glm::translate(glm::mat4(1.0f), _positions[0].position);
	const KeyPosition* last = &_positions[0];
	const KeyPosition* next = &_positions[1];
	for (auto i = 1; i < _positions.size() - 1; ++i){
		if (_positions[i].timestamp > time)
			break ;
		last = &_positions[i];
		next = &_positions[i + 1];
	}
	return glm::translate(glm::mat4(1.0f), glm::mix(last->position, next->position,
		getInterpolant(time, last->timestamp, next->timestamp)));
}

glm::mat4 Bone::currentRot(float time) const {
	if (_rotations.size() == 0)
		return glm::mat4(1.0f);
	if (_rotations.size() == 1)
		return glm::toMat4(_rotations[0].rotation);
	const KeyRotation* last = &_rotations[0];
	const KeyRotation* next = &_rotations[1];
	for (auto i = 1; i < _rotations.size() - 1; ++i){
		if (_rotations[i].timestamp > time)
			break ;
		last = &_rotations[i];
		next = &_rotations[i + 1];
	}
	return glm::toMat4(glm::mix(last->rotation, next->rotation,
		getInterpolant(time, last->timestamp, next->timestamp)));
}

glm::mat4 Bone::currentScale(float time) const {
	if (_scales.size() == 0)
		return glm::mat4(1.0f);
	if (_scales.size() == 1)
		return glm::translate(glm::mat4(1.0f), _scales[0].scale);
	const KeyScale* last = &_scales[0];
	const KeyScale* next = &_scales[1];
	for (auto i = 1; i < _scales.size() - 1; ++i){
		if (_scales[i].timestamp > time)
			break ;
		last = &_scales[i];
		next = &_scales[i + 1];
	}
	return glm::translate(glm::mat4(1.0f), glm::mix(last->scale, next->scale,
		getInterpolant(time, last->timestamp, next->timestamp)));
}

float Bone::getInterpolant(float time, float t1, float t2) const {
	return ((time - t1) / (t2 - t1));
}

//Set
void Bone::setID(unsigned short ID) { _ID = ID; }
void Bone::setOffset(const glm::mat4& mat) { _offset = mat; }
void Bone::setRelative(const glm::mat4& mat) { _relative = mat; }
void Bone::setPositions(const std::vector<KeyPosition>& pos) { _positions = pos; }
void Bone::setRotations(const std::vector<KeyRotation>& rot) { _rotations = rot; }
void Bone::setScales(const std::vector<KeyScale>& scl) { _scales = scl; }
void Bone::setChildren(const std::vector<unsigned short>& chld) { _children = chld; }

//Get
unsigned short						Bone::ID() const { return _ID; };
const std::string&					Bone::name() const { return _name; };
const glm::mat4						Bone::offset() const { return _offset; }
const glm::mat4						Bone::relative() const { return _relative; }
const std::vector<KeyPosition>&		Bone::positions() const { return _positions; }
const std::vector<KeyRotation>&		Bone::rotations() const { return _rotations; }  
const std::vector<KeyScale>&		Bone::scales() const { return _scales; } 
const std::vector<unsigned short>&	Bone::children() const { return _children; }