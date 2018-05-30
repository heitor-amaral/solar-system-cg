#include "texturas.h"

#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <math.h>

using namespace std;

//VARIAVEIS DE TEXTURA
static int sun;
static int mercury;
static int venus;
static int earth;
static int mars;
static int jupiter;
static int saturn;
static int uranus;
static int neptune;
static int sky;
//VARIAVEIS DE TEXTURA

void carregaTextura();
