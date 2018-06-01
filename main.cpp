#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <math.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>

# define menu 1
# define aplicacao 2
# define sair 3


using namespace std;

int estado;

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
bool iluminacao = true;
int cont = 0;

bool modoTerraPlana = false;


bool orbita = false;
bool fullScreen = false;
bool planoOrbital = false;
bool normal = false;

//CAMERA
int camera = 1;
int olharX = 0;
int olharY = 0;
float zoom = 1;
//CAMERA

//VARIAVEIS DE TEXTURA
static int sun;
static int mercury;
static int venus;
static int earth;
static int flatEarth;
static int groundFlatEarth;
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
static int stewart;
static int inicio;
static int Sair;
//VARIAVEIS DE TEXTURA

//ILUMINACAO
float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
float lightDif0[] = { d, d, d, 1.0 };
float lightSpec0[] = { e, e, e, 1.0 };
float lightPos0[] = { 0.5, 0.5, 0.5, 1 };
//ILUMINACAO

void escreveTexto(void* font, char* s, float x, float y,float z);

void escreveNumero(void* font, int numero, float x, float y, float z);

void carregaTextura();

//Musica de fundo do jogo
int volume_musica=100;
Mix_Music *musicMenu=NULL;

void iniciar_musica(char  *music){
	if(!Mix_PlayingMusic()){
		Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,1024);
		//atexit(Mix_LoadMUS(music));
		musicMenu=Mix_LoadMUS(music);
		Mix_VolumeMusic(volume_musica);
		Mix_PlayMusic(musicMenu,-1);        
	}
}
void parar_musica(){
	if(Mix_PlayingMusic()){
		Mix_FadeOutMusic(1000);
	}
}
//Musica de fundo do jogo

// Configuração inicial do OpenGL e GLUT

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

void desenhaCubo(float tamanho)
{
     // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, stewart);
    glBegin(GL_TRIANGLE_FAN);
        
        // Associamos um canto da textura para cada vértice
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-tamanho, -tamanho,  tamanho/4);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( tamanho, -tamanho,  tamanho/4);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( tamanho,  tamanho,  tamanho/4);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-tamanho,  tamanho,  tamanho/4);
		// Back Face
		 glVertex3f(-tamanho, -tamanho, -tamanho/4);
		 glVertex3f(-tamanho,  tamanho, -tamanho/4);
		 glVertex3f( tamanho,  tamanho, -tamanho/4);
		 glVertex3f( tamanho, -tamanho, -tamanho/4);
		// Top Face
		 glVertex3f(-tamanho,  tamanho, -tamanho/4);
		 glVertex3f(-tamanho,  tamanho,  tamanho/4);
		 glVertex3f( tamanho,  tamanho,  tamanho/4);
		 glVertex3f( tamanho,  tamanho, -tamanho/4);
		// Bottom Face
		 glVertex3f(-tamanho, -tamanho, -tamanho/4);
		 glVertex3f( tamanho, -tamanho, -tamanho/4);
		 glVertex3f( tamanho, -tamanho,  tamanho/4);
		 glVertex3f(-tamanho, -tamanho,  tamanho/4);
		// Right face
		 glVertex3f( tamanho, -tamanho, -tamanho/4);
		 glVertex3f( tamanho,  tamanho, -tamanho/4);
		 glVertex3f( tamanho,  tamanho,  tamanho/4);
		 glVertex3f( tamanho, -tamanho,  tamanho/4);
		// Left Face
		 glVertex3f(-tamanho, -tamanho, -tamanho/4);
		 glVertex3f(-tamanho, -tamanho,  tamanho/4);
		 glVertex3f(-tamanho,  tamanho,  tamanho/4);
		 glVertex3f(-tamanho,  tamanho, -tamanho/4);

    glEnd();

    //glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void desenhaHUD()
{
    float posX1 = 40;
    float posX2 = 28;
    float posX3 = 25;

    float posY1 = 38;
    float posY2 = 36;
    float posY3 = 34;
    float posY4 = 32;
    float posY5 = 30;
    float posY6 = 28;
    float posZ = 40;

    glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "CAMERA", -posX1, posY1, -posZ); //x,y,z
    escreveNumero(GLUT_BITMAP_HELVETICA_18, camera, -posX2, posY1, -posZ);

    if(camera < 3)
    {
        if(iluminacao)
        {
            escreveTexto(GLUT_BITMAP_HELVETICA_18, "ILUMINACAO ON", -posX1, posY2, -posZ); //x,y,z    
        }

        else escreveTexto(GLUT_BITMAP_HELVETICA_18, "ILUMINACAO OFF", -posX1, posY2, -posZ); //x,y,z
    }

    escreveTexto(GLUT_BITMAP_HELVETICA_18, "Comandos", posX3, posY1, -posZ); //x,y,z
    escreveTexto(GLUT_BITMAP_HELVETICA_12, "C - Muda de camera", posX3, posY2, -posZ); //x,y,z
    escreveTexto(GLUT_BITMAP_HELVETICA_12, "I - Liga/Desliga ilumiacao", posX3, posY3, -posZ); //x,y,z
    escreveTexto(GLUT_BITMAP_HELVETICA_12, "O - Liga/Desliga orbitas", posX3, posY4, -posZ); //x,y,z
    escreveTexto(GLUT_BITMAP_HELVETICA_12, "P - Liga/Desliga plano orbital", posX3, posY5, -posZ); //x,y,z    
    escreveTexto(GLUT_BITMAP_HELVETICA_12, "WASD - Movimenta a camera", posX3, posY6, -posZ); //x,y,z
    
}

