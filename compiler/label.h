// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#ifndef _LABEL_
#define _LABEL_

#define AST_LABEL_NUMBER 37

// List of enums for the non-leaf nodes of AST
typedef enum {
    AST_PROGRAM, MODULE_DECLARATIONS, MODULE_DECLARATION, OTHER_MODULES, AST_DRIVER, AST_MODULE, INPUT_PLIST, NEW1,
    OUTPUT_PLIST, NEW2, DATA_TYPE, DATA_TYPE2, RANGE, RANGE2, STATEMENTS, VAR, ASSIGNMENT_STMT, 
    LVALUE_ARR_STMT, MODULE_REUSE_STMT, ID_LIST, NEWX, EXPRESSION, NEW6, NEW7, NEW8, RELATIONAL_EXPR, 
    DECLARE_STMT, AST_FOR, AST_WHILE, CONDITIONAL_STMT, CASE_STMT_T, CASE_STMT_F, NUMERIC_CASES, NUMERIC_CASE, IO_READ,
    IO_WRITE, AST_DEFAULT
} Label;

#endif