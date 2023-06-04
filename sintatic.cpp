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

void throwError(Token token) {
    cout << "Erro sintático na linha " << token.line << " e coluna " << token.column << endl;
}

int main() {
    populatePredictiveTable();
    initialize_lexic();
    stack<int> stack;
    stack.push(INI);
    Token currentToken = getToken();

    while(!stack.empty()) {
        int currentSymbol = stack.top();
        if(currentSymbol < 23) {
            if (currentSymbol != currentToken.type) {
                throwError(currentToken);
                finalize_lexic();
                return 1;
            }
            stack.pop();
            currentToken = getToken();
        } else {
            int productionIdx = predictiveTable[currentSymbol][currentToken.type];
            if (productionIdx == -1) {
                throwError(currentToken);
                finalize_lexic();
                return 1;
            }
            // Trata produção // Constrói subárvore X ou executa ações semânticas
            stack.pop();
            vector<int> productionBody = productions[productionIdx];
            for (int i = productionBody.size()-1; i>=0; i--) {
                stack.push(productionBody[i]);
            }
        }
    }
    
    if (currentToken.type != FINAL_TOKEN) {
        throwError(currentToken);
        finalize_lexic();
        return 1;
    } else {

    }

    finalize_lexic();

    return 0;
}