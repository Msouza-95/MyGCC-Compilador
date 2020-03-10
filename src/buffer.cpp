
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
#define for(b) for(int i=0;i<b;i++)

using namespace std; 

/*---------------------------Definindo tipo-----------------------------------*/
	typedef struct token{
            int classe;//Classe do token
   			char valor[100];//Lexema
            int posicaoL;//Linha do lexema
    }token;
/*----------------------------------------------------------------------------*/
  
  char analise; // caracter a ser analisado 
  int line=1; 
  int  initLexa =0; 
  int nextt = 0; // aponta para proximo
  char *vector; // vetor com caracteres do arquivo 
/* -------------------------------------------------------*/


void openFile(char* nameFile){
    FILE *pointerFile;
    char caracter; 
    int bloco = 0 ;// controlador de coluna 
    int aux= 0; // aux de inserção 

    // abrindoo aquivo 
    if((pointerFile = fopen(nameFile, "r"))== NULL){
        cout << "Deu ruim!" << endl; 
        cout << "Verificar se endereco do arquivo esta certinho e tentar novamente"<< endl; 
    }else{
        while ((caracter=getc(pointerFile))!=EOF)
        {
            bloco++; 
        }

        vector = new char[bloco]; 

        for(bloco){
            vector[i]=NULL; 
        }
     
        rewind(pointerFile); // posiciona o ponteiro no inicio do arquivo
         while ((caracter=getc(pointerFile))!=EOF)
        {
            vector[aux]=caracter;
            aux++; 
        }
        vector[bloco]= '\0'; // marcando final no vetor 
        fclose; 
     
    }

}

void nextCaracter(){
    
    analise= vector[nextt];
    if(analise=='\n'){
        line++; 
    }

}