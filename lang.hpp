#include<iostream>
using namespace std;

//Terminal
#define NOTOKEN -2
#define ERROR -1
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

//Not terminal
#define INI 25 
#define BLOCO 26 
#define BLOCO_AUX 27 
#define DECL_VARS 28 
#define DECL_VARS_FAT 29 
#define DECL_VAR 30 
#define LISTA_ID 31 
#define LISTA_ID_FAT 32 
#define CMDS 33 
#define CMDS_FAT 34 
#define CMD 35 
#define CMD_ATRIB 36 
#define ARIT3 37 
#define ARIT3_ 38 
#define ARIT2 39 
#define ARIT2_ 40 
#define ARIT1 41 
#define ARIT1_ 42 
#define ARIT_FATOR 43 
#define CMD_COND 44 
#define COND 45 
#define CMD_BLOCO 46 
#define SENAO_FAT 47
#define CMD_REP 48
#define EPSILON 49
#define FINAL_TOKEN 50

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