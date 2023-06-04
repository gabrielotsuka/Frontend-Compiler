#include<stack>
#include<vector>
#include<map>
#include<iostream>
#include"lang.hpp"

using namespace std;

vector<vector<int>> productions = {
    {FUNCTION, ID, ABRE_PARENTESES, FECHA_PARENTESES, BLOCO},
    {ABRE_CHAVES, BLOCO_AUX, FECHA_CHAVES},
    {DECL_VARS, CMD},
    {CMDS},
    {DECL_VAR, DECL_VARS_FAT},
    {DECL_VARS},
    {EPSILON},
    {TIPO, DOIS_PONTOS, LISTA_ID, PONTO_VIRGULA},
    {ID, LISTA_ID_FAT},
    {VIRGULA, LISTA_ID},
    {EPSILON},
    {CMD, CMDS_FAT},
    {CMDS},
    {EPSILON},
    {CMD_ATRIB},
    {CMD_COND},
    {CMD_REP},
    {ID, IGUAL, ARIT3, PONTO_VIRGULA},
    {ARIT2, ARIT3_},
    {OP_ARIT_PREC3, ARIT2, ARIT3_},
    {EPSILON},
    {ARIT1, ARIT2_},
    {OP_ARIT_PREC2, ARIT1, ARIT2_},
    {EPSILON},
    {ARIT_FATOR, ARIT1_},
    {OP_ARIT_PREC1, ARIT_FATOR, ARIT1_},
    {EPSILON},
    {ID},
    {CONST_INT},
    {CONST_CHAR},
    {CONST_FLOAT},
    {ABRE_PARENTESES, ARIT3, FECHA_PARENTESES},
    {SE, ABRE_PARENTESES, COND, FECHA_PARENTESES, ENTAO, CMD_BLOCO, SENAO_FAT},
    {ARIT3, RELOP, ARIT3},
    {CMD},
    {BLOCO},
    {SENAO, CMD_BLOCO},
    {EPSILON},
    {ENQUANTO, ABRE_PARENTESES, COND, FECHA_PARENTESES, FACA, CMD_BLOCO},
    {REPITA, CMD_BLOCO, ATE, ABRE_PARENTESES, COND, FECHA_PARENTESES},
};

