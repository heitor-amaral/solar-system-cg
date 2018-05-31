#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>

#include "musica.h"

int volume_musica=100;
Mix_Music *musicMenu=NULL;

//Musica de fundo do jogo
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
