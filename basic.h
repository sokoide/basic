#pragma once

#ifdef STM32F072xB
#include "usart.h"
#endif

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_NO (65535)
#define MAX_LINE_LEN (255)
#define MAX_NODES (64)
#define MAX_BASMEM (4096)

extern char lines[MAX_BASMEM];
extern uint16_t szLines;

typedef enum _nodeType {
    ndNotUsed,
    ndNull,
    ndString,
    ndInteger,
    ndIdent,
    ndAdd,
    ndSub,
    ndMul,
    ndDiv,
    ndMod,
} nodeType;

typedef struct _node {
    nodeType type; // if ndNotUsed, not used
    struct _node* lhs;
    struct _node* rhs;
    union {
        char svalue[32];
        int ivalue;
    };
} node;

typedef enum _tokenType {
    tkNull,
    // keyword
    tkGoto,
    tkIf,
    tkPrint,
    tkLp,
    tkRp,
    // operator
    tkAdd,
    tkSub,
    tkMul,
    tkDiv,
    tkAssign,
    tkMod,
    // others
    tkIdent,
    tkString,
    tkNumber,
} tokType;

typedef struct _token {
    tokType type;
    uint16_t lineno;
    uint16_t start; // first character's offset of the line
    uint16_t len;   // token length
} token;

typedef struct _basline {
    uint16_t lineno;
    uint8_t len;
    char line[];
} basline;

void start();
void print(const char*);
void list();
void newList();
void run();
void getLine(char* buf, size_t len);
void skipSpaces(uint16_t lineno, uint16_t* offset);
token getToken(uint16_t lineno, uint16_t* offset, bool peek);
void reset();
void resetNodes();
void resetVars();
void resetLines();
node* newNode(nodeType type, node* lhs, node* rhs);
void freeNode(node* n);
bool consume(tokType type, uint16_t lineno, uint16_t* offset);
node* expr(uint16_t lineno, uint16_t* offset);
node* add(uint16_t lineno, uint16_t* offset);
node* mod(uint16_t lineno, uint16_t* offset);
node* mul(uint16_t lineno, uint16_t* offset);
node* term(uint16_t lineno, uint16_t* offset);
node* evaluateExpression(uint16_t lineno, uint16_t* offset);
void eval(node* n);
uint16_t parseLine(char* buf, size_t len, char** instr);
void syntaxError(uint16_t lineno);
uint16_t tok2I(token* t);
bool upsertLine(uint16_t lineno, const char* line);
uint8_t* linePos(uint16_t lineno, uint8_t* len);
void moveMemoryDown(char* srcStart, char* srcEnd, char* dstEnd);
void moveMemoryUp(char* srcStart, char* srcEnd, char* dstStart);
