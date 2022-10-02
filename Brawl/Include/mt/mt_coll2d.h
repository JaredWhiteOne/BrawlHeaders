#pragma once

#include <mt/mt_vector.h>

class clAABBox2D
{
    float unk1;
    float unk2;
    float unk3;
    float unk4;
};

class clCircle2D
{
    Vec2f centerPos;
    float radius;
};

class clRhombus2D
{
    Vec2f centerPos;
    Vec2f upPos;
    Vec2f downPos;
    Vec2f leftPos;
    Vec2f rightPos;
    clAABBox2D aabBox;
};
