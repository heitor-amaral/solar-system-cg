#include "texturas.h"
#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;


void carregaTextura()
{
// Carrega a textura do Sol
    sun = SOIL_load_OGL_texture
	(
		"../texturas/sun.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(sun == 0)
    {
        cout << "SOL - Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    //MERCURIO
    mercury = SOIL_load_OGL_texture
	(
		"../texturas/mercury.jpg",
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
		"../texturas/venus.jpg",
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
		"../texturas/earth.jpg",
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
		"../texturas/mars.jpg",
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
		"../texturas/jupiter.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(jupiter == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    //jupiter_rings
    jupiter_rings = SOIL_load_OGL_texture
	(
		"../texturas/jupiter_rings.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(jupiter_rings == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }


    // saturn
    saturn = SOIL_load_OGL_texture
	(
		"../texturas/saturn.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(saturn == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    // saturn_ring
    saturn_rings = SOIL_load_OGL_texture
	(
		"../texturas/saturn_rings.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(saturn_rings == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }



     // uranus
    uranus = SOIL_load_OGL_texture
	(
		"../texturas/uranus.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(uranus == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

     // uranus rings
    uranus__rings = SOIL_load_OGL_texture
	(
		"../texturas/uranus__rings.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(uranus__rings == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

     // neptune
    neptune = SOIL_load_OGL_texture
	(
		"../texturas/neptune.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(neptune == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    //neptune_rings
    neptune_rings = SOIL_load_OGL_texture
	(
		"../texturas/neptune_rings.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(neptune_rings == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }


    // Carrega a textura Skysphere
    sky = SOIL_load_OGL_texture
	(
		"../texturas/sky.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(sky == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    // Carrega a textura Lua
    moon = SOIL_load_OGL_texture
	(
		"../texturas/moon.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(moon == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }


}