
#include <iostream>
#include <fstream>
#include "lex.cpp"
#include <map>
#include <stack>
//#include "sintatico.cpp"

//#include "token.h"

using namespace std;

int sintatico(vector<pair<typeToken, string>> &tok);
vector<pair<typeToken, string>> proxToken(vector<pair<typeToken, string>> &tok);

int main()
{

    ifstream arq("exemple.txt"); // abre arquivo passado

    if (!arq.is_open())
    {
        cout << "falha em abrir o arquivo\n";
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "---------Iniciado a Analise Lexica-----------"<<endl;
        auto Tok = nextToken(arq);
        std::cout << " Gerado Arquivo de log com lexemas abra : tokens.txt "<<endl;
        std::cout << "---------Analise Lexica Finalizada-----------"<<endl;

        auto sint= sintatico(Tok);
        if(sint==1)
        std::cout << "---------Parabens seu programa passou no analise lexico e sintatica -----------"<<endl;
    

    }

    // cin.get();
    arq.close();
    return 0;
}

int sintatico(vector<pair<typeToken, string>> &tok)
{
    std::stack<typeToken> pilha;                          // pilha de controle
    std::map<typeToken, std::map<typeToken, int>> tabela; // tabela parser

    // iniciando a pilha com $ = marca final da pilha e PROGRAMA = gramatica inicial
    pilha.push(typeToken::$);
    pilha.push(typeToken::PROGRAMA);
    int i = 0;

    // iniciando a tabela parser com suas devidas regras

    // Todo esse bloco recebe a regra 1 = <PROGRAMA>::= <comando> <PROGRAMATT>
    tabela[typeToken::PROGRAMA][typeToken::SE] =
        tabela[typeToken::PROGRAMA][typeToken::ENQUANTO] =
            tabela[typeToken::PROGRAMA][typeToken::ID] =
                tabela[typeToken::PROGRAMA][typeToken::TIPO] = 1;
    // Todo esse bloco recebe a regra 2 =<PROGRAMATT>::= <comando> <PROGRAMATT> ou Nulo
    tabela[typeToken::PROGRAMATT][typeToken::SE] =
        tabela[typeToken::PROGRAMATT][typeToken::ENQUANTO] =
            tabela[typeToken::PROGRAMATT][typeToken::ID] =
                tabela[typeToken::PROGRAMATT][typeToken::TIPO] = 2;
    tabela[typeToken::PROGRAMATT][typeToken::SENAO] =
        tabela[typeToken::PROGRAMATT][typeToken::ACABOU] =
            tabela[typeToken::PROGRAMATT][typeToken::$] = typeToken::NULO;
    // Todo esse bloco recebe a regra 3 =<bloco>::= <PROGRAMA>
    tabela[typeToken::BLOCO][typeToken::SE] =
        tabela[typeToken::BLOCO][typeToken::ENQUANTO] =
            tabela[typeToken::BLOCO][typeToken::ID] =
                tabela[typeToken::BLOCO][typeToken::TIPO] = 3;
    // Todo esse bloco recebe a regra 4 = <comando>::= <Condicional>;
    //  5 =  <comando>::= <Repeticao>; 6 = <comando>::= <VAR>;
    tabela[typeToken::COMANDO][typeToken::SE] = 4;
    tabela[typeToken::COMANDO][typeToken::ENQUANTO] = 5;
    tabela[typeToken::COMANDO][typeToken::ID] =
        tabela[typeToken::COMANDO][typeToken::TIPO] = 6;
    //  esse bloco recebe a regra 7 =<Condicional>::= <se><senao>
    tabela[typeToken::CONDICIONAL][typeToken::SE] = 7;
    // esse bloco recebe a regra 8 =<se>::=SE <condicao>FACA <bloco>
    tabela[typeToken::COND_SE][typeToken::SE] = 8;
    // esse bloco recebe a regra 9 =<se>::=<senao>::=SENAO <bloco>ACABOU 
    tabela[typeToken::COND_SENAO][typeToken::SENAO] = 9;
    // esse bloco recebe a regra 10 =<senao>::= ACABOU
    tabela[typeToken::COND_SENAO][typeToken::ACABOU] = 10;
    // esse bloco recebe a regra 11 =<Repeticao>::= ENQUANTO <condicao> FACA <bloco> ACABOU
    tabela[typeToken::REPETICAO][typeToken::ENQUANTO] = 11;
    // esse bloco recebe a regra 12 = <condicao>::= <expressao>
    tabela[typeToken::CONDICAO][typeToken::ID] =
        tabela[typeToken::CONDICAO][typeToken::VALOR] =
            tabela[typeToken::CONDICAO][typeToken::ABRE_PARENT] =
                tabela[typeToken::CONDICAO][typeToken::OPA] =
                    tabela[typeToken::CONDICAO][typeToken::NEGACAO] = 12;
    // esse bloco recebe a regra 13 =<VAR>::= <Atribuicao>
    tabela[typeToken::VAR][typeToken::ID] = 13;
    // esse bloco recebe a regra 14 =<VAR>::= <declaracao>
    tabela[typeToken::VAR][typeToken::TIPO] = 14;
    // esse bloco recebe a regra 15 =<VAR>::= <Atribuicao>::= <identificador>=<expressao>
    tabela[typeToken::ATRIBUICAO][typeToken::ID] = 15;
    // esse bloco recebe a regra 16 =<VAR>::= <declaracao>::=<tipo><identificador>
    tabela[typeToken::DECLARACAO][typeToken::TIPO] = 16;
    // esse bloco recebe a regra 17 =<VAR>::= <expressao>::=<exp><expII>
    tabela[typeToken::EXPRESSAO][typeToken::ID] =
        tabela[typeToken::EXPRESSAO][typeToken::VALOR] =
            tabela[typeToken::EXPRESSAO][typeToken::ABRE_PARENT] = 17;
    // esse bloco recebe a regra 18 =<expressao>::=<nop><expressao>
    tabela[typeToken::EXPRESSAO][typeToken::OPA] =
        tabela[typeToken::EXPRESSAO][typeToken::NEGACAO] = 18;
    // esse bloco recebe a regra 19 =<exp>::=<identificador>
    tabela[typeToken::EXP][typeToken::ID] = 19;
    // esse bloco recebe a regra 20 =<exp>::=<valor>
    tabela[typeToken::EXP][typeToken::VALOR] = 20;
    // esse bloco recebe a regra 21 =<exp>::=(<expressao>)
    tabela[typeToken::EXP][typeToken::ABRE_PARENT] = 21;
    // esse bloco recebe a regra 22 =<expII>::=  <oper><expressao>
    tabela[typeToken::EXPII][typeToken::OPA] =
        tabela[typeToken::EXPII][typeToken::OPB] =22;
    // esse bloco recebe a regra 23 =<expII>::=   £
    tabela[typeToken::EXPII][typeToken::PONTO_VIRGULA] =
        tabela[typeToken::EXPII][typeToken::FACA] =
            tabela[typeToken::EXPII][typeToken::FECHA_PARENT] = typeToken::NULO;
    // esse bloco recebe a regra 24 = <oper>::= <opa>; 25= <oper>::= <opb>
    tabela[typeToken::OPER][typeToken::OPA]  = 24;
    tabela[typeToken::OPER][typeToken::OPB] = 25;
    // esse bloco recebe a regra 26 <nop>::= <sinal>; 27 = <nop>::= !
    tabela[typeToken::NOP][typeToken::OPA] = 26;
    tabela[typeToken::NOP][typeToken::NEGACAO] = 27;

    // -------------------fim tabela parser---------------

    while (pilha.size()>0)
    {
        
        if(pilha.top()== typeToken::$ && tok[i].first ==typeToken::$){
                cout <<"Tudo certo! - Analise completa!"<<endl;
                return 1; 
        }
                

        
        // cout<<pilha.top()<<endl;
        if (tok[i].first == pilha.top())
        {
            std::cout << "massa bateu: " << endl;
            //std::cout << "tirei = " << pilha.top()<< endl;
            pilha.pop();
            i++;
        }
        else
        {

            std::cout << "nao bateu vamos olhar na tabela regra" << endl;
            
            const auto topo = pilha.top();
           // cout << "topo: " << topo<<endl; 
            const auto prod = tabela[topo][tok[i].first];

            // cout << "tok: " << tok[i].first << endl;
         //   cout << " producao : " << prod << endl;
          //  std::cout << "tirei = " << pilha.top()<< endl;
            pilha.pop();
             //cout << " posicao do vector : " << i << endl;
            switch (prod)
            {
            case 1: //<PROGRAMA>::= <comando> <PROGRAMATT>
                pilha.push(typeToken::PROGRAMATT);
                pilha.push(typeToken::COMANDO);
                
                break;
            case 2: // <PROGRAMATT>::= <comando> <PROGRAMATT>
                pilha.push(typeToken::PROGRAMATT);
                pilha.push(typeToken::COMANDO);

                break;
            case 3: //<bloco>::= <PROGRAMA>
                pilha.push(typeToken::PROGRAMA);
                
                break;
            case 4: //<comando>::= <Condicional>
                pilha.push(typeToken::CONDICIONAL);
                
                break;
            case 5: //<comando>::= <Repeticao>
                pilha.push(typeToken::REPETICAO);
             
                break;
            case 6: //<comando>::= <VAR>;
                pilha.push(typeToken::PONTO_VIRGULA);
                pilha.push(typeToken::VAR);
       
                break;
            case 7: //<Condicional>::= <se><senao>
                pilha.push(typeToken::COND_SENAO);
                pilha.push(typeToken::COND_SE);
                
                break;
            case 8: //<se>::=SE <condicao>FACA <bloco>
                pilha.push(typeToken::BLOCO);
                pilha.push(typeToken::FACA);
                pilha.push(typeToken::CONDICAO);
                pilha.push(typeToken::SE);
               
                break;
            case 9: //<se>::=<senao>::=SENAO <bloco>ACABOU
                pilha.push(typeToken::ACABOU);
                pilha.push(typeToken::BLOCO);
                pilha.push(typeToken::SENAO);
               
                break;
            case 10: // <senao>::= ACABOU
                pilha.push(typeToken::ACABOU);
                break;
            case 11: //<Repeticao>::= ENQUANTO <condicao> FACA <bloco> ACABOU
                pilha.push(typeToken::ACABOU);
                pilha.push(typeToken::BLOCO);
                pilha.push(typeToken::FACA);
                pilha.push(typeToken::CONDICAO);
                pilha.push(typeToken::ENQUANTO);
                break;
            case 12: //<condicao>::= <expressao>
                pilha.push(typeToken::EXPRESSAO);
                break;
            case 13: //<VAR>::= <Atribuicao>
                pilha.push(typeToken::ATRIBUICAO);
                break;
            case 14: //<VAR>::= <declaracao>
                pilha.push(typeToken::DECLARACAO);

                break;
            case 15: //<VAR>::= <Atribuicao>::= <identificador>=<expressao>
                pilha.push(typeToken::EXPRESSAO);
                pilha.push(typeToken::ATRIBUICAO);
                pilha.push(typeToken::ID);
                break;
            case 16: //<VAR>::= <declaracao>::=<tipo><identificador>
                pilha.push(typeToken::ID);
                pilha.push(typeToken::TIPO);
                break;
            case 17: //<VAR>::= <expressao>::=<exp><expII>
                pilha.push(typeToken::EXPII);
                pilha.push(typeToken::EXP);
                break;
            case 18: //<expressao>::=<nop><expressao>
                pilha.push(typeToken::EXPRESSAO);
                pilha.push(typeToken::NEGACAO);
                break;
            case 19: // <exp>::=<identificador>
                pilha.push(typeToken::ID);
                break;
            case 20: // <exp>::=<valor>
                pilha.push(typeToken::VALOR);
                break;
            case 21: // <exp>::=(<expressao>)
                pilha.push(typeToken::FECHA_PARENT);
                pilha.push(typeToken::EXPRESSAO);
                pilha.push(typeToken::ABRE_PARENT);
                break;
            case 22: //<expII>::=  <oper><expressao>
                pilha.push(typeToken::EXPRESSAO);
                pilha.push(typeToken::OPER);
                break;
                // case 23:

                // break;
            case 24: //<oper>::= <opa>
                pilha.push(typeToken::OPA);
                break;
            case 25: //<oper>::= <opb>
                pilha.push(typeToken::OPB);
                break;
            case 26: // <nop>::= <opa>
                pilha.push(typeToken::OPA);
                break;
            case 27: // <nop>::= !
                pilha.push(typeToken::NEGACAO);
                break;
            case NULO: // nulo
                break;

            default:
               throw invalid_argument("erro sintatico - Nao exite essa producao");
                return 0; 

                break;
            }
           ///
        }
        
    }
    return 0; 
}

/*
vector<pair<typeToken,string>> proxToken(vector<pair<typeToken, string> > &tok){
   for(Tok.size()){
              cout<<Tok[i].first<<endl; 
            } tok.get_allocator() ;
          

}*/