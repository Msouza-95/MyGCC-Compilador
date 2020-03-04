#include <stdio.h>
#include <ctype.h>


int charClass;
char lexema [100];
char nextChar;
int lexLen; 
int token;
int nextToken; 
FILE *in_fp, *fopen;


int main()
{
    /* lendo arquivo de dados de entrada */

    if ((in_fp = fopen("front.in", "r")) == NULL)
        printf("ERROR - cannot open front.in \n");
    else
    {
        getChar();
        do
        {
            lex();
        } while (nextToken != EOF);
    }

    return 0;
}