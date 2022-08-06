#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Structs.hpp"

class Bone
{
	public:
		Bone(const char* name);

	public:
		glm::mat4 currentMatrix(float time) const;
	
	private:
		glm::mat4 currentPos(float time) const;
		glm::mat4 currentRot(float time) const;
		glm::mat4 currentScale(float time) const;
		float getInterpolant(float time, float t1, float t2) const;

	public:
		void setID(unsigned short ID);
		void setOffset(const glm::mat4& mat);
		void setRelative(const glm::mat4& mat);
		void setPositions(const std::vector<KeyPosition>& pos);
	    void setRotations(const std::vector<KeyRotation>& rot);
		void setScales(const std::vector<KeyScale>& scl);
		void setChildren(const std::vector<unsigned short>& chld);

	public:
		unsigned short						ID() const;
		const std::string&					name() const;
		const glm::mat4						offset() const;
		const glm::mat4						relative() const;
		const std::vector<KeyPosition>&		positions() const;
		const std::vector<KeyRotation>&		rotations() const;
		const std::vector<KeyScale>&		scales() const;
		const std::vector<unsigned short>&	children() const;

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