void desenhaOrbita(float raio, float x, float y, float z)

{
    float angulo;
    int i;    

    if(iluminacao)
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0); //Desabilita iluminacaos

        glBegin(GL_LINE_LOOP);

        for (i = 0; i <= esferaLados; i++) 
        {
            angulo = 2 * M_PI * i / esferaLados;
            glVertex3f(x + 1.2*cos(angulo) * raio, y + sin(angulo) * raio, z);
        }

        glEnd();

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0); //Habilita iluminacaos
    } else
      {
        glBegin(GL_LINE_LOOP);

        for (i = 0; i <= esferaLados; i++) 
        {
            angulo = 2 * M_PI * i / esferaLados;
            glVertex3f(x + 1.2*cos(angulo) * raio, y + sin(angulo) * raio, z);
        }

        glEnd();
                
      }
}

void quadradoDotamanhoDaTela(GLint qualTextura)
{
    glDisable(GL_LIGHTING); // Desabilita iluminação
    
    glColor4f(1,1,1,1);

    int tamanho = 10;
    // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, qualTextura);
    glBegin(GL_TRIANGLE_FAN);
        
        // Associamos um canto da textura para cada vértice
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-tamanho, -tamanho,  -tamanho);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( tamanho, -tamanho,  -tamanho);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( tamanho,  tamanho,  -tamanho);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-tamanho,  tamanho,  -tamanho);

     glEnd();

     glDisable(GL_TEXTURE_2D);
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
                    glTexCoord2f(xVertice, yVerticesLinhaDeCima);  glVertex2f(xVertice  , yVerticesLinhaDeCima);
                    glTexCoord2f(xVertice, yVerticesLinhaDeBaixo); glVertex2f(xVertice  , yVerticesLinhaDeBaixo);
                }
            glEnd();
        }
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}


void desenhaSol()
{
    
// Desenha a esfera grande e bem arredondada
    if (usarTextura) 
    {
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
    if (usarTextura) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mercury);
    }

    glPushMatrix();
        glTranslatef(distanciaAteOSol*1.2*cos(anguloEsferaY/10),0,distanciaAteOSol*sin(anguloEsferaY/10));
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
    if (usarTextura) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, venus);
    }

    glPushMatrix();
        glTranslatef(distanciaAteOSol*1.2*cos(anguloEsferaY/15),0,distanciaAteOSol*sin(anguloEsferaY/15));
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

//Funcao que desenha terra plana
void terraPlana()
{
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    // chama 01 glNormal para cada vértice.. poderia ser
    // GLU_FLAT (01 por face) ou GLU_NONE
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    // chama 01 glTexCoord por vértice
    gluQuadricTexture(quadObj, GL_TRUE);

    //Parte de cima da Terra plana
    glBindTexture(GL_TEXTURE_2D, earth);
    gluDisk(quadObj, 0, 10, 20, 2);

    //Parte do baixo da Terra plana
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, groundFlatEarth);
        glTranslatef(0,0,-2);
        gluCylinder(quadObj, 2, 10, 2, 20,20);
    glPopMatrix();
    
    
    gluDeleteQuadric(quadObj);
}

