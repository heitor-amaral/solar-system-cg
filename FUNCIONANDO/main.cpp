#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <math.h>
#include <string.h>

using namespace std;

static float d = 5.0;           // Intensidade da cor difusa da luz branca
static float e = 5.0;           // Intensidade da cor especular da luz branca
static float m = 0.2;           // Intensidade da luz ambiente global
static float p = 1.0;           // A luz branca é posicional?
static float s = 50.0;          // Expoente especular do material (shininess)
float matShine[] = { s };                       // expoente especular (shininess)
static float xMouse = 250, yMouse = 250;        // (x,y) do ponteiro do mouse
static float larguraJanela, alturaJanela;       // (w,h) da janela
static float anguloEsferaY = 0;                 // Rotação da esfera em torno do eixo y
static int esferaLados = 200;                  // Quantas subdivisões latitudinais/longitudinais da esfera
static bool usarTextura = true;
static bool localViewer = false;


bool orbita = false;
bool fullScreen = false;
bool planoOrbital = false;
bool normal = false;

//CAMERA
int camera = 1;
int olharX = 0;
int olharY = 0;
//CAMERA

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
static int moon;
static int saturn_rings;
static int uranus__rings;
static int neptune_rings;
static int jupiter_rings;
//VARIAVEIS DE TEXTURA

float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
float lightDif0[] = { d, d, d, 1.0 };
float lightSpec0[] = { e, e, e, 1.0 };
float lightPos0[] = { 0.5, 0.5, 0.5, 1 };

void escreveTexto(void* font, char* s, float x, float y,float z)
{
  unsigned int i;

  glRasterPos3f(x, y, z);

  for (i = 0; i < strlen (s); i++)
  {// menor que
     glutBitmapCharacter(font, s[i]);
  }
}

void escreveNumero(void* font, int numero, float x, float y, float z)
{
  unsigned int i;

  glRasterPos3f(x, y, z);

  char buffer[50];

  sprintf( buffer, "%d", numero );

  for (i = 0; i < strlen (buffer); i++)
  {// menor que
     glutBitmapCharacter(font, buffer[i]);
  }
}

void desenhaHUD()
{
    glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "CAMERA", -40.0, 38, -40.0); //x,y,z
    escreveNumero(GLUT_BITMAP_HELVETICA_18, camera, -23.0, 38, -40.0);
}


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

    //jupiter_rings
    jupiter_rings = SOIL_load_OGL_texture
	(
		"jupiter_rings.png",
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
		"saturn.jpg",
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
		"saturn_rings.png",
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
		"uranus.jpg",
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
		"uranus__rings.png",
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
		"neptune.jpg",
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
		"neptune_rings.png",
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
		"sky.jpg",
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
		"moon.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(moon == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }


}

// Configuração inicial do OpenGL e GLUT
void setup(void)
{
    //glClearColor(.4,.4,.4, 0.0);                    // fundo cinza
    glClearColor(0,0,0, 0.0);
    glEnable(GL_DEPTH_TEST);                        // Ativa teste Z

    carregaTextura();

    float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

    // Definindo as propriedades do material
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    // Esconder o ponteiro do mouse quando dentro da janela
    glutSetCursor(GLUT_CURSOR_NONE);
}

void solidSphere(int radius, int stacks, int columns)
{
    // cria uma quádrica
    GLUquadric* quadObj = gluNewQuadric();
    // estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
    // ou GLU_POINT
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    // chama 01 glNormal para cada vértice.. poderia ser
    // GLU_FLAT (01 por face) ou GLU_NONE
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    // chama 01 glTexCoord por vértice
    gluQuadricTexture(quadObj, GL_TRUE);
    // cria os vértices de uma esfera
    gluSphere(quadObj, radius, stacks, columns);
    // limpa as variáveis que a GLU usou para criar
    // a esfera
    gluDeleteQuadric(quadObj);
}

void solidPartialDisk(GLdouble interior, GLdouble exterior, int fatias, int rotacoes, int comecar, int varrer)
{
    // cria uma quádrica
    GLUquadric* quadObj = gluNewQuadric();
    // estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
    // ou GLU_POINT
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    // chama 01 glNormal para cada vértice.. poderia ser
    // GLU_FLAT (01 por face) ou GLU_NONE
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    // chama 01 glTexCoord por vértice
    gluQuadricTexture(quadObj, GL_TRUE);
    // cria os vértices de uma esfera
    gluPartialDisk(quadObj, interior, exterior, fatias, rotacoes, comecar, varrer);
    // limpa as variáveis que a GLU usou para criar
    // a esfera
    gluDeleteQuadric(quadObj);
}

void desenhaOrbita(float raio, float x, float y, float z) {
    float angulo;
    int i;

    glBegin(GL_LINE_LOOP);
        //glVertex3f(x, y, z);
        for (i = 0; i <= esferaLados; i++) {
            angulo = 2 * M_PI * i / esferaLados;
            glVertex3f(x + cos(angulo) * raio, y + sin(angulo) * raio, z);
        }
    glEnd();
}

