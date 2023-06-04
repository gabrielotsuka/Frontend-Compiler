#include <iostream>
#include "lang.hpp"
using namespace std;

typedef struct c{
    char value;
    int line, column;
} Char;

FILE *file;
char row[250];
int curPos = 0, lineCounter = 0;
Char lastChar;
Char curChar;

void initialize_lexic() {
    file = fopen("program.lang", "rt");
    if (file == NULL) {
        printf("Failed opening the desired file\n");
        return;
    }
}

bool getNextChar() {
    while (feof(file) == 0 && curPos >= strlen(row)) {
        char* result = fgets(row, 250, file);
        curPos = 0;
        lineCounter++;
        // cout << row << endl;
        if(!result) {
            return false;
        }
    }
    if(strlen(row) <= curPos) {
        return false;
    }
    lastChar = curChar;
    if(curPos >= 0) {
        curChar.value = row[curPos];
        curChar.line = lineCounter;
        curChar.column = curPos+1;
    }
    curPos++;
    return true;
}

void treatLookAhead() {
    curChar = lastChar;
    curPos--;
}

Token getToken() {
    int state = 0;
    bool shouldRead = true;
    string value;
    while (1) {
        if(shouldRead){
            if(!getNextChar()) {
                return Token(NOTOKEN, "N/A", -1, -1);
            }
            value.push_back(curChar.value);
        }
        char c = curChar.value;
        shouldRead = true;
        switch (state)
        {
            case 0:
                if(c == 'f') {
                    state = 1;
                }
                else if(c == '(') {
                    state = 2;
                    shouldRead = false;
                }
                else if(c == ')') {
                    state = 3;
                    shouldRead = false;
                }
                else if(c == '{') {
                    state = 4;
                    shouldRead = false;
                }
                else if(c == '}') {
                    state = 5;
                    shouldRead = false;
                }
                else if(c == ';') {
                    state = 6;
                    shouldRead = false;
                }
                else if(c == ',') {
                    state = 7;
                    shouldRead = false;
                }
                else if(c == '^') {
                    state = 8;
                    shouldRead = false;
                }
                else if(c == '/') {
                    state = 9;
                }
                else if(c == '*') {
                    state = 10;
                    shouldRead = false;
                }
                else if(c == '+') {
                    state = 11;
                    shouldRead = false;
                }
                else if(c == '-') {
                    state = 12;
                    shouldRead = false;
                }
                else if(c == 's') {
                    state = 13;
                }
                else if(c == '<') {
                    state = 14;
                }
                else if(c == '=') {
                    state = 15;
                }
                else if(c == '>') {
                    state = 16;
                }
                else if(c == 'e') {
                    state = 17;
                }
                else if(c == 'r') {
                    state = 18;
                }
                else if(c == 'a') {
                    state = 19;
                }
                else if(c >= '0' && c <= '9') {
                    state = 20;
                }
                else if(c == ' ' || c == '\t' || c == '\n') {
                    state = 21;
                }
                else if(c == ':') {
                    state = 22;
                    shouldRead = false;
                }
                else if(c == '\'') {
                    state = 23;
                }
                else if(c == 'i') {
                    state = 24;
                }
                else if(c == 'c') {
                    state = 25;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 1:
                if(c == 'u') {
                    state = 27;
                }
                else if(c == 'a') {
                    state = 28;
                }
                else if(c == 'l') {
                    state = 29;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 2: 
                return Token(ABRE_PARENTESES, emptyAttribute, curChar.line, curChar.column);
            case 3: 
                return Token(FECHA_PARENTESES, emptyAttribute, curChar.line, curChar.column);
            case 4: 
                return Token(ABRE_CHAVES, emptyAttribute, curChar.line, curChar.column);
            case 5: 
                return Token(FECHA_CHAVES, emptyAttribute, curChar.line, curChar.column);
            case 6: 
                return Token(PONTO_VIRGULA, emptyAttribute, curChar.line, curChar.column);
            case 7: 
                return Token(VIRGULA, emptyAttribute, curChar.line, curChar.column);
            case 8: 
                return Token(OP_ARIT_PREC1, emptyAttribute, curChar.line, curChar.column);
            case 9:
                if(c == '*') {
                    state = 30;
                }
                else {
                    state = 31;
                    shouldRead = false;
                }
                break;
            case 10: 
                return Token(OP_ARIT_PREC2, "*", curChar.line, curChar.column);
            case 11: 
                return Token(OP_ARIT_PREC3, "+", curChar.line, curChar.column);
            case 12: 
                return Token(OP_ARIT_PREC3, "-", curChar.line, curChar.column);
            case 13:
                if(c == 'e') {
                    state = 32;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 14:
                if(c == '=') {
                    state = 33;
                    shouldRead = false;
                }
                else if(c == '>') {
                    state = 34;
                    shouldRead = false;
                }
                else {
                    state = 35;
                    shouldRead = false;
                }
                break;
            case 15:
                if(c == '=') {
                    state = 36;
                    shouldRead = false;
                }
                else {
                    state = 37;
                    shouldRead = false;
                }
                break;
            case 16:
                if(c == '=') {
                    state = 38;
                    shouldRead = false;
                }
                else {
                    state = 39;
                    shouldRead = false;
                }
                break;
            case 17:
                if(c == 'n') {
                    state = 40;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 18:
                if(c == 'e') {
                    state = 41;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 19:
                if(c == 't') {
                    state = 42;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 20:
                if(c >= '0' && c <= '9') {
                    state = 20;
                }
                else if(c == '.') {
                    state = 43;
                }
                else if(c == 'E') {
                    state = 44;
                }
                else {
                    state = 45;
                    shouldRead = false;
                }
                break;
            case 21:
                if(c == ' ' || c == '\t' || c == '\n') {
                    state = 21;
                }
                else {
                    state = 46;
                    shouldRead = false;
                }
                break;
            case 22:
                return Token(DOIS_PONTOS, emptyAttribute, curChar.line, curChar.column);
            case 23:
                if(c == '\'') {
                    state = 88;
                    shouldRead = false;
                }
                else {
                    state = 23;
                }
                break;
            case 24:
                if(c == 'n') {
                    state = 47;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 25:
                if(c == 'h') {
                    state = 48;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 26:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                } else {
                    state = 49;
                    shouldRead = false;
                }
                break;
            case 27:
                if(c == 'n') {
                    state = 50;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 28:
                if(c == 'c') {
                    state = 51;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 29:
                if(c == 'o') {
                    state = 52;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 30:
                if(c == '*') {
                    state = 53;
                } else {
                    state = 30;
                }
                break;
            case 31:
            {
                treatLookAhead();
                Token tok = Token(OP_ARIT_PREC2, "/", curChar.line, curChar.column);
                return tok;
            }
            case 32:
                if(c == 'n') {
                    state = 54;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(SE, emptyAttribute, curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 33:
                return Token(RELOP, "<=", curChar.line, curChar.column);
            case 34:
                return Token(RELOP, "<>", curChar.line, curChar.column);
            case 35:
            {
                treatLookAhead();
                Token tok = Token(RELOP, "<", curChar.line, curChar.column);
                return tok;
            }
            case 36:
                return Token(RELOP, "==", curChar.line, curChar.column);
            case 37:
            {
                treatLookAhead();
                Token tok = Token(IGUAL, emptyAttribute, curChar.line, curChar.column);
                return tok;
            }
            case 38:
                return Token(RELOP, ">=", curChar.line, curChar.column);
            case 39:
            {
                treatLookAhead();
                Token tok = Token(RELOP, ">", curChar.line, curChar.column);
                return tok;
            }
            case 40:
                if(c == 'q') {
                    state = 55;
                }
                else if(c == 't') {
                    state = 56;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 41:
                if(c == 'p') {
                    state = 57;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 42:
                if(c == 'e') {
                    state = 58;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 43:
                if(c >= '0' && c <= '9') {
                    state = 59;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 44:
                if(c == '+' || c == '-') {
                    state = 60;
                }
                else if(c >= '0' && c <= '9') {
                    state = 61;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 45:
            {
                value.pop_back();
                treatLookAhead();
                Token tok = Token(CONST_INT, value, curChar.line, curChar.column);
                return tok;
            }
            case 46:
            {
                // WS is not returned
                treatLookAhead();
                value.clear();
                state = 0;
                break;
            }
            case 47:
                if(c == 't') {
                    state = 62;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 48:
                if(c == 'a') {
                    state = 63;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 49:
            {
                string symbolTablePos = "-1"; //Should be changed after we create the symbol table structure
                treatLookAhead();
                Token tok = Token(ID, symbolTablePos, curChar.line, curChar.column);
                return tok;
            }
            case 50:
                if(c == 'c') {
                    state = 64;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 51:
                if(c == 'a') {
                    state = 65;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 52:
                if(c == 'a') {
                    state = 66;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 53:
                if(c == '/') {
                    state = 67;
                    shouldRead = false;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 54:
                if(c == 'a') {
                    state = 68;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);;
                }
                break;
            case 55:
                if(c == 'u') {
                    state = 69;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 56:
                if(c == 'a') {
                    state = 70;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 57:
                if(c == 'i') {
                    state = 71;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);;
                }
                break;
            case 58:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(ATE, emptyAttribute, curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 59:
                if(c == 'E') {
                    state = 44;
                }
                else if(c >= '0' && c <= '9') {
                    state = 59;
                }
                else {
                    state = 72;
                    shouldRead = false;
                }
                break;
            case 60:
                if(c >= '0' && c <= '9') {
                    state = 61;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 61:
                if(c >= '0' && c <= '9') {
                    state = 61;
                }
                else {
                    state = 73;
                    shouldRead = false;
                }
                break;
            case 62:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(TIPO, "int", curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 63:
                if(c == 'r') {
                    state = 74;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 64:
                if(c == 't') {
                    state = 75;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 65:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(FACA, emptyAttribute, curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 66:
                if(c == 't') {
                    state = 76;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 67:
            {
                // texto_comentario is not returned
                value.clear();
                state = 0;
                break;
            }
            case 68:
                if(c == 'o') {
                    state = 77;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 69:
                if(c == 'a') {
                    state = 78;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 70:
                if(c == 'o') {
                    state = 80;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 71:
                if(c == 't') {
                    state = 79;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 72:
            {
                value.pop_back();
                treatLookAhead();
                Token tok = Token(CONST_FLOAT, value, curChar.line, curChar.column);
                return tok;
            }
            case 73:
            {
                value.pop_back();
                treatLookAhead();
                Token tok = Token(CONST_FLOAT, value, curChar.line, curChar.column);
                return tok;
            }
            case 74:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(TIPO, "char", curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 75:
                if(c == 'i') {
                    state = 81;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 76:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(TIPO, "float", curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 77:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(SENAO, emptyAttribute, curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 78:
                if(c == 'n') {
                    state = 82;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 79:
                if(c == 'a') {
                    state = 83;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 80:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(ENTAO, emptyAttribute, curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 81:
                if(c == 'o') {
                    state = 84;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 82:
                if(c == 't') {
                    state = 85;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 83:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(REPITA, emptyAttribute, curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 84:
                if(c == 'n') {
                    state = 86;
                }
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 85:
                if(c == 'o') {
                    state = 87;
                } 
                else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    return Token(ERROR, "N/A", curChar.line, curChar.column);
                }
                break;
            case 86:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(FUNCTION, emptyAttribute, curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 87:
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    state = 26;
                }
                else {
                    treatLookAhead();
                    Token tok = Token(ENQUANTO, emptyAttribute, curChar.line, curChar.column);
                    return tok;
                }
                break;
            case 88:
                return Token(CONST_CHAR, value, curChar.line, curChar.column);
            default:
                return Token(ERROR, "N/A", curChar.line, curChar.column);
                break;
        }
    }
    return Token();
}

void finalize_lexic() {
    fclose(file);
}

int main() {
    initialize_lexic();
    int cnt = 10;
    while (1) {
        Token tok = getToken();
        if(tok.type == NOTOKEN) break;
        cout << tok.type << ' ' << tok.value << ' ' << tok.line << ' ' << tok.column << endl;
    }
    finalize_lexic();
}