void desenhaLua(float tamanhoDaTerra)
{
    //ORBITA DA LUA       
    glBindTexture(GL_TEXTURE_2D, moon);
    glRotatef(-60, 1, 0, 0);
        
    if(orbita)
    {
        desenhaOrbita(14.7,0,0,0);
    }            

    glRotatef(90, 1, 0, 0);
    glTranslatef(14.7*1.2*cos(3*anguloEsferaY/20),0,14.7*sin(3*anguloEsferaY/20));
    glRotatef(2*anguloEsferaY, 0, 1, 0);
    solidSphere(tamanhoDaTerra/10, esferaLados, esferaLados); // LUA
    //ORBITA DA LUA
}

void desenhaStewart(int distanciaAteOSol)
{
    //STEWART
    glTranslatef(distanciaAteOSol*1.2*cos(anguloEsferaY/20),0,distanciaAteOSol*sin(anguloEsferaY/20));
    glRotatef(-90, 1, 0, 0);        

    if(orbita)
    {
        desenhaOrbita(14.7,0,0,0);
    }             

    glRotatef(90, 1, 0, 0);
    glTranslatef(14.7*1.2*cos(anguloEsferaY/20),0,14.7*sin(anguloEsferaY/20));               
    desenhaCubo(2);
    //STEWART

}

