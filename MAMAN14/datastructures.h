/* datastructures.h */
/* this file contains most data structures of the assembler program */

typedef enum {false, true} boolean;

/* Type of encoding */
typedef enum {absolute, external, relocatable} encoding;

/* address methods */
typedef enum {immediate, direct, jump, registr} addressing;

/* commands */
char *commands[] = {"mov","cmp","add","sub",
					   "not","clr","lea","inc",
					   "dec","jmp","bne","red",
					   "prn","jsr","rts","stop"};

/* registers */
char *registers[] = {"r0","r1","r2","r3","r4","r5","r6","r7"};

/* instructions */
char *instructions[] = {".data",".string",".entry",".extern"};

/* labels */
typedef struct label label;
typedef struct labeltable labeltable;

