#include <stdio.h>
#include <iostream>
#include <cctype>
#include <string>
#include <list>
#include <fstream>
#include "lex.h"

using namespace std;

void Gravar(string substr, string output)
{ // gravar em um arquivo de saida

    std::fstream arqOut;
    arqOut.open("tokens.txt", fstream::out | fstream::app);
    arqOut << " [" << substr << "] ->" << output << std::endl;
    arqOut.close();
}

typeToken reservadas(const string &test)
{

    if (test == "QUEBRADO")
        return typeToken::TIPO;
    else if (test == "INTEIRO")
        return typeToken::TIPO;
    else if (test == "LOGICO")
        return typeToken::TIPO;
    else if (test == "SE")
        return typeToken::SE;
    else if (test == "ENTAO")
        return typeToken::ENTAO;
    else if (test == "ENQUANTO")
        return typeToken::ENQUANTO;
    else if (test == "FACA")
        return typeToken::FACA;
    else if (test == "ACABOU")
        return typeToken::ACABOU;

    return typeToken::ID;
}

vector<pair<typeToken, string>> nextToken(ifstream &arquivo)
{
    vector<pair<typeToken, string>> Tokens; // vetor de tokens
    int status = 0;
    string stringTest; // subre string de teste
    char c;            // caracter de teste

    while (status != EOF)
    {
        switch (status)
        {
        case 0: // estado de partida
            c = arquivo.get();
            switch (c)
            {
            case '=':
                stringTest += c;
                status = 1;
                break;
            case '-':
            case '+':
            case '*':
            case '/':
                stringTest += c;
                status = 8;
                break;
            case '&':
                stringTest += c;
                status = 12;
                break;
            case '|':
                stringTest += c;
                status = 13;
                break;
            case '!':
                stringTest += c;
                status = 15;
                break;
            case ';':
                stringTest += c;
                status = 17;
                break;
            case '(':
                stringTest += c;
                status = 18;
                break;
            case ')':
                stringTest += c;
                status = 19;
                break;
            case '%': // % comenttarios e leva a linha toda
                stringTest += c;
                status = 20;
                break;
            case '<':
            case '>':
                stringTest += c;
                status = 21;
                break;
            case EOF:
                cout << "Leitura finalizada";
                status= c; 
                break;

            default:
                if (isalpha(c))
                {

                    stringTest += c;
                    status = 2;
                }
                else if (isdigit(c))
                {
                    stringTest += c;
                    status = 3;
                }
                else if (isspace(c))
                    break;
                else
                    status = 99; // erro
            }
            break;
        case 1:
            Tokens.push_back(make_pair(typeToken::ATRIBUICAO, stringTest));
            status = 0;
            Gravar(stringTest, string(" :  Atribuicao"));
            stringTest.clear();
            break;

        case 2:
            c = arquivo.get();
            if (!isalnum(c))
                status = 5;
            else
                stringTest += c;
            break;
        case 3:
            c = arquivo.get();
            if (c == ',')
            {
                stringTest += c; //back()= '.';
                status = 6;
            }
            else if (isdigit(c))
            {
                stringTest += c;
                status = 3;
            }
            else if (!isdigit(c))
                status = 10;
            break;

        case 5:
        {
            auto result = reservadas(stringTest);

            if (result != typeToken::ID)
            {
                
                Gravar(stringTest, string(": PALAVRA RESERVADA"));
            }
            else
            {
               
                Gravar(stringTest, ": ID");
            }
            Tokens.push_back(make_pair(result, stringTest));

            stringTest.clear();
            status = 0;
            arquivo.unget();
        }
        break;

        case 6:
            c = arquivo.get();
            ;
            if (isdigit(c))
            {
                status = 9; /// teste de valor
                stringTest += c;
            }
            else
            {
                cout << "erro";
                throw invalid_argument("algo de erado não está certo, verifique o valor");
            }
            break;

        case 8:
           
            Tokens.push_back(make_pair(typeToken::OPA, stringTest));
            Gravar(stringTest, string("OPERADOR ARITMETICO"));
            stringTest.clear();
            status = 0;
            break;
        case 9:
            c = arquivo.get();
            if (!isdigit(c)) // verificar valor
                status = 10;
            else
                status = 3;
            stringTest += c;
            break;

        case 10:
            
            arquivo.unget();

            Gravar(stringTest, string("VALOR"));
            status = 0;
            stringTest.clear();
            break;
        case 12:
            c = arquivo.get();
            if (c == '&')
            {
                
                stringTest += c;
                Tokens.push_back(make_pair(typeToken::OPB, stringTest));
                Gravar(stringTest, string("OPERADOR LOGICO"));
                stringTest.clear();
                status = 0;
            }
            else
            {
                throw invalid_argument("era esperado outro & ");
            }
            break;
        case 13:
             c = arquivo.get();
            if (c == '|')
            {
                
                stringTest += c;
                Tokens.push_back(make_pair(typeToken::OPB, stringTest));
                Gravar(stringTest, string("OPERADOR LOGICO"));
                stringTest.clear();
                status = 0;
            }
            else
                throw invalid_argument("era esperado outro | ");
            break;

        case 15:
            Tokens.push_back(make_pair(typeToken::NEGACAO, stringTest));
            Gravar(stringTest, string("NEGAÇAO"));
            stringTest.clear();
            status = 0;
            break;

        case 17:
           
            Tokens.push_back(make_pair(typeToken::PONTO_VIRGULA, stringTest));
            Gravar(stringTest, string("PONTO E VIRGULA"));
            stringTest.clear();
            status = 0;
            break;
        case 18:
            Tokens.push_back(make_pair(typeToken::ABRE_PARENT, stringTest));
            Gravar(stringTest, string("ABRE PARENTTESE"));
            stringTest.clear();
            status = 0;
            break;
        case 19:
            
            Tokens.push_back(make_pair(typeToken::FECHA_PARENT, stringTest));
            Gravar(stringTest, string("FECHA PARENTTESE "));
            stringTest.clear();
            status = 0;
            break;

        case 21:
            Tokens.push_back(make_pair(typeToken::OPB, stringTest));
            Gravar(stringTest, string("OPERADOR LOGICO"));
            stringTest.clear();
            status = 0;
            break;
        }
    }
    return Tokens;
}
