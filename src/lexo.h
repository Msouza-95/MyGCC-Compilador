#include <stdio.h>
#include <ctype.h>


int nextAutomatos (int &partida)
{
	switch(partida)
   {
   		 case  0: return  ; //comentario
   		 case  3: return  6; //se
         case  6: return 11; //faca
         case 11: return 16; //senao
         case 16: return 20; //acabou
         case 20: return 27; //repeat
         case 27: return 33; //until
         case 33: return 38; //read
         case 38: return 44; //write
         case 44: return 46; // +
         case 46: return 48; // -
         case 48: return 50; // *
         case 50: return 52; // /
         case 52: return 54; // =
         case 54: return 56; // <
         case 56: return 58; // (
         case 58: return 60; // )
         case 60: return 62; // ;
         case 62: return 65; // :=
         case 65: return 68; // número
         case 68: return 72; //Identificador ou Final de sentença
         default: return 74;//Retorna Erro...
   }
}