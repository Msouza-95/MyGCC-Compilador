
#include <iostream>
#include <fstream>
#include "lex.cpp"

//#include "token.h"

using namespace std;
 


using namespace std; 



int main()
{
   
       ifstream arq("exemple.txt"); // abre arquivo passado

      if(!arq.is_open()){
         cout<< "falha em abrir o arquivo\n";
         return EXIT_FAILURE; 
      }else
      {
         std::cout<< "---------Iniciado a Analise Lexica-----------\n\n\n";
         auto Tok = nextToken(arq);
         std::cout<< "---------Analise Lexica Finalizada-----------\n";

      }
  // cin.get();
   arq.close();
    return 0;       
    }

