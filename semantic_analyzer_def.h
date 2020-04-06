#ifndef _SEMANTICANALYZERDEF_
#define _SEMANTICANALYZERDEF_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table_def.h"
//#include "symbol_table.h"

#define ERROR_STRING_SIZE 200

typedef struct error{
	int line_num;
	char* str;
	struct error* next;

}Error;

typedef struct errorList{
	Error* head;
	int total_errors;
}ErrorList;

#endif