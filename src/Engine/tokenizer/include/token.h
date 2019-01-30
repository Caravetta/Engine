#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
#include <fstream>

namespace Engine {

typedef enum {
    INVALID_TOKEN,
    SYMBOL_TOKEN,
    INTEGER_TOKEN,
    FLOAT_TOKEN,
    LITERAL_TOKEN,
    CONST_LITERAL_TOKEN,
    PUNCTUATION_TOKEN,
    WHITESPACE_TOKEN,
    EOL_TOKEN,
    EOF_TOKEN
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

} // end namespace Engine

#endif //__TOKEN_H__
