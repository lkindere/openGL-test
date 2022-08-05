#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Structs.hpp"

#include <glm/glm.hpp>

#include <iostream>

class Bone
{
	public:
		Bone(const char* name) : _name(name) {}

	float getInterpolant(float time, float t1, float t2){
		return ((time - t1) / (t2 - t1));
	}

	public:
		glm::vec3 currentPos(float time){
			// std::cout << "Positions size: " << _positions.size() << std::endl;
			if (_positions.size() == 0)
				return glm::vec3(0.0f);
			if (_positions.size() == 1)
				return _positions[0].position;
			KeyPosition& last = _positions[0];
			KeyPosition& next = _positions[1];
			for (auto i = 1; i < _positions.size() - 1; ++i){
				if (_positions[i].timestamp > time)
					break ;
				last = _positions[i];
				next = _positions[i + 1];
			}
			std::cout << "Time: " << time << std::endl;
			std::cout << "Last: " << last.timestamp << std::endl;
			std::cout << "Next: " << next.timestamp << std::endl;
			return glm::mix(last.position, next.position, getInterpolant(time, last.timestamp, next.timestamp));
		}

	public:
		void setID(unsigned short ID) { _ID = ID; }
		void setOffset(const glm::mat4& mat) { _offset = mat; }
		void setRelative(const glm::mat4& mat) { _relative = mat; }
		void setPositions(const std::vector<KeyPosition>& pos) { _positions = pos; }
	    void setRotations(const std::vector<KeyRotation>& rot) { _rotations = rot; }
		void setScales(const std::vector<KeyScale>& scl) { _scales = scl; }
		void setChildren(const std::vector<unsigned short>& chld) { _children = chld; }

	public:
		unsigned short						ID() const { return _ID; };
		const std::string&					name() const { return _name; };
		const std::vector<unsigned short>&	children() const { return _children; }
		const std::vector<KeyPosition>&		positions() const { return _positions; } 

	private:
		unsigned short				_ID;
		std::string					_name;
		//Matrix that transforms from mesh space to bone space in bind pose
		glm::mat4					_offset;
		//Matrix transformation relative to node parent
		glm::mat4					_relative;
		std::vector<KeyPosition>	_positions;
		std::vector<KeyRotation>	_rotations;
		std::vector<KeyScale>		_scales;
		std::vector<unsigned short>	_children;
};