void desenhaTerra()
{

    int distanciaAteOSol = 120;
    float tamanhoDaTerra = 10.7;

// Desenha a esfera grande e bem arredondada
    if (usarTextura) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, earth);
    }

    glPushMatrix();
        glTranslatef(distanciaAteOSol*1.2*cos(anguloEsferaY/20),0,distanciaAteOSol*sin(anguloEsferaY/20));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);

        if(modoTerraPlana)
        {
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);

            terraPlana();

            if(iluminacao)
            {
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
            }

        }

        else{

            solidSphere(tamanhoDaTerra, esferaLados, esferaLados);
        }
        

        desenhaLua(tamanhoDaTerra);        

    glPopMatrix();

    glPushMatrix();

        desenhaStewart(distanciaAteOSol);       

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
    if (usarTextura) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mars);
    }

    glPushMatrix();
        glTranslatef(distanciaAteOSol*1.2*cos(anguloEsferaY/25),0,distanciaAteOSol*sin(anguloEsferaY/25));
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
    int raioAnelPequeno = 19;
    int raioAnelGrande = 23;

    // Desenha a esfera grande e bem arredondada
    if (usarTextura) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, jupiter);
    }

    //DESENHA ORBITA
    seOrbita(distanciaAteOSol);

    glPushMatrix();
        glTranslatef(distanciaAteOSol*1.2*cos(anguloEsferaY/30),0,distanciaAteOSol*sin(anguloEsferaY/30));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(13.8, esferaLados, esferaLados);

        //ANEL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, jupiter_rings);
        glRotatef(30, 1, 0, 0);
        glColor4f(0.824, 0.706, 0.549,0.8);
        solidPartialDisk(raioAnelPequeno, raioAnelGrande, esferaLados, esferaLados, 0, 360);
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
    int raioAnelPequeno = 18;
    int raioAnelGrande = 22;

    // Desenha a esfera grande e bem arredondada
    if (usarTextura) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, saturn);
    }

    glPushMatrix();
        glTranslatef(distanciaAteOSol*1.2*cos(anguloEsferaY/35),0,distanciaAteOSol*sin(anguloEsferaY/35));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(13.4, esferaLados, esferaLados);

        //ANEL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, saturn_rings);
        glRotatef(30, 1, 0, 0);
        glColor4f(1,1,1,0.5);
        solidPartialDisk(raioAnelPequeno, raioAnelGrande, esferaLados, esferaLados, 0, 360);
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
    int raioAnelPequeno = 14;
    int raioAnelGrande = 17;

    // Desenha a esfera grande e bem arredondada
    if (usarTextura) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, uranus);
    }

    //DESENHA ORBITA
    seOrbita(distanciaAteOSol);

    glPushMatrix();
        glTranslatef(distanciaAteOSol*1.2*cos(anguloEsferaY/40),0,distanciaAteOSol*sin(anguloEsferaY/40));
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
        solidPartialDisk(raioAnelPequeno, raioAnelGrande, esferaLados, esferaLados, 0, 360);
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
    int raioAnelPequeno = 15;
    int raioAnelGrande = 17;

    // Desenha a esfera grande e bem arredondada
    if (usarTextura) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, neptune);
    }

    glPushMatrix();
        glTranslatef(distanciaAteOSol*1.2*cos(anguloEsferaY/45), 0, distanciaAteOSol*sin(anguloEsferaY/45));
        glRotatef(2*anguloEsferaY, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        solidSphere(11.7, esferaLados, esferaLados);

        //ANEL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, neptune_rings);
        glRotatef(30, 1, 0, 0);
        glColor4f(0.255, 0.412, 0.882,1);
        solidPartialDisk(raioAnelPequeno, raioAnelGrande, esferaLados, esferaLados, 0, 360);
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
    if (usarTextura) 
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sky);
    }

    glPushMatrix();        
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

    if(estado == menu)
    {
        quadradoDotamanhoDaTela(inicio);
    }
    
    if(estado == aplicacao)
    {
        desenhaHUD();

        int distanciaAteOSol;
        //int distanciaTotal;      
        
        if(camera == 1) //camera de cima
        {        
            gluLookAt(0, 400, 50,
                    0, 0, 0,
                    0, 1, 0);
        }


        if(camera == 2) // camera inclinada WASD
        {        
            gluLookAt(0, 150, 100,
                    olharX, olharY, 0,
                    0, 1, 0);
        }
        

        if(camera == 3) //MERCURIO
        {
            distanciaAteOSol = 50;
            
            gluLookAt(20*1.2*cos(anguloEsferaY/10) + distanciaAteOSol*1.2*cos(anguloEsferaY/10) + olharX, olharY, 20*1.2*sin(anguloEsferaY/10) + distanciaAteOSol*sin(anguloEsferaY/10),
                    distanciaAteOSol*1.2*cos(anguloEsferaY/10), 0 ,distanciaAteOSol*sin(anguloEsferaY/10),
                    0,1,0);  
        }

        if(camera == 4) //VENUS
        {
            distanciaAteOSol = 80;
            
            gluLookAt(20*1.2*cos(anguloEsferaY/15) + distanciaAteOSol*1.2*cos(anguloEsferaY/15) + olharX, olharY, 20*1.2*sin(anguloEsferaY/15) + distanciaAteOSol*sin(anguloEsferaY/15),
                    distanciaAteOSol*1.2*cos(anguloEsferaY/15), 0 ,distanciaAteOSol*sin(anguloEsferaY/15),
                    0,1,0);

        }

        if(camera == 5) //TERRA ->  //CAMERA NO SATÉLITE ESPECIAL
        {
            distanciaAteOSol = 130;
            
            gluLookAt(zoom*20*1.2*cos(anguloEsferaY/20) + distanciaAteOSol*1.2*cos(anguloEsferaY/20) + olharX , 1 + olharY, zoom*20*1.2*sin(anguloEsferaY/20) + distanciaAteOSol*sin(anguloEsferaY/20),
                    distanciaAteOSol*1.2*cos(anguloEsferaY/20), 0 , distanciaAteOSol*sin(anguloEsferaY/20),
                    0,1,0);

        }

        if(camera == 6) //MARTE
        {
            distanciaAteOSol = 160;
            
            gluLookAt(20*1.2*cos(anguloEsferaY/25) + distanciaAteOSol*1.2*cos(anguloEsferaY/25) + olharX, olharY, 20*1.2*sin(anguloEsferaY/25) + distanciaAteOSol*sin(anguloEsferaY/25),
                    distanciaAteOSol*1.2*cos(anguloEsferaY/25), 0 ,distanciaAteOSol*sin(anguloEsferaY/25),
                    0,1,0);

        }

        if(camera == 7) //JUPITER
        {
            distanciaAteOSol = 200;
        
            gluLookAt(20*1.2*cos(anguloEsferaY/30) + distanciaAteOSol*1.2*cos(anguloEsferaY/30) + olharX, olharY, 20*1.2*sin(anguloEsferaY/30) + distanciaAteOSol*sin(anguloEsferaY/30),
                    distanciaAteOSol*1.2*cos(anguloEsferaY/30), 0 ,distanciaAteOSol*sin(anguloEsferaY/30),
                    0,1,0);

        }

        if(camera == 8) //SATURNO
        {
            distanciaAteOSol = 240;
            
            gluLookAt(20*1.2*cos(anguloEsferaY/35) + distanciaAteOSol*1.2*cos(anguloEsferaY/35) + olharX, olharY, 20*1.2*sin(anguloEsferaY/35) + distanciaAteOSol*sin(anguloEsferaY/35),
                    distanciaAteOSol*1.2*cos(anguloEsferaY/35), 0 ,distanciaAteOSol*sin(anguloEsferaY/35),
                    0,1,0);

        }

        if(camera == 9) //URANO
        {
            distanciaAteOSol = 280;
            
            gluLookAt(20*1.2*cos(anguloEsferaY/40) + distanciaAteOSol*1.2*cos(anguloEsferaY/40) + olharX, olharY, 20*1.2*sin(anguloEsferaY/40) + distanciaAteOSol*sin(anguloEsferaY/40),
                    distanciaAteOSol*1.2*cos(anguloEsferaY/40), 0 ,distanciaAteOSol*sin(anguloEsferaY/40),
                    0,1,0);

        }

        if(camera == 10) //NETUNO
        {
            distanciaAteOSol = 320;
            
            gluLookAt(20*1.2*cos(anguloEsferaY/45) + distanciaAteOSol*1.2*cos(anguloEsferaY/45) + olharX , olharY, 20*1.2*sin(anguloEsferaY/45) + distanciaAteOSol*sin(anguloEsferaY/45),
                    distanciaAteOSol*1.2*cos(anguloEsferaY/45), 0 ,distanciaAteOSol*sin(anguloEsferaY/45),
                    0,1,0);

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

        //desenhaCubo();

        desenhaSkySphere();
        desenhaSol();    

        if(iluminacao)
        {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0); //Habilita iluminacaos
        } else
        {
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0); //Desabilita iluminacaos        
        }

        desenhaMercurio();
        desenhaVenus();
        desenhaTerra();
        desenhaMarte();
        desenhaJupiter();
        desenhaSaturno();
        desenhaUrano();
        desenhaNetuno(); 
    }

    if(estado == sair)
    {
        quadradoDotamanhoDaTela(Sair);
    }

    glutSwapBuffers();
}

