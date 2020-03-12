#include <ostream>
#include <string>
#include <iostream>

#include "enumTipo.h"

class tokens{
            typeToken classe;//Classe do token
   		    char lexema;//Lexema
            int pLinha, pColuna; 
            public:
            void setValues(typeToken,char,int,int);
            void getLexema();
            tokens nextToken();
    };

tokens::nextToken(){

}


 void tokens::setValues(typeToken name, char lex, int l, int c){
        classe = name;
        lexema = lex; 
        pLinha= l;
        pColuna =c;
    };


void tokens::getLexema(){
   // cout<< lexema; 
  //  cout << "asas";
};