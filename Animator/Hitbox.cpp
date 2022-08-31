#include <algorithm>

#include "Hitbox.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Object.hpp"

extern Shader* g_hitboxShader;

Hitbox::Hitbox(const HitboxData& data)
    : _vertices(data.vertices) {
    if (data.vertices.size() == 0)
        return ;
    recalculate(data.vertices);
}

void Hitbox::recalculate(const std::vector<glm::vec3>& vertices){
    if (vertices.size() == 0)
        return ;
    _flats.clear();
    _normals.clear();
    _minY = vertices[0].y;
    _maxY = vertices[0].y;
    for (auto i = 0; i < vertices.size(); ++i){
        glm::vec2 flatvec = glm::vec2(vertices[i].x, vertices[i].z);
        if (std::find(_flats.begin(), _flats.end(), flatvec) == _flats.end())
            _flats.push_back(flatvec);
        if (vertices[i].y < _minY)
            _minY = vertices[i].y;
        else if (vertices[i].y > _maxY)
            _maxY = vertices[i].y;
    }
    for (auto i = 0; i < 2; ++i){
        glm::vec2 norm = get2Dnormal(_flats[i], _flats[(i + 1) % _flats.size()]);
        _normals.push_back(norm);
    }
}

glm::vec2 Hitbox::get2Dnormal(const glm::vec2& p1, const glm::vec2& p2) const{
    glm::vec2 normal = p1 - p2;
    normal = glm::normalize(glm::vec2(-normal[1], normal[0]));
    return normal;
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

CollisionData Hitbox::sat2D(const Object& obj, const Object& target) const{
    std::string name;
    int         id = 0;
    CollisionData data;
    data.overlap = 1E+37;
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
    const std::vector<glm::vec2>& tnormals = target.hitbox()._normals;
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
    glm::vec2 minMaxY(finalY + _minY, finalY + _maxY);
    glm::vec2 tminMaxY(tfinalY + targ._minY, tfinalY + targ._maxY);
    data.overlap = getOverlap(minMaxY, tminMaxY);
    if (data.overlap == 0)
        return CollisionData();
    data.normal = glm::vec3(0.0f, 1.0f, 0.0f);
    return data;
}

CollisionData Hitbox::checkDirection(const glm::vec3& finalpos, const glm::vec3& tfinalpos, CollisionData& data) const{
    glm::vec2 direction(finalpos.x - tfinalpos.x, finalpos.z - tfinalpos.z);
    if (glm::dot(direction, glm::vec2(data.normal.x, data.normal.z)) > 0.0f)
        data.normal = -data.normal;
    return data;
}

CollisionData Hitbox::checkCollision(const Object& obj, const Object& target) const{
    if (_flats.size() == 0 || target.hitbox()._flats.size() == 0)
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

void Hitbox::setRotation(const glm::mat3& mat){
    _rotation = mat;
    if (_lastRot != _rotation){
        std::vector<glm::vec3> vertices = _vertices;
        _lastRot = _rotation;
        for (auto i = 0; i < vertices.size(); ++i)
            vertices[i] = vertices[i] * _rotation;
        recalculate(vertices);
    }
}

void Hitbox::draw(const Uniforms& uni){
    if (_vertices.size() == 0)
        return;
    std::vector<glm::vec3> vertices(_vertices);
    for (auto i = 0; i < vertices.size(); ++i)
        vertices[i] = vertices[i] * _rotation;
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STREAM_DRAW);

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
