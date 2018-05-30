#ifndef TEXTURAS_H
#define TEXTURAS_H

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


void carregaTextura()
{
// Carrega a textura do Sol
    sun = SOIL_load_OGL_texture
	(
		"sun.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(sun == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    //MERCURIO
    mercury = SOIL_load_OGL_texture
	(
		"mercury.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(mercury == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

     //VENUS
    venus = SOIL_load_OGL_texture
	(
		"venus.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(venus == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    // Carrega a textura da terra
    earth = SOIL_load_OGL_texture
	(
		"earth.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(earth == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    // MARTE
    mars = SOIL_load_OGL_texture
	(
		"mars.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(mars == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    // jupiter
    jupiter = SOIL_load_OGL_texture
	(
		"jupiter.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(jupiter == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    // saturn
    saturn = SOIL_load_OGL_texture
	(
		"saturn.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(saturn == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

     // uranus
    uranus = SOIL_load_OGL_texture
	(
		"uranus.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(uranus == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

     // neptune
    neptune = SOIL_load_OGL_texture
	(
		"neptune.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(neptune == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }


    // Carrega a textura Skysphere
    sky = SOIL_load_OGL_texture
	(
		"sky.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(sky == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }


}

#endif // TEXTURAS_H
