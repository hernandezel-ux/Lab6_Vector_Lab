/***************
* filename: myVectTop.c
* author: emanuel Hernandez
* date: 10/1/2026
* desc: vector calculator
* comp: gcc miniMat.c myVectArray.c myVectTop.c -o miniMat
****************/
    #include <stdio.h>
    #include "miniMat.h"

struct Vector add(struct Vector a, struct Vector b)
{
    struct Vector c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return c;
}

struct Vector subtract(struct Vector a, struct Vector b)
{
    struct Vector c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return c;
}

struct Vector dotMultiply(struct Vector a, struct Vector b)
{
    struct Vector c;
    c.x = a.x * b.x;
    c.y = a.y * b.y;
    c.z = a.z * b.z;
    return c;
}

struct Vector crossMultiply(struct Vector a, struct Vector b)
{
    struct Vector c;
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;
    return c;
}

struct Vector scalarMultiply(struct Vector a, float scalar)
{
    struct Vector c;
    c.x = a.x * scalar;
    c.y = a.y * scalar;
    c.z = a.z * scalar;
    return c;
}