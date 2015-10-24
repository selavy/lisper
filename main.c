#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *
 * atom ::= <character> <atom> | <character>
 * character ::= digit | letter
 * digit ::= "1" | ... "9" | "0"
 * letter ::= "a" | ... | "z"
 * empty ::= " "
 *
 */

#define INSTREAM stdin
#define MAX_SZ 1024
#define STACK_SZ 1024
#define FAILURE -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

enum AtomType {
    NONE       = 0x00,

    /* VALUE TYPES */
    VALUE      = 0x0F,
    INTEGER    = 0x01,
    STRING     = 0x02,
    IDENTIFIER = 0x04,
    /*      = 0x08, */

    /* NUMERIC OPERATORS */
    OPERATOR   = 0xF0,
    PLUS       = 0x10,
    MINUS      = 0x20,
    DIVIDE     = 0x40,
    MULTIPLY   = 0x80,

    /* EXPR MARKER */
    EXPR_START = 0x100, /* "(" */
    EXPR_END   = 0x200, /* ")" */
};

struct Atom {
    char *name;
    int sz;
    enum AtomType type;
    int value;
};

/* struct SExpr { */
/*     struct Atom* atom; */
/*     struct SExpr* next; */
/* }; */

int IsWhiteSpace(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

int IsBeginSExpr(int c) {
    return c == '(';
}

int IsFinishSExpr(int c) {
    return c == ')';
}

int UseBuffer(char buf[MAX_SZ], int p, struct Atom *atom) {
    if (p > 0) {
        buf[p] = 0;
        //DEBUG
        printf("adding %s\n", &(buf[0]));
        //GUBED

        atom->name = malloc(p+1);
        memcpy(atom->name, &(buf[0]), p);
        atom->name[p] = 0;
        atom->sz = p;
        atom->type = NONE;
        return TRUE;
    } else {
        return FALSE;
    }
}

struct AtomList {
    struct AtomList* next;
    struct Atom* atom;
};

void AtomList_Push(struct AtomList** list, struct Atom* atom) {
    struct AtomList* curr = malloc(sizeof(*curr));
    curr->next = *list;
    curr->atom = malloc(sizeof(atom));
    memcpy(curr->atom, atom, sizeof(*atom));
    *list = curr;
}

struct LinkedList {
    struct LinkedList *next;
    void* buf;
    int sz;
};

void LinkedList_Push(struct LinkedList** list, void* buf, int sz) {
    struct LinkedList* curr = malloc(sizeof(*curr));
    curr->next = *list;
    curr->buf = malloc(sz);
    memcpy(curr->buf, buf, sz);
    curr->sz = sz;
    *list = curr;
}

int main(int argc, char *argv[]) {
    struct LinkedList* llist = 0;
    struct LinkedList* lcur;
    int c;
    int i;
    char buf[MAX_SZ];
    int buf_p = 0;
    struct Atom stack[STACK_SZ];
    int stack_p = 0;
    struct AtomList* alist = 0;
    struct AtomList* lists[STACK_SZ];
    int list_p = 0;

    while ((c = fgetc(INSTREAM)) != EOF) {
        //DEBUG
        printf("C = %c\n", c);
        //GUBED

        if (IsBeginSExpr(c)) {
            //DEBUG
            printf("Begin S-Expr\n");
            //GUBED

            if (UseBuffer(buf, buf_p, &(stack[stack_p]))) ++stack_p;
            buf_p = 0;

            stack[stack_p].name = 0;
            stack[stack_p].sz = 0;
            stack[stack_p].type = EXPR_START;
        }
        else if (IsFinishSExpr(c)) {
            //DEBUG
            printf("Finish S-Expr\n");
            //GUBED

            if (UseBuffer(buf, buf_p, &(stack[stack_p]))) ++stack_p;
            buf_p = 0;

            printf("Add expression to lists...\n");
            alist = 0;
            --stack_p;
            while (stack_p > 0 && stack[stack_p].type != EXPR_START) {
                printf("adding %s\n", stack[stack_p].name);
                AtomList_Push(&alist, &(stack[stack_p]));
                --stack_p;
            }
            lists[list_p++] = alist;
            printf("finished adding expression to lists\n\n");

            --stack_p;
        }
        else if (IsWhiteSpace(c)) {
            //DEBUG
            printf("whitespace\n");
            //GUBED

            if (UseBuffer(buf, buf_p, &(stack[stack_p]))) ++stack_p;
            buf_p = 0;
        }
        else {
            //DEBUG
            printf("other\n");
            //GUBED

            buf[buf_p++] = c;
        }
    }

    /* printf("\n\nToken List\n"); */
    /* for (i = 0; i < stack_p; ++i) { */
    /*     printf("name = %s, size = %d\n", stack[i].name, stack[i].sz); */
    /* } */

    for (i = 0; i < list_p; ++i) {
        for (alist = lists[list_p]; alist != 0; alist = alist->next) {
            printf("%s -> ", alist->atom->name);
        }
        printf("\n");
    }

    /* for (i = 0; i < 10; ++i) { */
    /*     LinkedList_Push(&llist, &i, sizeof(i)); */
    /* } */

    /* for(lcur = llist; lcur != 0; lcur = lcur->next) { */
    /*     printf("%d\n", *(int*)lcur->buf); */
    /* } */

    return 0;
}

void PrintUsage(const char *prog) {
    printf("Usage: %s [FILE]\n", prog);
}