void seOrbita(float distanciaAteOSol)
{
   if(orbita)
        {
            glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            desenhaOrbita(distanciaAteOSol,0,0,0);
            glPopMatrix();
        }
}

void desenhaPlanoOrbital()
{
int subdivisoes = 100;

    int i, j;
    float alturaDoSubTriangulo = 1000.0f / (subdivisoes);
    float larguraDoSubTriangulo = 1000.0f / (subdivisoes);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glPushMatrix();
        glTranslatef(-500, -500, 0);
        for (i = 0; i < subdivisoes; i++) {
            glBegin(GL_TRIANGLE_STRIP);
                // define o vetor normal do ladrilho
                glNormal3f(0,  0, 1);
                float yVerticesLinhaDeBaixo = alturaDoSubTriangulo * (i);
                float yVerticesLinhaDeCima = yVerticesLinhaDeBaixo
                    + alturaDoSubTriangulo;

                for (j = 0; j < subdivisoes + 1; j++) {
                    float xVertice = larguraDoSubTriangulo * j;
                    glTexCoord2f(xVertice, yVerticesLinhaDeCima);
                    glVertex2f(xVertice, yVerticesLinhaDeCima);
                    glTexCoord2f(xVertice, yVerticesLinhaDeBaixo);
                    glVertex2f(xVertice, yVerticesLinhaDeBaixo);
                }
            glEnd();
        }
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}


void desenhaSol()
{
    
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sun);
        glDisable(GL_LIGHTING);
    }
    glPushMatrix();
        
        glTranslatef(0,0,0);
        glRotatef(anguloEsferaY, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        solidSphere(20, esferaLados, esferaLados);

    glPopMatrix();
    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaMercurio()
{
    int distanciaAteOSol = 50;
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mercury);
    }
    glPushMatrix();
        glTranslatef(distanciaAteOSol*cos(anguloEsferaY/10),0,distanciaAteOSol*sin(anguloEsferaY/10));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(10.1, esferaLados, esferaLados);
    glPopMatrix();

    //DESENHA ORBITA
    seOrbita(distanciaAteOSol);

    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaVenus()
{
int distanciaAteOSol = 80;
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, venus);
    }
    glPushMatrix();
        glTranslatef(distanciaAteOSol*cos(anguloEsferaY/15),0,distanciaAteOSol*sin(anguloEsferaY/15));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(10.4, esferaLados, esferaLados);
    glPopMatrix();

    //DESENHA ORBITA
     seOrbita(distanciaAteOSol);

    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaTerra()
{

    int distanciaAteOSol = 120;
    int tamanhoDaTerra = 10.7;
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, earth);
    }
    glPushMatrix();
        glTranslatef(distanciaAteOSol*cos(anguloEsferaY/20),0,distanciaAteOSol*sin(anguloEsferaY/20));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(tamanhoDaTerra, esferaLados, esferaLados);

        //ORBITA DA LUA
        //glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, moon);
        glRotatef(-60, 1, 0, 0);
        if(orbita)
            desenhaOrbita(14.7,0,0,0);
        glRotatef(90, 1, 0, 0);
        glTranslatef(14.7*cos(3*anguloEsferaY/20),0,14.7*sin(3*anguloEsferaY/20));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        //glRotatef(-60, 1, 0, 0);
        solidSphere(tamanhoDaTerra/10, esferaLados, esferaLados); // LUA
        //ORBITA DA LUA

    glPopMatrix();

    //DESENHA ORBITA
    seOrbita(distanciaAteOSol);

    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaMarte()
{
int distanciaAteOSol = 160;
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mars);
    }
    glPushMatrix();
        glTranslatef(distanciaAteOSol*cos(anguloEsferaY/25),0,distanciaAteOSol*sin(anguloEsferaY/25));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(12, esferaLados, esferaLados);
    glPopMatrix();

    //DESENHA ORBITA
     seOrbita(distanciaAteOSol);

    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaJupiter()
{
int distanciaAteOSol = 200;
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, jupiter);
    }
    //DESENHA ORBITA
    seOrbita(distanciaAteOSol);

    glPushMatrix();
        glTranslatef(distanciaAteOSol*cos(anguloEsferaY/30),0,distanciaAteOSol*sin(anguloEsferaY/30));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(13.8, esferaLados, esferaLados);

    //ANEL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, jupiter_rings);
        glRotatef(30, 1, 0, 0);
        glColor4f(0.824, 0.706, 0.549,0.8);
        solidPartialDisk(19,23,esferaLados,esferaLados,0,360);
        glDisable(GL_BLEND);
        //ANEL

    glPopMatrix();



    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaSaturno()
{
int distanciaAteOSol = 240;
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, saturn);
    }
    glPushMatrix();
        glTranslatef(distanciaAteOSol*cos(anguloEsferaY/35),0,distanciaAteOSol*sin(anguloEsferaY/35));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(13.4, esferaLados, esferaLados);

        //ANEL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, saturn_rings);
        glRotatef(30, 1, 0, 0);
        glColor4f(1,1,1,0.5);
        solidPartialDisk(18,22,esferaLados,esferaLados,0,360);
        glDisable(GL_BLEND);
        //ANEL

    glPopMatrix();

    //DESENHA ORBITA
    seOrbita(distanciaAteOSol);

    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaUrano()
{
int distanciaAteOSol = 280;
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, uranus);
    }

    //DESENHA ORBITA
    seOrbita(distanciaAteOSol);

    glPushMatrix();
        glTranslatef(distanciaAteOSol*cos(anguloEsferaY/40),0,distanciaAteOSol*sin(anguloEsferaY/40));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(12, esferaLados, esferaLados);

        //ANEL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glColor4f(0.000, 1.000, 1.000,0.5);
        glBindTexture(GL_TEXTURE_2D, uranus__rings);
        glRotatef(-45, 1, 0, 0);
        glColor4f(0.686, 0.933, 0.933,0.8);
        solidPartialDisk(14,17,esferaLados,esferaLados,0,360);
        glDisable(GL_BLEND);
        //ANEL

    glPopMatrix();

    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaNetuno()
{
int distanciaAteOSol = 320;
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, neptune);
    }
    glPushMatrix();
        glTranslatef(distanciaAteOSol*cos(anguloEsferaY/45), 0, distanciaAteOSol*sin(anguloEsferaY/45));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(11.7, esferaLados, esferaLados);

        //ANEL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, neptune_rings);
        glRotatef(30, 1, 0, 0);
        glColor4f(0.255, 0.412, 0.882,0.3);
        solidPartialDisk(15,17,esferaLados,esferaLados,0,360);
        glDisable(GL_BLEND);
        //ANEL

    glPopMatrix();

    //DESENHA ORBITA
    seOrbita(distanciaAteOSol);

    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaSkySphere()
{
// Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sky);
    }
    glPushMatrix();
        //glRotatef(anguloEsferaY, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        solidSphere(500, esferaLados, esferaLados);
    glPopMatrix();
    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}

