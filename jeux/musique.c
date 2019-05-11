#include "musique.h"

int ouvrir_mixer(){
  if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)== -1)//init API Mixer
    {
      printf("erreur Init mixer %s \n",Mix_GetError());
      exit(-1);
    }
  return 1;
}

void fermeture_mixer(){
  Mix_CloseAudio();//fermeture de l'API
}

