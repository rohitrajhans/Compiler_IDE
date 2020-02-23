#include <float.h>
#include "lexer_def.h"
#include "lookup_table.h"

FILE* open_file(char* filename);
int string_flush(char *str);
int get_stream(FILE* fp);
Node* create_node();
int add_error(char ch);
Node* get_next_token(FILE* fp, lookup_table table);
int lexical_analyzer(char* filename, Node*** n, lookup_table** table, int check);
