#include"tree.h"

char * nt_string_map[NON_TERMINAL_SIZE] = {"program", "moduleDeclarations", "moduleDeclaration", "otherModules", "driverModule", "module", "ret", "input_plist",
    "new1", "output_plist", "new2", "dataType", "dataType2", "type", "range", "range2", "moduleDef", "statements", "new3",
    "statement", "ioStmt", "var", "var2", "whichID", "simpleStmt", "assignmentStmt", "whichStmt", "lvalueIDstmt", "lvalueArrStmt", 
    "Index", "moduleReuseStmt", "optional", "idList", "newX", "expression", "new4", "AorBExpr", "arithmeticExpr", "new6",
    "term", "new7", "factor", "PlusMinus", "MulDiv", "relationalOP", "logicalOP", "boolKey", "boolExpr", "new8", "relationalExpr",
    "declareStmt", "iterativeStmt", "conditionalStatement", "caseStmt", "numericCases", 
    "numericCase", "new11", "Default"};

char * t_string_map[TOKEN_NUMBERS] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START",
            "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE", "PRINT",
            "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS",
            "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "PLUS", 
            "MINUS", "MUL", "DIV", "LT", "LE", "GE", "GT", "EQ", "NE", "DEF", "DRIVERDEF",
            "ENDDEF", "DRIVERENDDEF", "COLON", "RANGEOP", "SEMICOL", "COMMA", "ASSIGNOP", 
            "SQBO", "SQBC", "BO", "BC", "COMMENTMARK", "NUM", "RNUM", "ID", "ERROR", "E", "$"
};

t_node* initialize_tree() {
    t_node* root = create_internal(program);

    return root;
}

t_node* create_internal(non_terminals nt) {
    t_node* intern = (t_node*) malloc(sizeof(t_node));
    intern->tag = 1;
    intern->sibling = NULL;
    intern->child = NULL;
    intern->node.internal = nt;

    return intern;
}

t_node* create_leaf(Node n) {
    t_node* leaf = (t_node*) malloc(sizeof(t_node));
    leaf->tag = 0;
    leaf->sibling = NULL;
    leaf->child = NULL;
    leaf->node.leaf = n;

    return leaf;
}

int insert_node(t_node** parent, t_node* child) {
    
    if((*parent)->child == NULL) {
        (*parent)->child = child;
    }
    else {
        t_node* temp = (*parent)->child;
        (*parent)->child = child;
        child->sibling = temp;
    }

    return 1;
}

int print_parse_tree(t_node* root, char* fname) {
    FILE* fp = fopen(fname, "w");

    inorder_traversal(root, -1, fp);
}

int inorder_traversal(t_node* root, non_terminals parent, FILE* fp) {
    if(root == NULL) {
        return 0;
    }
    inorder_traversal(root->child, root->node.internal, fp);
    print_tnode(root, parent, fp);
    if(root->child==NULL)
        return 0;
    
    t_node* org_root = root;
    root = root->child;
    root = root->sibling;
    while(root) {
        inorder_traversal(root, org_root->node.internal, fp);
        root = root->sibling;
    }

    return 1;
}

int print_tnode(t_node* n, non_terminals parent, FILE* fp) {
    if(n==NULL) {
        return 0;
    }

    if(n->tag == 0) {
        fprintf(fp, "Lexeme: %s\tLine No: %d\tToken: %s\t", n->node.leaf.lexeme, n->node.leaf.line_no, t_string_map[n->node.leaf.token]);
        if(n->node.leaf.tag == 1)
            fprintf(fp, "Value: %d\t", n->node.leaf.val.num);
        else if(n->node.leaf.tag == 2)
            fprintf(fp, "Value: %f\t", n->node.leaf.val.rnum);
        else
            fprintf(fp, "Value: ------\t");
        
        fprintf(fp, "Parent Node: %s\t", nt_string_map[parent]);
        fprintf(fp, "Leaf Node: Yes\t");
        fprintf(fp, "Node Symbol: ------\n\n");
    }
    else {
        fprintf(fp, "Lexeme: ------\tLine No: ------\tToken: ------\tValue: ------\t");
        if(parent == -1)
            fprintf(fp, "Parent Node: ROOT\t");
        else
            fprintf(fp, "Parent Node: %s\t", nt_string_map[parent]);
        
        fprintf(fp, "Leaf Node: No\t");
        fprintf(fp, "Node Symbol: %s\n\n", nt_string_map[n->node.internal]);
    }

    return 1;
}