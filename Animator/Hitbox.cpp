#include <algorithm>

#include "Hitbox.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Object.hpp"

extern Shader* g_hitboxShader;

Hitbox::Hitbox() {}

void Hitbox::recalculate(const std::vector<glm::vec3>& base, const glm::mat3& rotation){
    if (base.size() == 0)
        return;
    _vertices.clear();
    _flats.clear();
    _normals.clear();
    _min = glm::vec3(1E-37);
    _max = glm::vec3(1E+37);
    for (auto i = 0; i < base.size(); ++i){
        _vertices.push_back(base[i] * rotation);
        glm::vec2 flatvec = glm::vec2(_vertices[i].x, _vertices[i].z);
        if (std::find(_flats.begin(), _flats.end(), flatvec) == _flats.end()){
            _flats.push_back(flatvec);
            if (_vertices[i].x < _min.x)
                _min.x = _vertices[i].x;
            else if (_vertices[i].x > _max.x)
                _max.x = _vertices[i].x;
            if (_vertices[i].y < _min.y)
                _min.y = _vertices[i].y;
            else if (_vertices[i].y > _max.y)
                _max.y = _vertices[i].y;
            if (_vertices[i].z < _min.z)
                _min.z = _vertices[i].z;
            else if (_vertices[i].z > _max.z)
                _max.z = _vertices[i].z;
        }
    }
}

glm::vec2 Hitbox::getMinMax(const glm::vec2& normal, const Object& obj) const{
    std::vector<glm::vec2> flats(obj.hitbox()._flats);
    glm::vec3 finalpos(obj.finalpos());
    for (auto i = 0; i < flats.size(); ++i)
        flats[i] += glm::vec2(finalpos.x, finalpos.z);
    float dot = glm::dot(flats[0], normal);
    glm::vec2 range(dot, dot);
    for (auto i = 1; i < flats.size(); ++i){
        dot = glm::dot(flats[i], normal);
        if (dot < range[0])
            range[0] = dot;
        else if (dot > range[1])
            range[1] = dot;
    }
    return range;
}

float Hitbox::getOverlap(const glm::vec2& minMax, const glm::vec2& tminMax) const{
    if (minMax[0] > tminMax[1] || minMax[1] < tminMax[0])
        return 0;
    float distance1 = minMax[1] - tminMax[0];
    float distance2 = tminMax[1] - minMax[0];
    return glm::min(distance1, distance2);
}

void Hitbox::getNormals(){
    for (auto i = 0; i < 2; ++i){
        glm::vec2 normal = _flats[i] - _flats[i + 1]; //Will need to modulo back to 0 if iterating all
        _normals.push_back(glm::normalize(glm::vec2(-normal[1], normal[0])));
    }
}

CollisionData Hitbox::sat2D(Object& obj, Object& target){
    CollisionData data;
    data.overlap = 1E+37;
    if (_normals.size() == 0)
        getNormals();
    if (target.hitbox()._normals.size() == 0)
        target.hitbox().getNormals();
    for (auto i = 0; i < _normals.size(); ++i){
        glm::vec2 minMax = getMinMax(_normals[i], obj);
        glm::vec2 tminMax = getMinMax(_normals[i], target);
        float overlap = getOverlap(minMax, tminMax);
        if (overlap == 0)
            return CollisionData();
        if (overlap < data.overlap){
            data.overlap = overlap;
            data.normal = glm::vec3(_normals[i][0], 0.0f, _normals[i][1]);
        }
    }
    std::vector<glm::vec2> tnormals(target.hitbox()._normals);
    for (auto i = 0; i < tnormals.size(); ++i){
        glm::vec2 minMax = getMinMax(tnormals[i], obj);
        glm::vec2 tminMax = getMinMax(tnormals[i], target);
        float overlap = getOverlap(minMax, tminMax);
        if (overlap == 0)
            return CollisionData();
        if (overlap < data.overlap){
            data.overlap = overlap;
            data.normal = glm::vec3(tnormals[i][0], 0.0f, tnormals[i][1]);
        }
    }
    return data;
}

CollisionData Hitbox::checkY(float finalY, float tfinalY, const Object& obj, const Object& target) const{
    CollisionData data;
    const Hitbox& targ = target.hitbox();
    glm::vec2 minMaxY(finalY + _min.y, finalY + _max.y);
    glm::vec2 tminMaxY(tfinalY + targ._min.y, tfinalY + targ._max.y);
    data.overlap = getOverlap(minMaxY, tminMaxY);
    if (data.overlap == 0)
        return CollisionData();
    data.normal = glm::vec3(0.0f, 1.0f, 0.0f);  //Probably bs, test with vertical collisions later
    return data;
}

CollisionData Hitbox::checkDirection(const glm::vec3& finalpos, const glm::vec3& tfinalpos, CollisionData& data) const{
    glm::vec2 direction(finalpos.x - tfinalpos.x, finalpos.z - tfinalpos.z);
    if (glm::dot(direction, glm::vec2(data.normal.x, data.normal.z)) > 0.0f)
        data.normal = -data.normal;
    return data;
}

CollisionData Hitbox::checkCollision(Object& obj, Object& target){
    if (_vertices.size() == 0 || target.hitbox()._vertices.size() == 0)
        return CollisionData();
    glm::vec3 finalpos = obj.finalpos();
    glm::vec3 tfinalpos = target.finalpos();
    CollisionData Yaxis = checkY(finalpos.y, tfinalpos.y, obj, target);
    if (Yaxis.overlap == 0)
        return CollisionData();
    CollisionData XZaxis = sat2D(obj, target);
    if (XZaxis.overlap == 0)
        return CollisionData();
    if (Yaxis.overlap < XZaxis.overlap)
        return checkDirection(finalpos, tfinalpos, Yaxis);
    return checkDirection(finalpos, tfinalpos, XZaxis);
}

void Hitbox::draw(const Uniforms& uni){
    if (_vertices.size() == 0)
        return;
    std::vector<GLuint> indices = {
        0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7,
        1, 0, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7,
        2, 0, 2, 1, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7,
        3, 0, 3, 1, 3, 2, 3, 4, 3, 5, 3, 6, 3, 7,

        4, 5, 4, 6, 4, 7, 4, 0, 4, 1, 4, 2, 4, 3,
        5, 4, 5, 6, 5, 7, 5, 0, 5, 1, 5, 2, 5, 3,
        6, 4, 6, 5, 6, 7, 6, 0, 6, 1, 6, 2, 6, 3,
        7, 4, 7, 5, 7, 6, 7, 0, 7, 1, 7, 2, 7, 3,
    };
    g_hitboxShader->bind();
    g_hitboxShader->update(uni);

    GLuint temp;
    glGenVertexArrays(1, &temp);
	glBindVertexArray(temp);

    GLuint VerticeBuffer;
	glGenBuffers(1, &VerticeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VerticeBuffer);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), _vertices.data(), GL_STREAM_DRAW);

	GLuint IndiceBuffer;
	glGenBuffers(1, &IndiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndiceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, (void*)0);

    glDeleteBuffers(1, &VerticeBuffer);
    glDeleteBuffers(1, &IndiceBuffer);
    glDeleteVertexArrays(1, &temp);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    g_hitboxShader->unbind();
}
