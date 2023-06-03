#include<stack>
#include<vector>

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

typedef struct {
    int tipo;
    int valor;
} Token;

typedef struct {
    int cabeça;
    vector<int> Corpo; 
} Producao;

vector<Producao> producoes = {
    {0, {FUNCTION, ID, ABRE_PARENTESES, FECHA_PARENTESES, BLOCO}},
    {1, {ABRE_CHAVES, BLOCO_AUX, FECHA_CHAVES}},
    {2, {DECL_VARS, CMD}},
    {3, {CMDS}},
    {4, {DECL_VAR, DECL_VARS_FAT}},
    {5, {DECL_VARS}},
    {6, {EPSILON}},
    {7, {TIPO, DOIS_PONTOS, LISTA_ID, PONTO_VIRGULA}},
    {8, {ID, LISTA_ID_FAT}},
    {9, {VIRGULA, LISTA_ID}},
    {10, {EPSILON}},
    {11, {CMD, CMDS_FAT}},
    {12, {CMDS}},
    {13, {EPSILON}},
    {14, {CMD_ATRIB}},
    {15, {CMD_COND}},
    {16, {CMD_REP}},
    {17, {ID, IGUAL, ARIT3, PONTO_VIRGULA}},
    {18, {ARIT2, ARIT3_}},
    {19, {OP_ARIT_PREC3, ARIT2, ARIT3_}},
    {20, {EPSILON}},
    {21, {ARIT1, ARIT2_}},
    {22, {OP_ARIT_PREC2, ARIT1, ARIT2_}},
    {23, {EPSILON}},
    {24, {ARIT_FATOR, ARIT1_}},
    {25, {OP_ARIT_PREC1, ARIT_FATOR, ARIT1_}},
    {26, {EPSILON}},
    {27, {ID}},
    {28, {CONST_INT}},
    {29, {CONST_CHAR}},
    {30, {CONST_FLOAT}},
    {31, {ABRE_PARENTESES, ARIT3, FECHA_PARENTESES}},
    {32, {SE, ABRE_PARENTESES, COND, FECHA_PARENTESES, ENTAO, CMD_BLOCO, SENAO_FAT}},
    {33, {ARIT3, RELOP, ARIT3}},
    {34, {CMD}},
    {35, {BLOCO}},
    {36, {SENAO, CMD_BLOCO}},
    {37, {EPSILON}},
    {38, {ENQUANTO, ABRE_PARENTESES, COND, FECHA_PARENTESES, FACA, CMD_BLOCO}},
    {39, {REPITA, CMD_BLOCO, ATE, ABRE_PARENTESES, COND, FECHA_PARENTESES}},
};

