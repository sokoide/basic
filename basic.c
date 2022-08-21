#include "basic.h"

char lines[MAX_BASMEM];
uint16_t szLines;
node nodes[MAX_NODES];
int vars[26];

void start() {
    char buf[MAX_LINE_LEN];
    char msg[64];
    uint16_t lineno;
    char* instr;

    memset(buf, 0, sizeof(buf));
    memset(msg, 0, sizeof(msg));
    reset();

    print("> ");
    getLine(buf, sizeof(buf));

    if (strcmp("list", buf) == 0) {
        list();
    } else if (strcmp("run", buf) == 0) {
        run();
    } else if (strcmp("new", buf) == 0) {
        newList();
    } else if (buf[0] == '\0') {
        exit(0);
    } else {
        lineno = parseLine(buf, sizeof(buf), &instr);

        if (lineno > 0 && lineno <= MAX_LINE_LEN) {
            // TODO:
            /* memcpy(lines[lineno - 1], instr, LINE_LEN); */
            /* sprintf(msg, "line:%d, %s\r\n", lineno, instr); */
        } else {
            sprintf(msg, "line number must be between 1 and %d\r\n",
                    MAX_LINE_LEN);
        }
        print(msg);
    }
}

void print(const char* msg) {
#ifdef STM32F072xB
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 10);
#else
    printf("%s", msg);
#endif
}

void list() {
    // TODO:
    /* for (int i = 0; i < MAX_LINES; i++) { */
    /*     if (lines[i][0] != '\0') { */
    /*         char msg[64]; */
    /*         sprintf(msg, "%d %s\r\n", i + 1, lines[i]); */
    /*         print(msg); */
    /*     } */
    /* } */
}

void newList() {
    // TODO:
    /* for (int i = 0; i < MAX_LINES; i++) { */
    /*     lines[i][0] = '\0'; */
    /* } */
}

void run() {
    uint16_t lineno = 1;
    node* n;
    token tok;
    // TODO:

    /* while (lineno <= MAX_LINES) { */
    /*     if (lines[lineno - 1][0] == '\0') { */
    /*         lineno++; */
    /*         continue; */
    /*     } */
    /*     uint16_t offset = 0; */
    /*     tok = getToken(lineno, &offset, false); */
    /*     bool done = false; */
    /*     int idx; */
    /*     while (!done) { */
    /*         if (tok.type == tkPrint) { */
    /*             n = evaluateExpression(lineno, &offset); */
    /*             if (n->type == ndString) { */
    /*                 print(n->svalue); */
    /*             } else if (n->type == ndInteger || n->type == ndIdent) { */
    /*                 char msg[32]; */
    /*                 sprintf(msg, "%d", n->ivalue); */
    /*                 print(msg); */
    /*             } */
    /*             freeNode(n); */
    /*             print("\r\n"); */
    /*             done = true; */
    /*         } else if (tok.type == tkGoto) { */
    /*             done = true; */
    /*             n = evaluateExpression(lineno, &offset); */
    /*             // since it's incremented outside of the while loop */
    /*             lineno = n->ivalue - 1; */
    /*             freeNode(n); */
    /*         } else if (tok.type == tkIf) { */
    /*             n = evaluateExpression(lineno, &offset); */
    /*             if ((n->type == ndInteger || n->type == ndIdent) && */
    /*                 n->ivalue == 0) { */
    /*                 done = true; */
    /*             } else { */
    /*                 tok = getToken(lineno, &offset, false); */
    /*             } */
    /*             freeNode(n); */
    /*         } else if (tok.type == tkIdent) { */
    /*             // assign (e.g a=40+2) */
    /*             if (!consume(tkAssign, lineno, &offset)) { */
    /*                 syntaxError(lineno); */
    /*             } */
    /*             n = evaluateExpression(lineno, &offset); */
    /*             idx = lines[lineno - 1][tok.start] - 'a'; */
    /*             vars[idx] = n->ivalue; */
    /*  */
    /*             freeNode(n); */
    /*             done = true; */
    /*         } else { */
    /*             // epxression (e.g 3*2+4*2) */
    /*             n = evaluateExpression(lineno, &offset); */
    /*             freeNode(n); */
    /*             done = true; */
    /*         } */
    /*     } */
    /*     lineno++; */
    /* } */
}

