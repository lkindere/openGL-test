#pragma once

#include "main.hpp"

enum object_type
{
    STATIC,
    LIGHT,
    PLAYER,
    MOB,
    DETAIL,
};

enum shader_flags
{
    hasTexture = 1,
    deformOn = 2,
};

struct object_info
{
    int             _ID = -1;
    std::string     _name; //for debugging only
    object_type     _type = STATIC;
    bool            _collide = false;

    object_info(int ID) : _ID(ID) {}

    public:
        int                 ID() const { return _ID; }
        const std::string&  name() const { return _name; }
        object_type         type() const { return _type; }
        bool                collide() const { return _collide; }

    public:
        void setName(const std::string& name) { _name = name; }
        void setType(object_type type) { _type = type; }
        void setCollide(bool b) { _collide = b; }
};