map<int, map<int, int>> predictiveTable;
void populatePredictiveTable() {
    predictiveTable[INI][FUNCTION] = 0;
    predictiveTable[BLOCO][ABRE_CHAVES] = 1;
    predictiveTable[BLOCO_AUX][TIPO] = 2;
    predictiveTable[BLOCO_AUX][ID] = 3;
    predictiveTable[BLOCO_AUX][SE] = 3;
    predictiveTable[BLOCO_AUX][ENQUANTO] = 3;
    predictiveTable[BLOCO_AUX][REPITA] = 3;
    predictiveTable[DECL_VARS][TIPO] = 4;
    predictiveTable[DECL_VARS_FAT][TIPO] = 5;
    predictiveTable[DECL_VARS_FAT][ID] = 6;
    predictiveTable[DECL_VARS_FAT][SE] = 6;
    predictiveTable[DECL_VARS_FAT][ENQUANTO] = 6;
    predictiveTable[DECL_VARS_FAT][REPITA] = 6;
    predictiveTable[DECL_VAR][TIPO] = 7;
    predictiveTable[LISTA_ID][ID] = 8;
    predictiveTable[LISTA_ID_FAT][VIRGULA] = 9;
    predictiveTable[LISTA_ID_FAT][PONTO_VIRGULA] = 10;
    predictiveTable[CMDS][ID] = 11;
    predictiveTable[CMDS][SE] = 11;
    predictiveTable[CMDS][ENQUANTO] = 11;
    predictiveTable[CMDS][REPITA] = 11;
    predictiveTable[CMDS_FAT][ID] = 12;
    predictiveTable[CMDS_FAT][SE] = 12;
    predictiveTable[CMDS_FAT][ENQUANTO] = 12;
    predictiveTable[CMDS_FAT][REPITA] = 12;
    predictiveTable[CMDS_FAT][FECHA_CHAVES] = 13;
    predictiveTable[CMD][ID] = 14;
    predictiveTable[CMD][SE] = 15;
    predictiveTable[CMD][ENQUANTO] = 16;
    predictiveTable[CMD][REPITA] = 16;
    predictiveTable[CMD_ATRIB][ID] = 17;
    predictiveTable[ARIT3][ID] = 18;
    predictiveTable[ARIT3][CONST_INT] = 18;
    predictiveTable[ARIT3][CONST_CHAR] = 18;
    predictiveTable[ARIT3][CONST_FLOAT] = 18;
    predictiveTable[ARIT3][ABRE_PARENTESES] = 18;
    predictiveTable[ARIT3_][OP_ARIT_PREC3] = 19;
    predictiveTable[ARIT3_][RELOP] = 20;
    predictiveTable[ARIT3_][PONTO_VIRGULA] = 20;
    predictiveTable[ARIT3_][FECHA_PARENTESES] = 20;
    predictiveTable[ARIT2][ID] = 21;
    predictiveTable[ARIT2][CONST_INT] = 21;
    predictiveTable[ARIT2][CONST_CHAR] = 21;
    predictiveTable[ARIT2][CONST_FLOAT] = 21;
    predictiveTable[ARIT2][ABRE_PARENTESES] = 21;
    predictiveTable[ARIT2_][OP_ARIT_PREC3] = 23;
    predictiveTable[ARIT2_][OP_ARIT_PREC2] = 22;
    predictiveTable[ARIT2_][RELOP] = 23;
    predictiveTable[ARIT2_][PONTO_VIRGULA] = 23;
    predictiveTable[ARIT2_][FECHA_PARENTESES] = 23;
    predictiveTable[ARIT1][ID] = 24;
    predictiveTable[ARIT1][CONST_INT] = 24;
    predictiveTable[ARIT1][CONST_CHAR] = 24;
    predictiveTable[ARIT1][CONST_FLOAT] = 24;
    predictiveTable[ARIT1][ABRE_PARENTESES] = 24;
    predictiveTable[ARIT1_][OP_ARIT_PREC3] = 26;
    predictiveTable[ARIT1_][OP_ARIT_PREC2] = 26;
    predictiveTable[ARIT1_][OP_ARIT_PREC1] = 25;
    predictiveTable[ARIT1_][RELOP] = 26;
    predictiveTable[ARIT1_][PONTO_VIRGULA] = 26;
    predictiveTable[ARIT1_][FECHA_PARENTESES] = 26;
    predictiveTable[ARIT_FATOR][ID] = 27;
    predictiveTable[ARIT_FATOR][CONST_INT] = 28;
    predictiveTable[ARIT_FATOR][CONST_CHAR] = 29;
    predictiveTable[ARIT_FATOR][CONST_FLOAT] = 30;
    predictiveTable[ARIT_FATOR][ABRE_PARENTESES] = 31;
    predictiveTable[CMD_COND][SE] = 32;
    predictiveTable[COND][ID] = 33;
    predictiveTable[COND][CONST_INT] = 33;
    predictiveTable[COND][CONST_CHAR] = 33;
    predictiveTable[COND][CONST_FLOAT] = 33;
    predictiveTable[COND][ABRE_PARENTESES] = 33;
    predictiveTable[CMD_BLOCO][ABRE_CHAVES] = 35;
    predictiveTable[CMD_BLOCO][ID] = 34;
    predictiveTable[CMD_BLOCO][SE] = 34;
    predictiveTable[CMD_BLOCO][ENQUANTO] = 34;
    predictiveTable[CMD_BLOCO][REPITA] = 34;
    predictiveTable[SENAO_FAT][ABRE_CHAVES] = 37;
    predictiveTable[SENAO_FAT][ID] = 37;
    predictiveTable[SENAO_FAT][SE] = 37;
    predictiveTable[SENAO_FAT][ENQUANTO] = 37;
    predictiveTable[SENAO_FAT][REPITA] = 37;
    predictiveTable[SENAO_FAT][SENAO] = 36;
    predictiveTable[SENAO_FAT][ATE] = 37;
    predictiveTable[CMD_REP][ENQUANTO] = 38;
    predictiveTable[CMD_REP][REPITA] = 39;
}

void throwError(Token token, int expected) {
    cout << "Erro sintático na linha " << token.line << " e coluna " << token.column << endl;
    cout << "Esperado: " << expected << endl;
    cout << "Encontrado: " << token.type << endl;
}

int main() {
    populatePredictiveTable();
    initialize_lexic();
    stack<int> stack;
    stack.push(INI);
    Token currentToken = getToken();

    while(!stack.empty()) {
        int currentSymbol = stack.top();
        cout<< "token lido"<< currentToken.type<<"\n"<<"topo da pilha" << currentSymbol<<endl << endl;
        if(currentSymbol < 25) {
            if (currentSymbol != currentToken.type) {
                throwError(currentToken, currentSymbol);
                finalize_lexic();
                return 1;
            }
            stack.pop();
            currentToken = getToken();
        } else {
            int productionIdx = predictiveTable[currentSymbol][currentToken.type];
            cout << productionIdx << endl;
            if (productionIdx == -1) {
                throwError(currentToken, currentSymbol);
                finalize_lexic();
                return 1;
            }
            // Trata produção // Constrói subárvore X ou executa ações semânticas
            stack.pop();
            vector<int> productionBody = productions[productionIdx];
            if (productionBody[0] != EPSILON) {
                for (int i = productionBody.size()-1; i>=0; i--) {
                    stack.push(productionBody[i]);
                }    
            }
        }
    }
    
    if (currentToken.type != NOTOKEN) {
        throwError(currentToken, -1);
        finalize_lexic();
        return 1;
    } else {
        cout << "aceita" << endl;
    }

    finalize_lexic();

    return 0;
}