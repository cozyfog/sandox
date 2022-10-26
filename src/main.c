#include <main.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define CANVAS_WIDTH    79
#define CANVAS_HEIGHT   44
#define CANVAS_SIZE     (CANVAS_WIDTH * CANVAS_HEIGHT)
#define DIFFUSE_VALUE   0.5

#define BRUSH_SAND      0x0001
#define BRUSH_WATER     0x0002
#define BRUSH_DIRT      0x0003
#define BRUSH_FIRE      0x0004

int canvas_buffer[CANVAS_SIZE];
int brush_type = BRUSH_SAND;

void initFunc()
{
  return;
}

void displayFunc()
{
  srand(sqrt(time(NULL)));
  
  // Clearing the canvas_buffer
  memset(&canvas_buffer, 0, CANVAS_SIZE);

  // Drawing the ground segment
  setColor(0.2f, 0.2f, 0.2f);
  putRectT(0, 0, CANVAS_WIDTH, 11);

  // Drawing + Simulating the pixels
  for (int y = 0; y < CANVAS_HEIGHT; ++y)
  {
    for (int x = 0; x < CANVAS_WIDTH; ++x)
    {
      switch (canvas_buffer[x + y * CANVAS_WIDTH])
      {  
        case 0:
          break;
        case BRUSH_SAND:
          setColor(1.0f, 1.0f, 0.0f);
          putPixel(x, y);
          if (y != 11)
          {
            if (canvas_buffer[x + (y - 1) * CANVAS_WIDTH] == 0)
            {
              canvas_buffer[x + (y - 1) * CANVAS_WIDTH] = 1;
              canvas_buffer[x + y * CANVAS_WIDTH] = 0;
            }
            else if (canvas_buffer[x + 1 + (y - 1) * CANVAS_WIDTH] == 0)
            {
              canvas_buffer[x + 1 + y * CANVAS_WIDTH] = 1;
              canvas_buffer[x + y * CANVAS_WIDTH] = 0;
            }
            else if (canvas_buffer[x - 1 + (y - 1) * CANVAS_WIDTH] == 0)
            {
              canvas_buffer[x - 1 + y * CANVAS_WIDTH] = 1;
              canvas_buffer[x + y * CANVAS_WIDTH] = 0;
            }
            if (canvas_buffer[x + (y - 1) * CANVAS_WIDTH] == BRUSH_WATER)
            {
              canvas_buffer[x + (y - 1) * CANVAS_WIDTH] = BRUSH_SAND;
              canvas_buffer[x + y * CANVAS_WIDTH] = BRUSH_WATER;
            }
          }
          break;
        case BRUSH_WATER:
          setColor(0.0f, 0.0f, 1.0f);
          putPixel(x, y);
          if (y != 11)
          {
            if (canvas_buffer[x + (y - 1) * CANVAS_WIDTH] == 0)
            {
              canvas_buffer[x + (y - 1) * CANVAS_WIDTH] = 2;
              canvas_buffer[x + y * CANVAS_WIDTH] = 0;
            }
            else if (canvas_buffer[x + 1 + y * CANVAS_WIDTH] == 0 && rand() * 0.00000001f < 14.5f)
            {
              canvas_buffer[x + 1 + y * CANVAS_WIDTH] = 2;
              canvas_buffer[x + y * CANVAS_WIDTH] = 0;
            }
            else if (canvas_buffer[x - 1 + y * CANVAS_WIDTH] == 0)
            {
              canvas_buffer[x - 1 + y * CANVAS_WIDTH] = 2;
              canvas_buffer[x + y * CANVAS_WIDTH] = 0;
            }
          }
          break;
        case BRUSH_DIRT:
          setColor(0.4f, 0.2f, 0.1f);
          putPixel(x, y);
          break;
        case BRUSH_FIRE:
          setColor(1.0f, 0.25f, 0.0f);
          putPixel(x, y);
          canvas_buffer[x + y * CANVAS_WIDTH] = 0;
          if (canvas_buffer[x + 1 + y * CANVAS_WIDTH] != 0 && canvas_buffer[x + 1 + y * CANVAS_WIDTH] != BRUSH_WATER)
          {
            canvas_buffer[x + 1 + y * CANVAS_WIDTH] = BRUSH_FIRE;
          }
          if (canvas_buffer[x - 1 + y * CANVAS_WIDTH] != 0 && canvas_buffer[x - 1 + y * CANVAS_WIDTH] != BRUSH_WATER)
          {
            canvas_buffer[x - 1 + y * CANVAS_WIDTH] = BRUSH_FIRE;
          }
          if (canvas_buffer[x + (y + 1) * CANVAS_WIDTH] != 0i && canvas_buffer[x + (y + 1) * CANVAS_WIDTH] != BRUSH_WATER)
          {
            canvas_buffer[x + (y + 1) * CANVAS_WIDTH] = BRUSH_FIRE;
          }
          if (canvas_buffer[x + (y - 1) * CANVAS_WIDTH] != 0i && canvas_buffer[x + (y - 1) * CANVAS_WIDTH] != BRUSH_WATER)
          {
            canvas_buffer[x + (y - 1) * CANVAS_WIDTH] = BRUSH_FIRE;
          }
          break;
      }
    }
  }
}

void cursorFunc(int button, int state, int x, int y)
{
  x = (int)(x * 0.0625f);
  y = ((int)(y * 0.0625f) - CANVAS_HEIGHT) * -1;

  switch (button)
  {
    case 0:
      canvas_buffer[x + y * CANVAS_WIDTH] = brush_type;
      break;
    case 2:
      canvas_buffer[x + y * CANVAS_WIDTH] = 0;
      break;
  }
}

void keyboardFunc(unsigned char key, int x, int y)
{
  if (key == '1') brush_type = BRUSH_SAND   ;
  if (key == '2') brush_type = BRUSH_WATER  ;
  if (key == '3') brush_type = BRUSH_DIRT   ;
  if (key == '4') brush_type = BRUSH_FIRE   ;
}
