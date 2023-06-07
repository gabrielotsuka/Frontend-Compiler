#include<stack>
#include<vector>
#include<map>
#include<iostream>
#include"lang.hpp"

using namespace std;

vector<vector<int>> productions = {
    {FUNCTION, ID, ABRE_PARENTESES, FECHA_PARENTESES, BLOCO}, // 0
    {ABRE_CHAVES, BLOCO_AUX, FECHA_CHAVES}, // 1
    {DECL_VARS, CMDS}, // 2
    {CMDS}, // 3
    {DECL_VAR, DECL_VARS_FAT}, // 4
    {DECL_VARS}, // 5
    {EPSILON}, // 6
    {TIPO, DOIS_PONTOS, LISTA_ID, PONTO_VIRGULA}, // 7
    {ID, LISTA_ID_FAT}, // 8 
    {VIRGULA, LISTA_ID}, // 9
    {EPSILON}, // 10
    {CMD, CMDS_FAT}, //11
    {CMDS}, // 12
    {EPSILON}, // 13
    {CMD_ATRIB}, // 14
    {CMD_COND},// 15
    {CMD_REP}, // 16
    {ID, IGUAL, ARIT3, PONTO_VIRGULA}, // 17
    {ARIT2, ARIT3_}, // 18
    {OP_ARIT_PREC3, ARIT2, ARIT3_}, // 19
    {EPSILON}, //20
    {ARIT1, ARIT2_}, // 21
    {OP_ARIT_PREC2, ARIT1, ARIT2_}, //22
    {EPSILON}, //23 
    {ARIT_FATOR, ARIT1_}, //24
    {OP_ARIT_PREC1, ARIT_FATOR, ARIT1_}, // 25
    {EPSILON}, // 26
    {ID}, //27
    {CONST_INT}, // 28
    {CONST_CHAR}, // 29
    {CONST_FLOAT}, //30
    {ABRE_PARENTESES, ARIT3, FECHA_PARENTESES}, //31
    {SE, ABRE_PARENTESES, COND, FECHA_PARENTESES, ENTAO, CMD_BLOCO, SENAO_FAT}, // 32
    {ARIT3, RELOP, ARIT3}, //33 
    {CMD}, //34
    {BLOCO}, //35
    {SENAO, CMD_BLOCO}, //36
    {EPSILON}, //37
    {ENQUANTO, ABRE_PARENTESES, COND, FECHA_PARENTESES, FACA, CMD_BLOCO}, //38
    {REPITA, CMD_BLOCO, ATE, ABRE_PARENTESES, COND, FECHA_PARENTESES}, // 39
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
    predictiveTable[SENAO_FAT][ID] = 37;
    predictiveTable[SENAO_FAT][SE] = 37;
    predictiveTable[SENAO_FAT][ENQUANTO] = 37;
    predictiveTable[SENAO_FAT][REPITA] = 37;
    predictiveTable[SENAO_FAT][SENAO] = 36;
    predictiveTable[SENAO_FAT][ATE] = 37;
    predictiveTable[SENAO_FAT][FECHA_CHAVES] = 37;
    predictiveTable[CMD_REP][ENQUANTO] = 38;
    predictiveTable[CMD_REP][REPITA] = 39;
}

vector<string> symbolNames = {
    "FUNCTION",	
    "ABRE_CHAVES",	
    "TIPO",	
    "ID",	
    "SE",	
    "ENQUANTO",	
    "REPITA",	
    "VIRGULA",	
    "CONST_INT",	
    "CONST_CHAR",	
    "CONST_FLOAT",
    "ABRE_PARENTESES",
    "OP_ARIT_PREC3",
    "OP_ARIT_PREC2",
    "OP_ARIT_PREC1",
    "SENAO",
    "ATE",
    "FECHA_CHAVES",
    "PONTO_VIRGULA",
    "FECHA_PARENTESES",
    "RELOP",
    "FACA",
    "ENTAO",
    "DOIS_PONTOS",
    "IGUAL",
    "INI", 
    "BLOCO", 
    "BLOCO_AUX", 
    "DECL_VARS", 
    "DECL_VARS_FAT", 
    "DECL_VAR", 
    "LISTA_ID", 
    "LISTA_ID_FAT", 
    "CMDS", 
    "CMDS_FAT", 
    "CMD", 
    "CMD_ATRIB", 
    "ARIT3", 
    "ARIT3_", 
    "ARIT2", 
    "ARIT2_", 
    "ARIT1", 
    "ARIT1_", 
    "ARIT_FATOR", 
    "CMD_COND", 
    "COND", 
    "CMD_BLOCO", 
    "SENAO_FAT",
    "CMD_REP",
    "EPSILON",
    "NOTOKEN",
    "ERROR"
};


void throwError(Token token, int expected) {
    cout << "Erro sintático na linha " << token.line << " e coluna " << token.column << endl;
    cout << "Esperado: " << symbolNames[expected] << endl;
    cout << "Encontrado: " << symbolNames[token.type] << endl;
}

void printPilha(stack<int> s) {
    while(!s.empty()) {
        int top = s.top();
        cout << symbolNames[top] << " ";
        s.pop();
    }
    cout << endl;
}


int main() {
    cout << "====================== inicio analise sintatica ======================\n";
    populatePredictiveTable();
    initialize_lexic();
    stack<int> stack;
    stack.push(INI);
    Token currentToken = getToken();

    while(!stack.empty()) {
        
        int currentSymbol = stack.top();
        cout<< "\ntoken lido: "<< symbolNames[currentToken.type] << endl;
        cout << "pilha: "; printPilha(stack);

        if(currentSymbol < 25) {
            if (currentSymbol != currentToken.type) {
                throwError(currentToken, currentSymbol);
                finalize_lexic();
                return 1;
            }
            cout << "MATCH! " << symbolNames[currentSymbol] << " == " << symbolNames[currentToken.type] << endl;
            stack.pop();
            currentToken = getToken();
        } else {
            int productionIdx = -1;
            try {
                productionIdx = predictiveTable.at(currentSymbol).at(currentToken.type);    
            } catch(const std::out_of_range& e) {
                while(stack.top() > 24) {
                    stack.pop();
                }
                throwError(currentToken, stack.top());
                finalize_lexic();
                return 1;
            }
            
            // 
            // Trata produção // Constrói subárvore X ou executa ações semânticas
            stack.pop();
            vector<int> productionBody = productions[productionIdx];
            if (productionBody[0] != EPSILON) {
                cout << "TabelaPreditiva[" << symbolNames[currentSymbol] << "][" << symbolNames[currentToken.type] << "] = { ";
                for (int i = productionBody.size()-1; i>=0; i--) {
                    cout << symbolNames[productionBody[i]] << " ";
                    stack.push(productionBody[i]);
                }    
                cout << "}\n";
            }
        }
    }
    
    if (currentToken.type != NOTOKEN) {
        throwError(currentToken, -1);
        finalize_lexic();
        return 1;
    } else {
        cout << "Codigo fonte sintaticamente correto!" << endl;
    }

    finalize_lexic();

    return 0;
}