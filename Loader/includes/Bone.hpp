#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
// #include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp

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
			if (_positions.size() == 0)
				return glm::vec3(0.0f);
			if (_positions.size() == 1)
				return _positions[0].position;
			const KeyPosition* last = &_positions[0];
			const KeyPosition* next = &_positions[1];
			for (auto i = 1; i < _positions.size() - 1; ++i){
				if (_positions[i].timestamp > time)
					break ;
				last = &_positions[i];
				next = &_positions[i + 1];
			}
			return glm::mix(last->position, next->position,
				getInterpolant(time, last->timestamp, next->timestamp));
		}

		glm::mat4 currentRot(float time){
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

		glm::vec3 currentScale(float time){
			if (_scales.size() == 0)
				return glm::vec3(1.0f);
			if (_scales.size() == 1)
				return _scales[0].scale;
			const KeyScale* last = &_scales[0];
			const KeyScale* next = &_scales[1];
			for (auto i = 1; i < _scales.size() - 1; ++i){
				if (_scales[i].timestamp > time)
					break ;
				last = &_scales[i];
				next = &_scales[i + 1];
			}
			return glm::mix(last->scale, next->scale,
				getInterpolant(time, last->timestamp, next->timestamp));
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
		const std::vector<KeyRotation>&		rotations() const { return _rotations; }  
		const std::vector<KeyScale>&		scales() const { return _scales; } 

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
