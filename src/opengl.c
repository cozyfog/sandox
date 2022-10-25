#include "opengl.h"

int clock_1, clock_2 = 0;

void EDIT_displayFunc()
{
  if (clock_1 - clock_2 >= 40)
  {
    glClear(GL_COLOR_BUFFER_BIT);
    displayFunc();
    clock_2 = clock_1;
    glutSwapBuffers();
  }
  clock_1 = glutGet(GLUT_ELAPSED_TIME);
  glutPostRedisplay();
}

void setColor(float r, float g, float b)
{
  glColor4f(r, g, b, 1.0f);
}

void putPixel(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(x * PIXEL_UNIT + PIXEL_OFFSET, y * PIXEL_UNIT + PIXEL_OFFSET);
  glEnd();
}

void putRectT(int x1, int y1, int x2, int y2)
{
  glBegin(GL_QUADS);
  glVertex2i(x1 * PIXEL_UNIT, y1 * PIXEL_UNIT);
  glVertex2i(x2 * PIXEL_UNIT, y1 * PIXEL_UNIT);
  glVertex2i(x2 * PIXEL_UNIT, y2 * PIXEL_UNIT);
  glVertex2i(x1 * PIXEL_UNIT, y2 * PIXEL_UNIT);
  glEnd();
}

void putFontT(const char *text, int x, int y)
{
  glRasterPos2i(x, y + 176);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char *)(text));
}

void initGlut(const char *title)
{
  int f_argc; char **f_argv = 0;

  glutInit(&f_argc, f_argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1280, 720);
  glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1280) * 0.5f, (glutGet(GLUT_SCREEN_HEIGHT) - 720) * 0.5f);

  glutCreateWindow(title);

  glClearColor(0.6f, 0.7f, 0.8f, 1.0f);
  glOrtho(0, 320, 0, 180, -1, 1);
  glPointSize(PIXEL_UNIT * 4);

  initFunc();

  glutIgnoreKeyRepeat(1);

  glutDisplayFunc(EDIT_displayFunc);
  glutMouseFunc(cursorFunc);
  glutKeyboardFunc(keyboardFunc);

  glutMainLoop();
}
