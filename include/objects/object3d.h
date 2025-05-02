#ifndef OBJECT3D_H

typedef struct {
  float position[3];
  float size[3];
  float color[4];
  void (*draw)(void *self);
} Object3d;

#endif
