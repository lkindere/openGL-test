#pragma once

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
