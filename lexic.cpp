#include <iostream>
#include "lang.hpp"
using namespace std;

string emptyAttribute = "N/A";

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

void getNextChar() {
    while (feof(file) == 0 && curPos >= strlen(row)) {
        char* result = fgets(row, 250, file);
        curPos = 0;
        lineCounter++;
        if(!result) {
            printf("Failed to read the next line\n");
            exit(1);
        }
    }
    if(strlen(row) <= curPos) {
        printf("The file has ended\n");
        exit(0);
    }
    lastChar = curChar;
    if(curPos >= 0) {
        curChar.value = row[curPos];
        curChar.line = lineCounter;
        curChar.column = curPos+1;
    }
    curPos++;
}

void treatLookAhead() {
    curChar = lastChar;
    curPos--;
}

Token getToken() {
    int state = 0;
    int cnt = 14;
    bool shouldRead = true;
    while (cnt--) {
        if(shouldRead) getNextChar();
        char c = curChar.value;
        cout << c << ' ' << state << endl;
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
                    //error
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
                    //error
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
                    // error
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
                    // error
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
                    // error
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
                    // error
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
                    // error
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
                    // error
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
                    // error
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
                    // error
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
                    // error
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
                Token tok = Token(OP_ARIT_PREC2, "/", curChar.line, curChar.column);
                treatLookAhead();
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
                    Token tok = Token(SE, emptyAttribute, curChar.line, curChar.column);
                    treatLookAhead();
                    return tok;
                }
            case 33:
                
            default:
                // error
                break;
        }
    }
    return Token();
}

void finalize_lexic() {
    fclose(file);
}