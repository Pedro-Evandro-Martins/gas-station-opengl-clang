#ifndef CUBE_H
#define CUBE_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <stdlib.h>

#include "objects/object3d.h"

typedef struct cube {
  Object3d *base;
} Cube;
struct cube *newCube();

#endif