void getLine(char* buf, size_t len) {
#ifdef STM32F072xB
    bool done = false;
    uint16_t idx = 0;
    char c;
    HAL_StatusTypeDef ret = HAL_TIMEOUT;
    while (!done && idx < len - 1) {
        do {
            ret = HAL_UART_Receive(&huart2, (uint8_t*)&c, 1, 1000);
        } while (ret == HAL_TIMEOUT);

        if (ret == HAL_OK) {
            if (c == 0x0d || c == 0x1b /* esc */) {
                HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 10);
                done = true;
            } else if (c >= ' ' && c <= '~') {
                // echo back
                HAL_UART_Transmit(&huart2, (uint8_t*)&c, 1, 10);
                buf[idx++] = (char)c;
            }
        }
    }
    buf[idx] = '\0';
#else
    getline(&buf, &len, stdin);
    for (int i = 0; i < (int)len; i++) {
        if (buf[i] == 0x0d || buf[i] == 0x0a)
            buf[i] = '\0';
    }
#endif
}

void skipSpaces(uint16_t lineno, uint16_t* offset) {
    // TODO:
    /* uint16_t i = 0; */
    /* char c = lines[lineno - 1][*offset + i]; */
    /* while (*offset + i < LINE_LEN && c == ' ') { */
    /*     i++; */
    /*     c = lines[lineno - 1][*offset + i]; */
    /* } */
    /* *offset = *offset + i; */
}

token getToken(uint16_t lineno, uint16_t* offset, bool peek) {
    token tok;
    return tok;

    // TODO:
    /* uint16_t i = 0; */
    /*  */
    /* skipSpaces(lineno, offset); */
    /* tok.lineno = lineno; */
    /* tok.start = *offset; */
    /*  */
    /* if (*offset >= LINE_LEN) { */
    /*     tok.type = tkNull; */
    /*     return tok; */
    /* } */
    /*  */
    /* char c = lines[lineno - 1][*offset + i]; */
    /* if (c == '\0') { */
    /*     tok.type = tkNull; */
    /*     return tok; */
    /* } else if (c == '"') { */
    /*     // tkString */
    /*     tok.type = tkString; */
    /*     tok.start = *offset + 1; */
    /*     i++; */
    /*     c = lines[lineno - 1][*offset + i]; */
    /*     while (*offset + i < LINE_LEN && c != '"') { */
    /*         i++; */
    /*         c = lines[lineno - 1][*offset + i]; */
    /*     } */
    /*     tok.len = i - 1; */
    /* } else if (c == '=') { */
    /*     tok.type = tkAssign; */
    /*     tok.start = *offset; */
    /*     tok.len = 1; */
    /*     i++; */
    /* } else if (c == '(') { */
    /*     tok.type = tkLp; */
    /*     tok.start = *offset; */
    /*     tok.len = 1; */
    /*     i++; */
    /* } else if (c == ')') { */
    /*     tok.type = tkRp; */
    /*     tok.start = *offset; */
    /*     tok.len = 1; */
    /*     i++; */
    /* } else if (c >= '0' && c <= '9') { */
    /*     tok.type = tkNumber; */
    /*     c = lines[lineno - 1][*offset + i]; */
    /*     while (*offset + i < LINE_LEN && c >= '0' && c <= '9') { */
    /*         i++; */
    /*         c = lines[lineno - 1][*offset + i]; */
    /*     } */
    /*     tok.len = i; */
    /* } else if (c == '+') { */
    /*     tok.type = tkAdd; */
    /*     tok.start = *offset; */
    /*     tok.len = 1; */
    /*     i++; */
    /* } else if (c == '-') { */
    /*     tok.type = tkSub; */
    /*     tok.start = *offset; */
    /*     tok.len = 1; */
    /*     i++; */
    /* } else if (c == '*') { */
    /*     tok.type = tkMul; */
    /*     tok.start = *offset; */
    /*     tok.len = 1; */
    /*     i++; */
    /* } else if (c == '/') { */
    /*     tok.type = tkDiv; */
    /*     tok.start = *offset; */
    /*     tok.len = 1; */
    /*     i++; */
    /* } else if (c == '%') { */
    /*     tok.type = tkMod; */
    /*     tok.start = *offset; */
    /*     tok.len = 1; */
    /*     i++; */
    /* } else if (isalpha(c)) { */
    /*     // keyword or ident */
    /*     tok.start = *offset; */
    /*     i++; */
    /*     c = lines[lineno - 1][*offset + i]; */
    /*     while (*offset + i < LINE_LEN && isalnum(c)) { */
    /*         i++; */
    /*         c = lines[lineno - 1][*offset + i]; */
    /*     } */
    /*     tok.len = i; */
    /*     if (strncmp("goto", &lines[lineno - 1][tok.start], tok.len) == 0) {
     */
    /*         tok.type = tkGoto; */
    /*     } else if (strncmp("if", &lines[lineno - 1][tok.start], tok.len) ==
     * 0) { */
    /*         tok.type = tkIf; */
    /*     } else if (strncmp("print", &lines[lineno - 1][tok.start], tok.len)
     * == */
    /*                0) { */
    /*         tok.type = tkPrint; */
    /*     } else { */
    /*         tok.type = tkIdent; */
    /*     } */
    /* } else { */
    /*     syntaxError(lineno); */
    /* } */
    /*  */
    /* if (!peek) */
    /*     *offset = *offset + i; */
    /* return tok; */
}

