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
    arqOut.open("tokens..txt", fstream::out | fstream::app);
    arqOut << " [" << substr << "]" << output << std::endl;
    arqOut.close();
}

typeToken reservadas(const string &test)
{

    if (test == "VALOR")
        return typeToken::VALOR;
    else if (test == "QUEBRADO")
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

    while (!arquivo.eof)
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
                status = 11;
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
            case EOF:
                cout << "Leitura finalizada";
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
            Gravar(stringTest, string("Atribuicao"));
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
                status = 6;
            else if (!isdigit(c))
            {
                status = 7;
                stringTest += c;
            }

            break;

        case 4:

            break;
        case 5:
            auto result = reservadas(stringTest);

            if (result != typeToken::ID)
            {
                // cout << stringTest << ": PALAVRA RESERVADA" << '\n';
                Gravar(stringTest, string("PALAVRA RESERVADA"));
            }
            else
            {
                //cout << stringTest << ": ID" << '\n';
                Gravar(stringTest, ": ID");
            }
            Tokens.push_back(make_pair(result, stringTest));

            stringTest.clear();
            status = 0;

            break;

        case 6:
            c = arquivo.get();
            if (isdigit(c))
            {
                status = 9; /// teste de valor
                stringTest += c;
            }
            else
            {
                cout << "erro";
                throw invalid_argument("algo de erro não está certo, verifique o valo");
            }
            break;
        case 7:

            break;

        case 8:
            //std::cout << "OPERADOR ARITMETICO\n";
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
                stringTest += c;
            break;

        case 10:
            //std::cout << stringTest << ": VALOR" << '\n';
            Gravar(stringTest, string(": VALOR"));
            status = 0;
            stringTest.clear();
            break;
        case 11:

            break;
        case 12:
            if (c == '&')
            {
                //std::cout << stringTest << "operador logico\n";
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

            if (c == '|')
            {
                //std::cout << stringTest << "operador logico\n";
                Tokens.push_back(make_pair(typeToken::OPB, stringTest));
                Gravar(stringTest, string("OPERADOR LOGICO"));
                stringTest.clear();
                status = 0;
            }
            else
                throw invalid_argument("era esperado outro | ");
            break;
        case 14:

            break;
        case 15:
            Tokens.push_back(make_pair(typeToken::NEGACAO, stringTest));
            Gravar(stringTest, string("NEGAÇAO"));
            stringTest.clear();
            status = 0;
            break;
        case 16:

            break;
        case 17:
            //std::cout << stringTest << "PONTO E VIRGULA\n";
            Tokens.push_back(make_pair(typeToken::PONTO_VIRGULA, stringTest));
            Gravar(stringTest, string("PONTO E VIRGULA"));
            stringTest.clear();
            status = 0;
            break;
        case 18:
            //std::cout << stringTest << "Abre parentese\n";
            Tokens.push_back(make_pair(typeToken::ABRE_PARENT, stringTest));
            Gravar(stringTest, string("ABRE PARENTTESE"));
            stringTest.clear();
            status = 0;
            break;
        case 19:
            //std::cout << stringTest << "FECHA parentese\n";
            Tokens.push_back(make_pair(typeToken::FECHA_PARENT, stringTest));
            Gravar(stringTest, string("FECHA PARENTTESE "));
            stringTest.clear();
            status = 0;
            break;
        default:
            throw invalid_argument("TA FODA VUH! REFAÇA");
            break;
        }
    }
    return Tokens;
}
