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

Token getToken() {
    int state = 0;
    int cnt = 14;
    while (cnt--) {
        getNextChar();
        char c = curChar.value;
        cout << c << ' ' << state << endl;
        switch (state)
        {
            case 0:
                if(c == 'f') {
                    state = 1;
                }
                else if(c == '(') {
                    state = 2;
                    return Token(ABRE_PARENTESES, emptyAttribute, curChar.line, curChar.column);
                }
                else if(c == ')') {
                    state = 3;
                    return Token(FECHA_PARENTESES, emptyAttribute, curChar.line, curChar.column);
                }
                else if(c == '{') {
                    state = 4;
                }
                else if(c == '}') {
                    state = 5;
                }
                else if(c == ';') {
                    state = 6;
                }
                else if(c == ',') {
                    state = 7;
                }
                else if(c == '^') {
                    state = 8;
                }
                else if(c == '/') {
                    state = 9;
                }
                else if(c == '*') {
                    state = 10;
                }
                else if(c == '+') {
                    state = 11;
                }
                else if(c == '-') {
                    state = 12;
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
                    //erro
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
                    //erro
                }
            case 3:
                

            default:
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
    int cnt = 4;
    while (cnt--) {
        Token tok = getToken();
        cout << tok.type << ' ' << tok.value << ' ' << tok.line << ' ' << tok.column << endl;
    }
    finalize_lexic();


}