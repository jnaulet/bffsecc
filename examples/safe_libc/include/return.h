#ifndef RETURN_H
#define RETURN_H

typedef int ret_t;

/* generic */
#define SUCCESS          0
#define FAILURE         -1
#define NOT_IMPLEMENTED -2

/* arguments */
#define ARG_INVALID -3

/* memory */
#define MEM_INVALID    -8
#define MEM_OVERLAP    -9
#define MEM_NULL_PTR  -10
#define MEM_TOO_SMALL -11

/* strings */
#define STR_TOO_LONG -16

#endif