// Callback do evento de teclado
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 13:
        if(estado == menu)
        {
            estado = aplicacao;
        }
        break;

    case 27:
        if(estado == aplicacao)
        {
            estado++;
        }
        break;

    case 't':
    case 'T':
        modoTerraPlana = !modoTerraPlana;
        break;

    case 'i':
    case 'I':
        iluminacao = !iluminacao;
        break;
    case 'c':
    case 'C':
        camera++;

        if(camera>= 3 && camera<=10)
        {
            if(iluminacao)
            {
                cont = 1;
                iluminacao = !iluminacao;
            }
        }

        if(camera > 10)
        {
            camera = 1;

            if(cont == 1)
            {
                iluminacao = !iluminacao;
                cont = 0;
            }
        }
            
        break;

    case 'w':
    case 'W':
        olharY+=2;
        break;

    case 's':
    case 'S':
        if(estado == sair)
        {
            exit(0);
        }

        if(estado == aplicacao)
        {
            olharY-=2;
        }        
        break;

    case 'n':
    case 'N':
        if(estado == sair)
        {
            estado = aplicacao;
        }

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

    case 45:
        zoom += 0.2;
        if(zoom == 0)
            zoom = 0.2;
        
        if(zoom > 3)
            zoom = 3;
        break; 

    case 43:
        zoom -= 0.2;
        if(zoom == 0)
            zoom = -0.2;

        if(zoom < 0.4)
            zoom = 0.4;
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

void setup(void)
{    
    glClearColor(0,0,0, 0.0);
    glEnable(GL_DEPTH_TEST);  // Ativa teste Z

    estado = 1;

    carregaTextura();

    iniciar_musica("Heliosphere.mp3");

    float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

    // Definindo as propriedades do material
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    // Esconder o ponteiro do mouse quando dentro da janela
    glutSetCursor(GLUT_CURSOR_NONE);
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
    glutCreateWindow("SISTEMA SOLAR V1.0");
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);    
    glutIdleFunc(rotacionaEsfera);

    setup();

    glutMainLoop();
}

