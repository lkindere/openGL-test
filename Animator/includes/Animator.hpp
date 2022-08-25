#pragma once

#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtx/quaternion.hpp>

#include "Structs.hpp"

struct modelIN
{
    std::map<std::string, glm::mat4> postTransforms;
    int anim = -1;
    float time = 0;
    bool loop = false;
};

struct aData
{
    std::vector<glm::mat4>  output;
    const modelIN*          input;
    float                   tick;
};

class Animator
{
	public:
		Animator(MeshData& data);
    private:
        void calculateBase(const NodeData& node, const glm::mat4& last);

    public:
	    std::vector<glm::mat4> generateMatrices(const modelIN& input);
        const NodeData* findNode(const char* name) const;


        const std::vector<glm::mat4>&   matrices() const;
        float                           duration(int ID) const;

    private:
        const NodeData* traverseNodes(const char*name, const NodeData& node) const;

        float getTick(int anim, float time, bool loop);
        void calculateNodes(const NodeData& node, const glm::mat4& last, aData& data);
        glm::mat4 currentMatrix(const BoneData* bone, int anim, float tick) const;
        glm::mat4 currentPos(const std::vector<KeyPosition>& positions, float time) const;
        glm::mat4 currentRot(const std::vector<KeyRotation>& rotations, float time) const;
        glm::mat4 currentScale(const std::vector<KeyScale>& scales, float time) const;
        float getInterpolant(float time, float t1, float t2) const;

    private:
        NodeData                _nodes;
        std::vector<AnimTimers> _timers;

        //Base transformations
        std::vector<glm::mat4>  _matrices;
};