void reset() {
    resetNodes();
    resetVars();
    resetLines();
}

void resetNodes() {
    for (int i = 0; i < MAX_NODES; i++) {
        freeNode(&nodes[i]);
    }
}

void resetLines() {
    for (int i = 0; i < MAX_BASMEM / 4; i += 4) {
        *((uint32_t*)&lines[i]) = 0;
    }
    szLines = 0;
}

void resetVars() {
    for (int i = 0; i < sizeof(vars) / sizeof(vars[0]); i++) {
        vars[i] = 0;
    }
}

node* newNode(nodeType type, node* lhs, node* rhs) {
    for (int i = 0; i < MAX_NODES; i++) {
        if (nodes[i].type == ndNotUsed) {
            nodes[i].type = type;
            nodes[i].lhs = lhs;
            nodes[i].rhs = rhs;
            return &nodes[i];
        }
    }

    print("Node overflow");
    return NULL;
}

void freeNode(node* n) {
    if (n->lhs != NULL) {
        freeNode(n->lhs);
    }
    if (n->rhs != NULL) {
        freeNode(n->rhs);
    }
    n->type = ndNotUsed;
    n->lhs = n->rhs = NULL;
}

/* check if the next token is 'type'.
 * if yes, proceeds the offset (consumes) and return true
 */
bool consume(tokType type, uint16_t lineno, uint16_t* offset) {
    token tok = getToken(lineno, offset, true);
    if (tok.type == type) {
        getToken(lineno, offset, false);
        return true;
    }
    return false;
}

/* grammar:
 * expr = add
 * add  = mod ('+' mod | '-' mod)*
 * mod  = mul ('%'  mul)*
 * mul  = term ('*' term | '/' term)*
 * term = IDENT | STRING | NUMBER | '(' expr ')'
 */
node* expr(uint16_t lineno, uint16_t* offset) {
    node* n = add(lineno, offset);
    return n;
}

node* add(uint16_t lineno, uint16_t* offset) {
    node* n = mod(lineno, offset);
    while (true) {
        if (consume(tkAdd, lineno, offset)) {
            n = newNode(ndAdd, n, mod(lineno, offset));
        } else if (consume(tkSub, lineno, offset)) {
            n = newNode(ndSub, n, mod(lineno, offset));
        } else {
            return n;
        }
    }
}