void carregaTextura()
{
    //carrega textura inicio
    inicio = SOIL_load_OGL_texture
	(
		"texturas/inicio.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(inicio == 0)
    {
        cout << "Problema ao carregar textura 0: " << SOIL_last_result() << endl;
    }

    //CARREGA TEXTURA SAIDA
    Sair = SOIL_load_OGL_texture
	(
		"texturas/Sair.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(Sair == 0)
    {
        cout << "Problema ao carregar textura 0: " << SOIL_last_result() << endl;
    }
    
    //carreta textura stewart
    stewart = SOIL_load_OGL_texture
	(
		"texturas/stewart.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(stewart == 0)
    {
        cout << "Problema ao carregar textura 0: " << SOIL_last_result() << endl;
    }

    // Carrega a textura do Sol
    sun = SOIL_load_OGL_texture
	(
		"texturas/sun.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(sun == 0)
    {
        cout << "Problema ao carregar textura 1: " << SOIL_last_result() << endl;
    }

    //MERCURIO
    mercury = SOIL_load_OGL_texture
	(
		"texturas/mercury.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(mercury == 0)
    {
        cout << "Problema ao carregar textura 2: " << SOIL_last_result() << endl;
    }

     //VENUS
    venus = SOIL_load_OGL_texture
	(
		"texturas/venus.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(venus == 0)
    {
        cout << "Problema ao carregar textura 3: " << SOIL_last_result() << endl;
    }

    // Carrega a textura da terra
    earth = SOIL_load_OGL_texture
	(
		"texturas/earth.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(earth == 0)
    {
        cout << "Problema ao carregar textura 4: " << SOIL_last_result() << endl;
    }


    groundFlatEarth = SOIL_load_OGL_texture
	(
		"texturas/ground.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);



    if(groundFlatEarth == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }

    // MARTE
    mars = SOIL_load_OGL_texture
	(
		"texturas/mars.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(mars == 0)
    {
        cout << "Problema ao carregar textura 5: " << SOIL_last_result() << endl;
    }

    // jupiter
    jupiter = SOIL_load_OGL_texture
	(
		"texturas/jupiter.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(jupiter == 0)
    {
        cout << "Problema ao carregar textura 6: " << SOIL_last_result() << endl;
    }

    //jupiter_rings
    jupiter_rings = SOIL_load_OGL_texture
	(
		"texturas/jupiter_rings.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(jupiter_rings == 0)
    {
        cout << "Problema ao carregar textura 7: " << SOIL_last_result() << endl;
    }

    // saturn
    saturn = SOIL_load_OGL_texture
	(
		"texturas/saturn.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(saturn == 0)
    {
        cout << "Problema ao carregar textura 8: " << SOIL_last_result() << endl;
    }

    // saturn_ring
    saturn_rings = SOIL_load_OGL_texture
	(
		"texturas/saturn_rings.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(saturn_rings == 0)
    {
        cout << "Problema ao carregar textura 9: " << SOIL_last_result() << endl;
    }

     // uranus
    uranus = SOIL_load_OGL_texture
	(
		"texturas/uranus.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(uranus == 0)
    {
        cout << "Problema ao carregar textura 10: " << SOIL_last_result() << endl;
    }

     // uranus rings
    uranus__rings = SOIL_load_OGL_texture
	(
		"texturas/uranus__rings.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(uranus__rings == 0)
    {
        cout << "Problema ao carregar textura 11: " << SOIL_last_result() << endl;
    }

     // neptune
    neptune = SOIL_load_OGL_texture
	(
		"texturas/neptune.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(neptune == 0)
    {
        cout << "Problema ao carregar textura 12: " << SOIL_last_result() << endl;
    }

    //neptune_rings
    neptune_rings = SOIL_load_OGL_texture
	(
		"texturas/neptune_rings.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(neptune_rings == 0)
    {
        cout << "Problema ao carregar textura 13: " << SOIL_last_result() << endl;
    }


    // Carrega a textura Skysphere
    sky = SOIL_load_OGL_texture
	(
		"texturas/sky.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(sky == 0)
    {
        cout << "Problema ao carregar textura 14: " << SOIL_last_result() << endl;
    }

    // Carrega a textura Lua
    moon = SOIL_load_OGL_texture
	(
		"texturas/moon.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(moon == 0)
    {
        cout << "Problema ao carregar textura 15: " << SOIL_last_result() << endl;
    }
}

void escreveTexto(void* font, char* s, float x, float y,float z)
{
  unsigned int i;

  glRasterPos3f(x, y, z);

  for (i = 0; i < strlen (s); i++)
  {
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
  {
     glutBitmapCharacter(font, buffer[i]);
  }
}


