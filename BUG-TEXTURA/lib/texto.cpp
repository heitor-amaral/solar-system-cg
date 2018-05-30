#include "texto.h"
#include <GL/freeglut.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void escreveTexto(void* font, char* s, float x, float y, float z) 
{
  unsigned int i;

  glRasterPos3f(x, y, z);

  for (i = 0; i < strlen (s); i++) 
  {// menor que
     glutBitmapCharacter(font, s[i]);
  }
}

void escreveNumero(void* font, float numero, float x, float y, float z) 
{
  unsigned int i;

  glRasterPos3f(x, y, z);

  char buffer[50];

  sprintf( buffer, "%.2f", numero );

  for (i = 0; i < strlen (buffer); i++) 
  {// menor que
     glutBitmapCharacter(font, buffer[i]);
  }
}