node* mod(uint16_t lineno, uint16_t* offset) {
    node* n = mul(lineno, offset);
    while (true) {
        if (consume(tkMod, lineno, offset)) {
            n = newNode(ndMod, n, mul(lineno, offset));
        } else {
            return n;
        }
    }
    return n;
}

node* mul(uint16_t lineno, uint16_t* offset) {
    node* n = term(lineno, offset);
    while (true) {
        if (consume(tkMul, lineno, offset)) {
            n = newNode(ndMul, n, term(lineno, offset));
        } else if (consume(tkDiv, lineno, offset)) {
            n = newNode(ndDiv, n, term(lineno, offset));
        } else {
            return n;
        }
    }
}

node* term(uint16_t lineno, uint16_t* offset) {
    node* n = NULL;
    if (consume(tkLp, lineno, offset)) {
        n = expr(lineno, offset);
        if (!consume(tkRp, lineno, offset)) {
            print("matching ) doesn't exist");
        }
        return n;
    }

    token tok = getToken(lineno, offset, false);
    // TODO:
    /* if (tok.type == tkIdent) { */
    /*     n = newNode(ndIdent, NULL, NULL); */
    /*     strncpy(n->svalue, &lines[lineno - 1][tok.start], tok.len); */
    /*     n->svalue[tok.len] = '\0'; */
    /* } else if (tok.type == tkString) { */
    /*     n = newNode(ndString, NULL, NULL); */
    /*     strncpy(n->svalue, &lines[lineno - 1][tok.start], tok.len); */
    /*     n->svalue[tok.len] = '\0'; */
    /* } else if (tok.type == tkNumber) { */
    /*     n = newNode(ndInteger, NULL, NULL); */
    /*     n->type = ndInteger; */
    /*     n->ivalue = tok2I(&tok); */
    /* } else { */
    /*     syntaxError(lineno); */
    /* } */

    return n;
}

node* evaluateExpression(uint16_t lineno, uint16_t* offset) {
    node* n = expr(lineno, offset);
    eval(n);
    return n;
}

void eval(node* n) {
    int idx;

    switch (n->type) {
    case ndNotUsed:
    case ndNull:
    case ndString:
    case ndInteger:
        break;
    case ndIdent:
        idx = n->svalue[0] - 'a';
        n->ivalue = vars[idx];
        break;
    case ndAdd:
        eval(n->lhs);
        eval(n->rhs);
        n->type = ndInteger;
        n->ivalue = n->lhs->ivalue + n->rhs->ivalue;
        break;
    case ndSub:
        eval(n->lhs);
        eval(n->rhs);
        n->type = ndInteger;
        n->ivalue = n->lhs->ivalue - n->rhs->ivalue;
        break;
    case ndMod:
        eval(n->lhs);
        eval(n->rhs);
        n->type = ndInteger;
        n->ivalue = n->lhs->ivalue % n->rhs->ivalue;
        break;
    case ndMul:
        eval(n->lhs);
        eval(n->rhs);
        n->type = ndInteger;
        n->ivalue = n->lhs->ivalue * n->rhs->ivalue;
        break;
    case ndDiv:
        eval(n->lhs);
        eval(n->rhs);
        n->type = ndInteger;
        n->ivalue = n->lhs->ivalue / n->rhs->ivalue;
        break;
    }
}

uint16_t parseLine(char* buf, size_t len, char** instr) {
    uint16_t lineno = 0;

    for (int i = 0; i < (int)len; i++) {
        if (buf[i] == '\0' || buf[i] == 0x0d)
            break;
        if (buf[i] >= '0' && buf[i] <= '9') {
            lineno = lineno * 10 + buf[i] - '0';
        } else if (buf[i] == ' ' || buf[i] == '\t') {
            // skip
        } else {
            // done
            *instr = &buf[i];
            break;
        }
    }
    return lineno;
}

void syntaxError(uint16_t lineno) {
    char msg[64];
    sprintf(msg, "* Syntax error in line %d", lineno);
    print(msg);
}