int predictiveTable[24][23];
int** buildPredictiveTable() {
    for (int i = 0; i < 24; i++) {
        for(int j = 0; j < 23; j++) {
            predictiveTable[i][j] = -1;
        }
    }
    int offset = 25;
    predictiveTable[INI-offset][FUNCTION] = 1;
    predictiveTable[BLOCO-offset][ABRE_CHAVES] = 2;
    predictiveTable[BLOCO_AUX-offset][TIPO] = 3;
    predictiveTable[BLOCO_AUX-offset][ID] = 4;
    predictiveTable[BLOCO_AUX-offset][SE] = 4;
    predictiveTable[BLOCO_AUX-offset][ENQUANTO] = 4;
    predictiveTable[BLOCO_AUX-offset][REPITA] = 4;
    predictiveTable[DECL_VARS-offset][TIPO] = 5;
    predictiveTable[DECL_VARS_FAT-offset][TIPO] = 6;
    predictiveTable[DECL_VARS_FAT-offset][ID] = 7;
    predictiveTable[DECL_VARS_FAT-offset][SE] = 7;
    predictiveTable[DECL_VARS_FAT-offset][ENQUANTO] = 7;
    predictiveTable[DECL_VARS_FAT-offset][REPITA] = 7;
    predictiveTable[DECL_VAR-offset][TIPO] = 8;
    predictiveTable[LISTA_ID-offset][ID] = 9;
    predictiveTable[LISTA_ID_FAT-offset][VIRGULA] = 10;
    predictiveTable[LISTA_ID_FAT-offset][PONTO_VIRGULA] = 11;
    predictiveTable[CMDS-offset][ID] = 12;
    predictiveTable[CMDS-offset][SE] = 12;
    predictiveTable[CMDS-offset][ENQUANTO] = 12;
    predictiveTable[CMDS-offset][REPITA] = 12;
    predictiveTable[CMDS_FAT-offset][ID] = 13;
    predictiveTable[CMDS_FAT-offset][SE] = 13;
    predictiveTable[CMDS_FAT-offset][ENQUANTO] = 13;
    predictiveTable[CMDS_FAT-offset][REPITA] = 13;
    predictiveTable[CMDS_FAT-offset][FECHA_CHAVES] = 14;
    predictiveTable[CMD-offset][ID] = 15;
    predictiveTable[CMD-offset][SE] = 16;
    predictiveTable[CMD-offset][ENQUANTO] = 17;
    predictiveTable[CMD-offset][REPITA] = 17;
    predictiveTable[CMD_ATRIB-offset][ID] = 18;
    predictiveTable[ARIT3-offset][ID] = 19;
    predictiveTable[ARIT3-offset][CONST_INT] = 19;
    predictiveTable[ARIT3-offset][CONST_CHAR] = 19;
    predictiveTable[ARIT3-offset][CONST_FLOAT] = 19;
    predictiveTable[ARIT3-offset][ABRE_PARENTESES] = 19;
    predictiveTable[ARIT3_-offset][OP_ARIT_PREC3] = 20;
    predictiveTable[ARIT3_-offset][RELOP] = 21;
    predictiveTable[ARIT3_-offset][PONTO_VIRGULA] = 21;
    predictiveTable[ARIT3_-offset][FECHA_PARENTESES] = 21;
    predictiveTable[ARIT2-offset][ID] = 22;
    predictiveTable[ARIT2-offset][CONST_INT] = 22;
    predictiveTable[ARIT2-offset][CONST_CHAR] = 22;
    predictiveTable[ARIT2-offset][CONST_FLOAT] = 22;
    predictiveTable[ARIT2-offset][ABRE_PARENTESES] = 22;
    predictiveTable[ARIT2_-offset][OP_ARIT_PREC3] = 24;
    predictiveTable[ARIT2_-offset][OP_ARIT_PREC2] = 23;
    predictiveTable[ARIT2_-offset][RELOP] = 24;
    predictiveTable[ARIT2_-offset][PONTO_VIRGULA] = 24;
    predictiveTable[ARIT2_-offset][FECHA_PARENTESES] = 24;
    predictiveTable[ARIT1-offset][ID] = 25;
    predictiveTable[ARIT1-offset][CONST_INT] = 25;
    predictiveTable[ARIT1-offset][CONST_CHAR] = 25;
    predictiveTable[ARIT1-offset][CONST_FLOAT] = 25;
    predictiveTable[ARIT1-offset][ABRE_PARENTESES] = 25;
    predictiveTable[ARIT1_-offset][OP_ARIT_PREC3] = 27;
    predictiveTable[ARIT1_-offset][OP_ARIT_PREC2] = 27;
    predictiveTable[ARIT1_-offset][OP_ARIT_PREC1] = 26;
    predictiveTable[ARIT1_-offset][RELOP] = 27;
    predictiveTable[ARIT1_-offset][PONTO_VIRGULA] = 27;
    predictiveTable[ARIT1_-offset][FECHA_PARENTESES] = 27;
    predictiveTable[ARIT_FATOR-offset][ID] = 28;
    predictiveTable[ARIT_FATOR-offset][CONST_INT] = 29;
    predictiveTable[ARIT_FATOR-offset][CONST_CHAR] = 30;
    predictiveTable[ARIT_FATOR-offset][CONST_FLOAT] = 40;
    predictiveTable[ARIT_FATOR-offset][ABRE_PARENTESES] = 31;
    predictiveTable[CMD_COND-offset][SE] = 32;
    predictiveTable[COND-offset][ID] = 33;
    predictiveTable[COND-offset][CONST_INT] = 33;
    predictiveTable[COND-offset][CONST_CHAR] = 33;
    predictiveTable[COND-offset][CONST_FLOAT] = 33;
    predictiveTable[COND-offset][ABRE_PARENTESES] = 33;
    predictiveTable[CMD_BLOCO-offset][ABRE_CHAVES] = 35;
    predictiveTable[CMD_BLOCO-offset][ID] = 34;
    predictiveTable[CMD_BLOCO-offset][SE] = 34;
    predictiveTable[CMD_BLOCO-offset][ENQUANTO] = 34;
    predictiveTable[CMD_BLOCO-offset][REPITA] = 34;
    predictiveTable[SENAO_FAT-offset][ABRE_CHAVES] = 37;
    predictiveTable[SENAO_FAT-offset][ID] = 37;
    predictiveTable[SENAO_FAT-offset][SE] = 37;
    predictiveTable[SENAO_FAT-offset][ENQUANTO] = 37;
    predictiveTable[SENAO_FAT-offset][REPITA] = 37;
    predictiveTable[SENAO_FAT-offset][SENAO] = 36;
    predictiveTable[SENAO_FAT-offset][ATE] = 37;
    predictiveTable[CMD_REP-offset][ENQUANTO] = 38;
    predictiveTable[CMD_REP-offset][REPITA] = 39;
}


int main() {
    stack<int> stack;
    stack.push(INI);
    Token proxToken;//lex();

    while(!stack.empty()) {
        int expectedSymbol = stack.top();
        if(expectedSymbol < 23) {
            if (expectedSymbol == proxToken.tipo) {
                stack.pop();
                proxToken;//lex();
            } else {
                // throw error
            }
        } else {
            // DERIVA
        }
    }
    return 0;
}