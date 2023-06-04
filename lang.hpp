#include<bits/stdc++.h>
using namespace std;

//Terminal
#define FUNCTION 0	
#define ABRE_CHAVES 1	
#define TIPO 2	
#define ID 3	
#define SE 4	
#define ENQUANTO 5	
#define REPITA 6	
#define VIRGULA 7	
#define CONST_INT 8	
#define CONST_CHAR 9	
#define CONST_FLOAT 10
#define ABRE_PARENTESES 11
#define OP_ARIT_PREC3 12
#define OP_ARIT_PREC2 13
#define OP_ARIT_PREC1 14
#define SENAO 15
#define ATE 16
#define FECHA_CHAVES 17
#define PONTO_VIRGULA 18
#define FECHA_PARENTESES 19
#define RELOP 20
#define FACA 21
#define ENTAO 22
#define DOIS_PONTOS 23
#define IGUAL 24

string emptyAttribute = "N/A";

typedef struct t{
    int type;
    string value;
    int line;
    int column;

    t(int _type, string _value, int _line, int _column) {
        type = _type, value = _value, line = _line, column = _column;
    }
    t() {}
} Token;

Token getToken();

void initialize_lexic();

void finalize_lexic();