uint16_t tok2I(token* t) {
    if (t->type != tkNumber) {
        print("Tok2I error");
    }
    uint16_t ret = 0;
    for (int i = t->start; i < (t->start + t->len); i++) {
        // TODO:
        /* ret = ret * 10 + lines[t->lineno - 1][i] - '0'; */
    }
    return ret;
}

/* find lineno.
 * if exists, expands/shrinks memory to store the line
 * and updates it.
 * if it doesn't exists, expands memory and store it.
 * returns true if successful.
 * false if oom.
 */
bool upsertLine(uint16_t lineno, const char* line) {
    uint16_t idx = 0;
    basline* p;
    uint16_t len = strlen(line);
    uint16_t diff = 0;

    while (true) {
        p = (basline*)&lines[idx];
        if (p->lineno == lineno) {
            if (p->len == len) {
                // same size, update
                strncpy(p->line, line, len);
                return true;
            } else if (p->len > len) {
                // shorter, shrink
                diff = p->len - len;
                moveMemoryUp((char*)p + diff, &lines[szLines - 1], (char*)p);
                //  alloc
                szLines -= diff;
                p->lineno = lineno;
                p->len = len;
                strncpy(p->line, line, len);
                return true;
            } else {
                // longer, expand
                diff = len - p->len;
                if (szLines + diff < MAX_BASMEM) {
                    moveMemoryDown((char*)p, &lines[szLines - 1],
                                   &lines[szLines - 1 + diff]);
                    //  alloc
                    szLines += diff;
                    p->lineno = lineno;
                    p->len = len;
                    strncpy(p->line, line, len);
                } else {
                    return false;
                }
                return true;
            }
        } else if (p->lineno > lineno) {
            // expand
            if (szLines + 3 + len < MAX_BASMEM) {
                moveMemoryDown((char*)p, &lines[szLines - 1],
                               &lines[szLines - 1 + 3 + len]);
                // alloc
                szLines += 3 + len;
                p->lineno = lineno;
                p->len = len;
                strncpy(p->line, line, len);
            } else {
                return false;
            }
            return true;
        } else if (p->lineno == 0) {
            // last line. add here
            if (idx + 3 + len < MAX_BASMEM) {
                // alloc
                szLines += 3 + len;
                p->lineno = lineno;
                p->len = len;
                strncpy(p->line, line, len);
                return true;
            } else {
                return false;
            }
        }
        idx = idx + 3 + p->len;
        if (idx >= MAX_BASMEM - sizeof(basline))
            break;
    }
    return false;
}

/* check if the lineno exists in 'lines' memory.
 * if yes, returns the pointer and update len.
 * if no, returns NULL
 */
uint8_t* linePos(uint16_t lineno, uint8_t* len) {
    uint16_t idx = 0;
    basline* p;
    while (true) {
        p = (basline*)&lines[idx];
        if (p->lineno == lineno) {
            *len = p->len;
            return (uint8_t*)p;
        }
        idx = idx + 3 + p->len;
        if (idx >= MAX_BASMEM - sizeof(basline))
            break;
    }
    return NULL;
}

/* copy memory from [srcStart, srcEnd]
 * to [dstEnd-srcEnd+srcStart, dstEnd]
 */
void moveMemoryDown(char* srcStart, char* srcEnd, char* dstEnd) {
    /* char* dstStart = dstEnd - srcEnd + srcStart; */
    char* p = srcEnd;
    while (p >= srcStart) {
        *dstEnd = *p;
        p--;
        dstEnd--;
    }
}

/* copy memory from [srcStart, srcEnd]
 * to [dstStart, dstStart + srcEnd - srcStart]
 */
void moveMemoryUp(char* srcStart, char* srcEnd, char* dstStart) {
    /* char* dstEnd = dstStart + srcEnd - srcStart; */
    char* p = dstStart;
    while (p <= srcEnd) {
        *p = *srcStart;
        p++;
        srcStart++;
    }
}
