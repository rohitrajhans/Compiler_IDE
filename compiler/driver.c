// Group 13
// Sahil Dubey - 2017A7PS0096P 
// Rohit Milind Rajhans - 2017A7PS0105P
// Saujas Adarkar - 2017A7PS0109P

#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include "symbol_table.h"
#include "type_extractor.h"
#include "semantic_analyzer.h"
#include "intermediate_code.h"
#include "code_gen.h"
#include <time.h>

int main(int argc, char* argv[]) {
    int choice;
    int flag = 0;
    int tokens;
    int parsed = 0;

    Node ** token_stream = NULL;
    lookup_table *table = NULL;
    t_node** parse_tree_ptr;
    AST root;
    ErrorList* err;
    Symbol_Table_Tree tree;
    tuple_list* list;

    // tokens = lexical_analyzer(argv[1], &token_stream, &table, 1);
    parse_tree_ptr = parser(argv[1], "", &parsed, 0);
    if(!parsed) {
        printf("ERROR! Error in parsing\n");
        return 0;
    }
        
    root = generate_AST(*parse_tree_ptr, 0);
    err = initialize_errors();
    tree = create_symbol_table_tree(root, err, 0);
    
    type_checker(root, err, tree);
    sort_errors(err);

    if((err->head) != NULL) {
        printf("Semantic error occurred\n\n");
        print_errors(err);
    }
    else {
        // printf("No semantic errors occurred\n\n");
        // printf("Code compiles successfully\n\n");
        printf("Success");
        list = generate_ir(root);
        generate_code(list, tree, argv[2]);
    }

    return 0;
}