#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include "enumType.h"


/*class sintatico
{
private:
    std::stack<typeToken> pilha; // pilha de controle  
    std::map<typeToken, std::map<typeToken, int>> tabela; // tabela parser 

public:
    sintatico( const std::vector<std::pair<typeToken, std::string>> & Tok);
    int proxToken();
   
};*/

void sintatico(const std::vector<std::pair<typeToken, std::string>> );
std::vector<std::pair<typeToken, std::string>> proxToken();

   

