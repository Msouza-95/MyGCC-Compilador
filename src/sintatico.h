#include <iostream>
#include <map>
#include <stack>
#include "enumType.h"

int lex; 
class sintatico
{
private:
    std::stack<typeToken> pilha; // pilha de controle  
    std::map<typeToken, std::map<typeToken, int>> tabela; // tabela parser 

public:
    sintatico();
   
};

void sintatico();



