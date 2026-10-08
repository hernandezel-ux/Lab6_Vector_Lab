/***************
* filename: miniMat.h
* author: emanuel Hernandez
* date: 10/1/2026
* desc: vector calculator declarations
****************/

struct Vector
{
    char name[10];
    float x;
    float y;
    float z;

};

extern struct Vector vectArray[10];

struct Vector add(struct Vector a, struct Vector b);
struct Vector subtract(struct Vector a, struct Vector b);
struct Vector dot(struct Vector a, struct Vector b);
struct Vector cross(struct Vector a, struct Vector b);
struct Vector scalarMultiply(struct Vector a, float scalar);
void printVectors(void);
void clearVectors(void);