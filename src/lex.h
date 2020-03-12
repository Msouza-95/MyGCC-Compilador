#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"




int automatos (int &partida)
{
	switch(partida)
   {
   		 case  0: return  3; //Se 
   		 case  3: return  8; //FACA
         case  8: return 14; //SENAO
         case 14: return 21; //ACABOU
         case 21: return 30; //EQUANTO
         case 30: return 38; //INTEIRO
         case 38: return 45; //QUEBRADOs
         case 45: return 52; //LOGICO
         case 52: return 54; //!
         case 54: return 56; // (
         case 56: return 58; // )
         case 58: return 60; // ;
         case 60: return 62; // +
         case 62: return 64; // -
         case 64: return 66; // *
         case 66: return 68; // /
         case 68: return 70; // =
         case 70: return 73; // :=
         case 73: return 76; // &&
         case 76: return 79; // ||
         case 79: return 83; // COMENTARIO 
         case 83: return 86; // NUMERO
         case 86: return 89; // IDENTIFICADO
         case 89: return 92; // espaço em branco
         default: return 99;//Retorna Erro...
   }
}

tokens::nextToken(){
      tokens token; 
      int p; // contador 
      int estado =0; 
   
      /*int m=100; 
      for(m){
         token.valor[i]= NULL; 

      }
*/

      while (1) // loop infinito 
      {
         switch (estado)
         {
         case 0: 
                  c= nextCaracter(); 
                  switch (c) {
               case '=': 
                  estado = 68;
                  break;
               case ',':
                  estado = 4;
                  break;
               case '-':
               case '+':
               case '*':
               case '/':
                  estado = 8;
                  break;
               case '&':
                  estado = 11;
                  break;
               case '|':
                  estado = 13;
                  break;
               case '!':
                  estado = 15;
                  break;
               case ';':
                  estado = 17;
                  break;
               case '(':
                  estado = 18;
                  break;
               case ')':
                  estado = 19;
                  break;
               case '#':
                  estado = 20;
                  break;
               case EOF:
                  estado = c;
                  break;

               default:
                  if (isalpha(c)) {
                     estado = 1;
                  } else if (isdigit(c)) {
                     estado = 3;
                  } else if (isspace(c)) {
                    /* if (c == '\n') {
                        mColCount = 0;
                        ++mLinhaCount;
                     }*/
                     /*lexema.pop_back();
                     break;*/
                  } else {
                    // erro 
                    estado =99;  
                  }
            }
            break;
         case 1 :
               c= nextCaracter(); 
               if(isalpha(c))
                  cout<< "aqui"; 
         break; 
         case 2: 
          
          break;
         
         case 3: 
          
          break;
         
         case 4: 
          
          break;
         
         case 5: 
          
          break;
         
         case 6: 
          
          break;
         
         case 7: 
               token.setValues(typeToken::op,c,1,2);
               token.getLexema; 
          break;
         case 8: 
          
          break;
         case 68: 
            cout<< "foi"; 
          break;
         
         default:
            break;
         } 
      }
      
}