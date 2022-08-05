#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Structs.hpp"

class Bone
{
	public:
		Bone(const char* name) : _name(name) {}

	public:
		void setID(unsigned short ID) { _ID = ID; }
		void setOffset(const glm::mat4& mat) { _offset = mat; }
		void setPositions(const std::vector<KeyPosition>& pos) { _positions = pos; }
	    void setRotations(const std::vector<KeyRotation>& rot) { _rotations = rot; }
		void setScales(const std::vector<KeyScale>& scl) { _scales = scl; }
		void setChildren(const std::vector<unsigned short>& chld) { _children = chld; }

	public:
		unsigned short						ID() const { return _ID; };
		const std::string&					name() const { return _name; };
		const std::vector<unsigned short>&	children() const { return _children; } 

	private:
		unsigned short				_ID;
		std::string					_name;
		glm::mat4					_offset;
		std::vector<KeyPosition>	_positions;
		std::vector<KeyRotation>	_rotations;
		std::vector<KeyScale>		_scales;
		std::vector<unsigned short>	_children;
};
