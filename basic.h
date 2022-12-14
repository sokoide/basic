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
#define MAX_BASMEM (8192)

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
    tkError,
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
    uint16_t offset; // first character's offset in the buffer you specify
    uint8_t len;     // token length
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
void mem();
void run();
uint16_t executeLine(uint16_t idx);
uint16_t getOffsetOfLine(int n);
void getLine(char* buf, size_t len);
void skipSpaces(const char* buf, uint8_t len, uint16_t* offset);
token getToken(const char* buf, uint8_t len, uint16_t* offset, bool peek);
void reset();
void resetNodes();
void resetVars();
void resetLines();

node* newNode(nodeType type, node* lhs, node* rhs);
void freeNode(node* n);
bool consume(tokType type, const char* buf, uint8_t len, uint16_t* offset);

node* expr(const char* buf, uint8_t len, uint16_t* offset);
node* add(const char* buf, uint8_t len, uint16_t* offset);
node* mod(const char* buf, uint8_t len, uint16_t* offset);
node* mul(const char* buf, uint8_t len, uint16_t* offset);
node* term(const char* buf, uint8_t len, uint16_t* offset);
node* evaluateExpression(const char* buf, uint8_t len, uint16_t* offset);
void eval(node* n);

uint16_t parseLine(char* buf, size_t len, char** instr);
void syntaxError(const char* buf, uint8_t len);
uint16_t tok2I(const char* buf, token* t);
bool upsertLine(uint16_t lineno, const char* line);
uint8_t* linePos(uint16_t lineno, uint8_t* len);
void moveMemoryDown(char* srcStart, char* srcEnd, char* dstEnd);
void moveMemoryUp(char* srcStart, char* srcEnd, char* dstStart);
