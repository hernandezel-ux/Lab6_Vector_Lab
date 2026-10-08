/***************
* filename: miniMat.c
* author: emanuel Hernandez
* date: 10/1/2026
* desc: vector calculator
* comp: gcc miniMat.c myVectArray.c myVectTop.c -o miniMat
****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miniMat.h"

static struct Vector *findVector(const char *name)
{
    for (int i = 0; i < 10; i++) {
        if (strcmp(vectArray[i].name, name) == 0) {
            return &vectArray[i];
        }
    }
    return 0;
}

static struct Vector *storeVector(const char *name)
{
    struct Vector *vector = findVector(name);
    if (vector != 0) {
        return vector;
    }
    for (int i = 0; i < 10; i++) {
        if (vectArray[i].name[0] == '\0') {
            snprintf(vectArray[i].name, sizeof vectArray[i].name, "%s", name);
            return &vectArray[i];
        }
    }
    return 0;
}

static void printVector(const char *name, struct Vector vector)
{
    printf("%s = %g %g %g\n", name, vector.x, vector.y, vector.z);
}

static int parseNumber(const char *text, float *number)
{
    char *end;
    *number = strtof(text, &end);
    while (*end == ' ' || *end == '\t') {
        end++;
    }
    return end != text && *end == '\0';
}

static int parseLiteral(const char *text, struct Vector *vector)
{
    float *components[] = {&vector->x, &vector->y, &vector->z};
    const char *position = text;

    for (int i = 0; i < 3; i++) {
        while (*position == ' ' || *position == '\t') {
            position++;
        }
        if (i > 0 && *position == ',') {
            position++;
        }
        while (*position == ' ' || *position == '\t') {
            position++;
        }
        char *end;
        *components[i] = strtof(position, &end);
        if (end == position) {
            return 0;
        }
        position = end;
    }

    while (*position == ' ' || *position == '\t') {
        position++;
    }
    return *position == '\0';
}

static int evaluate(char *expression, struct Vector *result, int *isVariable)
{
    char *start = expression;
    while (*start == ' ' || *start == '\t') {
        start++;
    }

    if (parseLiteral(start, result)) {
        *isVariable = 0;
        return 1;
    }

    char *operatorPosition = 0;
    for (char *p = start; *p != '\0'; p++) {
        if (*p == '+' || *p == '-' || *p == '*') {
            operatorPosition = p;
            break;
        }
    }

    if (operatorPosition == 0) {
        char name[sizeof vectArray[0].name];
        char trailing;
        if (sscanf(start, " %9s %c", name, &trailing) != 1) {
            return 0;
        }
        struct Vector *vector = findVector(name);
        if (vector == 0) {
            return 0;
        }
        *result = *vector;
        *isVariable = 1;
        return 1;
    }

    char operator = *operatorPosition;
    *operatorPosition = '\0';
    char *left = start;
    char *right = operatorPosition + 1;
    while (*right == ' ' || *right == '\t') {
        right++;
    }
    char leftName[sizeof vectArray[0].name];
    char rightName[sizeof vectArray[0].name];
    char trailing;
    struct Vector *leftVector = 0;
    struct Vector *rightVector = 0;
    float scalar;

    if (sscanf(left, " %9s %c", leftName, &trailing) == 1) {
        leftVector = findVector(leftName);
    }
    if (sscanf(right, " %9s %c", rightName, &trailing) == 1) {
        rightVector = findVector(rightName);
    }

    if (operator == '*' && leftVector != 0 && parseNumber(right, &scalar)) {
        *result = scalarMultiply(*leftVector, scalar);
    } else if (operator == '*' && rightVector != 0 && parseNumber(left, &scalar)) {
        *result = scalarMultiply(*rightVector, scalar);
    } else if (leftVector != 0 && rightVector != 0 && operator == '+') {
        *result = add(*leftVector, *rightVector);
    } else if (leftVector != 0 && rightVector != 0 && operator == '-') {
        *result = subtract(*leftVector, *rightVector);
    } else {
        return 0;
    }

    *isVariable = 0;
    return 1;
}

int main(void)
{
    char line[256];

    while (1) {
        printf("minimat> ");
        fflush(stdout);
        if (fgets(line, sizeof line, stdin) == 0) {
            break;
        }
        line[strcspn(line, "\r\n")] = '\0';

        char *input = line;
        while (*input == ' ' || *input == '\t') {
            input++;
        }
        if (*input == '\0') {
            continue;
        }
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
            break;
        }
        if (strcmp(input, "list") == 0) {
            printVectors();
            continue;
        }
        if (strcmp(input, "clear") == 0) {
            clearVectors();
            continue;
        }
        if (strcmp(input, "help") == 0) {
            printf("Enter vectors as name = x y z; use +, -, or * scalar.\n");
            printf("Commands: list, clear, help, quit\n");
            continue;
        }

        char *equals = strchr(input, '=');
        char name[sizeof vectArray[0].name];
        char *expression = input;
        int assignment = equals != 0;
        if (assignment) {
            *equals = '\0';
            char trailing;
            if (sscanf(input, " %9s %c", name, &trailing) != 1) {
                printf("Invalid vector name.\n");
                continue;
            }
            expression = equals + 1;
        }

        struct Vector result;
        int isVariable = 0;
        if (!evaluate(expression, &result, &isVariable)) {
            printf("Invalid expression.\n");
            continue;
        }

        if (assignment) {
            struct Vector *stored = storeVector(name);
            if (stored == 0) {
                printf("Vector storage is full.\n");
                continue;
            }
            result.name[0] = '\0';
            *stored = result;
            snprintf(stored->name, sizeof stored->name, "%s", name);
            printVector(name, *stored);
        } else {
            printVector(isVariable ? result.name : "ans", result);
        }
    }
    return 0;

}