// Callback de desenho
void desenhaCena()
{

    float globAmb[] = { m, m, m, 1.0 };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);        // Luz ambiente global
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);// Enable local viewpoint

    
    // Limpa a tela e o z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    desenhaHUD();

    /*
    if(camera == 0)
    {
        // Posiciona a câmera de acordo com posição x,y do mouse na janela
        gluLookAt(3*(xMouse-larguraJanela/2)/(larguraJanela/128), -3*(yMouse-alturaJanela/2)/(alturaJanela/128) + 3, 5,
                  0, 0, 0,
                  0, 1, 0);
    }
    */
    if(camera == 1)
    {
        // Posiciona a câmera de acordo com posição x,y do mouse na janela
        gluLookAt(0, 400, 50,
                  0, 0, 0,
                  0, 1, 0);
    }


    if(camera == 2)
    {
        // Posiciona a câmera de acordo com posição x,y do mouse na janela
        gluLookAt(0, 150, 100,
                  olharX, olharY, 0,
                  0, 1, 0);
    }

    if(camera == 3)
    {
        int distanciaAteOSol = 120;
        gluLookAt(distanciaAteOSol*cos(anguloEsferaY/20)+20,0,distanciaAteOSol*sin(anguloEsferaY/20)+20,
                    0,0,0,
                    0,1,0 );
    }

    if(planoOrbital)
    {
        glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        desenhaPlanoOrbital();
        glPopMatrix();
    }

    // Propriedades da fonte de luz LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    desenhaSkySphere();
    desenhaSol();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); //Habilita iluminacaos

    desenhaMercurio();
    desenhaVenus();
    desenhaTerra();
    desenhaMarte();
    desenhaJupiter();
    desenhaSaturno();
    desenhaUrano();
    desenhaNetuno();

    glutSwapBuffers();
}

// Callback do evento de teclado
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;

    case 'c':
    case 'C':
        camera++;

        if(camera>3)
            camera = 1;
        break;

    case 'w':
    case 'W':
        olharY+=2;
        break;

    case 's':
    case 'S':
        olharY-=2;
        break;

    case 'a':
    case 'A':
        olharX-=2;
        break;

    case 'd':
    case 'D':
        olharX+=2;
        break;

    case 'o':
    case 'O':
        orbita = !orbita;
        break;

    case 'f':
    case 'F':
        fullScreen = !fullScreen;
        if(fullScreen == true )
        {
            glutFullScreen();
        }

        else glutReshapeWindow(1000, 1000);
        break;

    case 'p':
    case 'P':
        planoOrbital = !planoOrbital;
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

// Callback de redimensionamento
void resize(int w, int h)
{
    larguraJanela = w;
    alturaJanela = h;

    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (float)w/(float)h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void posicionaCamera(int x, int y) {
    xMouse = x;
    yMouse = y;
    glutPostRedisplay();
}

void rotacionaEsfera() {
    anguloEsferaY += .1f;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition (200, 200);
    glutCreateWindow("Luz e Materiais");
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutPassiveMotionFunc(posicionaCamera);
    glutIdleFunc(rotacionaEsfera);

    setup();

    glutMainLoop();
}
