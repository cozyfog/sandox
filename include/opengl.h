#ifndef OPENGL_H_
#define OPENGL_H_

#ifndef __APPLE__
  #include <GL/glut.h>
  #include <GL/freeglut.h>
#else
  #include <GLUT/glut.h>
  #include <GLUT/freeglut.h>
#endif // __APPLE__
#include <GL/gl.h>

#include "main.h"

#define PIXEL_UNIT    4
#define PIXEL_OFFSET  (PIXEL_UNIT * 0.5f)

void setColor(float r, float g, float b);
void putPixel(int x, int y);
void putRectT(int x1, int y1, int x2, int y2);
void putFontT(const char *text, int x, int y);
void initGlut(const char *title);

#endif // OPENGL_H_
