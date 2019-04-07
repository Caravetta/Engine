#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
#include <fstream>

typedef enum {
    INVALID_TOKEN           = 1 << 0,
    SYMBOL_TOKEN            = 1 << 1,
    INTEGER_TOKEN           = 1 << 2,
    FLOAT_TOKEN             = 1 << 3,
    LITERAL_TOKEN           = 1 << 4,
    CONST_LITERAL_TOKEN     = 1 << 5,
    PUNCTUATION_TOKEN       = 1 << 6,
    WHITESPACE_TOKEN        = 1 << 7,
    EOL_TOKEN               = 1 << 8,
    EOF_TOKEN               = 1 << 9
} token_type_t;

typedef struct {
    token_type_t    type;
    std::string     data;
} token_t;

std::string token_type_to_string( token_type_t type );
void print_token_info( token_t* token );

int parse_symbol_token( std::fstream& stream, token_t* token, int input_char );
int parse_integer_token( std::fstream& stream, token_t* token, int input_char );
int parse_literal_token( std::fstream& stream, token_t* token, int input_char );
int parse_const_literal_token( std::fstream& stream, token_t* token, int input_char );
int parse_punctuation_token( std::fstream& stream, token_t* token, int input_char );
int parse_whitespace_token( std::fstream& stream, token_t* token, int input_char );
int parse_eol_token( std::fstream& stream, token_t* token, int input_char );
int parse_eof_token( std::fstream& stream, token_t* token, int input_char );

#endif //__TOKEN_H__
