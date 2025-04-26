#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#define M_PI 3.141592

static int y_rot = 0;
static int x_rot = 0;
static int z_rot = 0;
static float zoom = -25.0;

GLfloat white[] = {0.9, 0.9, 0.9, 1.0};
GLfloat pump_white[] = {0.8, 0.8, 0.9, 1.0};
GLfloat concrete_gray[] = {0.55, 0.55, 0.55, 1.0};
GLfloat ceiling_yellow[] = {0.8, 0.75, 0.15, 1.0};
GLfloat red[] = {0.8, 0.0, 0.0, 1.0};
GLfloat green[] = {0.0, 0.8, 0.0, 1.0};
GLfloat blue[] = {0.0, 0.0, 0.8, 1.0};

void init() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void drawCube(float width, float height, float depth, float *color,
              float pos[3]) {
  glPushMatrix();
  glTranslatef(pos[0], pos[1], pos[2]);
  glScalef(width, height, depth);
  glColor3fv(color);
  glutSolidCube(1.0);
  glPopMatrix();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef((GLfloat)x_rot, 1.0, 0.0, 0.0);
  glRotatef((GLfloat)y_rot, 0.0, 1.0, 0.0);
  glRotatef((GLfloat)z_rot, 0.0, 0.0, 1.0);

  float _defaultPos[3] = {0.0, 0.0, 0.0};

  // ground
  float _groundPos[3] = {0.0, -0.25, 0.0};
  drawCube(22.0, 0.5, 7.0, concrete_gray, _groundPos);

  // ceiling
  float _ceilingPos[3] = {0.0, 7.5, 0.0};
  drawCube(20.0, 1.0, 6.5, ceiling_yellow, _ceilingPos);

  // center edges
  float _edgePos[3] = {0, 3.5, 2.5};
  drawCube(0.4, 7.0, 0.4, pump_white, _edgePos);
  _edgePos[2] = -2.5;
  drawCube(0.4, 7.0, 0.4, pump_white, _edgePos);

  // left edges
  _edgePos[0] = 7.0;
  drawCube(0.4, 7.0, 0.4, pump_white, _edgePos);
  _edgePos[2] = 2.5;
  drawCube(0.4, 7.0, 0.4, pump_white, _edgePos);

  // right edges
  _edgePos[0] = -7.0;
  drawCube(0.4, 7.0, 0.4, pump_white, _edgePos);
  _edgePos[2] = -2.5;
  drawCube(0.4, 7.0, 0.4, pump_white, _edgePos);

  // gas pumps
  float _gasPumpPos[3] = {0.0, 1.2, 1.0};
  drawCube(0.6, 2.4, 1.3, pump_white, _gasPumpPos);
  _gasPumpPos[0] = 7.0;
  drawCube(0.6, 2.4, 1.3, pump_white, _gasPumpPos);
  _gasPumpPos[0] = -7.0;
  drawCube(0.6, 2.4, 1.3, pump_white, _gasPumpPos);

  // gas pump boards
  float _gasPumpBoards[3] = {0.0, 2.8, 1.0};
  drawCube(0.8, 0.8, 2.2, white, _gasPumpBoards);
  _gasPumpBoards[0] = 7.0;
  drawCube(0.8, 0.8, 2.2, white, _gasPumpBoards);
  _gasPumpBoards[0] = -7.0;
  drawCube(0.8, 0.8, 2.2, white, _gasPumpBoards);

  glPopMatrix(); // scene rotation
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, -4.0, -25.0);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 'r':
    y_rot = (y_rot + 5) % 360;
    glutPostRedisplay();
    break;
  case 'R':
    y_rot = (y_rot - 5) % 360;
    glutPostRedisplay();
    break;
  case 'c':
    x_rot = (x_rot + 5) % 360;
    glutPostRedisplay();
    break;
  case 'C':
    x_rot = (x_rot - 5) % 360;
    glutPostRedisplay();
    break;
  case 'w':
    z_rot = (z_rot + 5) % 360;
    glutPostRedisplay();
    break;
  case 'W':
    z_rot = (z_rot - 5) % 360;
    glutPostRedisplay();
    break;
  case '+':
    zoom += 0.5;
    if (zoom > -1.0)
      zoom = -1.0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, -4.0, zoom);
    glutPostRedisplay();
    break;
  case '-':
    zoom -= 0.5;
    if (zoom < -50.0)
      zoom = -50.0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, -4.0, zoom);
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
