#include <cctype>
#include "token.h"
#include "core_common.h"

namespace Engine {

int parse_symbol_token( std::fstream& stream, token_t* token, int input_char )
{
    bool still_symbol = true;
    token->data += (char)input_char;

    while ( still_symbol ) {
        input_char = stream.get();

        if ( isalpha(input_char) || isdigit(input_char) || input_char == '_' ) {
            token->data += (char)input_char;
        } else {
            still_symbol = false;
        }
    }

    return input_char;
}

int parse_integer_token( std::fstream& stream, token_t* token, int input_char )
{
    UNUSED_ARG( stream );
    UNUSED_ARG( token );
    UNUSED_ARG( input_char );
#if 0
    bool still_integer = true;
    token->data += input_char;

    if ( input_char == '0' ) {
        input_char = stream.peek();

        if ( input_char == 'x' || input_char == 'X' ) {
            token->data += input_char;

            input_char = stream.get();

            while ( still_integer ) {
                input_char = stream.get();

                if ( isxdigit(input_char) ) {
                    token->data += input_char;
                } else {
                    still_integer = false;
                }
            }
        }
    }

    while ( still_integer ) {
        input_char = stream.get();

        if ( isdigit(input_char) ) {
            token->data += input_char;
        } else if ( input_char == '.' ) {
            if ( token->type == FLOAT_TOKEN ) {
                LOG_ERROR("Multiple decimals in float");
            }
            token->type = FLOAT_TOKEN;
            token->data += input_char;
        } else {
            still_integer = false;
        }
    }

    return input_char;
#endif
    return 0;
}

int parse_literal_token( std::fstream& stream, token_t* token, int input_char )
{
    UNUSED_ARG( stream );
    UNUSED_ARG( token );
    UNUSED_ARG( input_char );
#if 0
    LOG("parse_literal_token");
    bool still_literal = true;
    token->data.clear();

    while ( still_literal ) {
        input_char = stream.get();

        if ( input_char == '\\' ) {
            input_char = stream.peek();

            switch( input_char ) {
            case '\\':
            case '\"': {
                token->data += '\\';
                input_char = stream.get();
                token->data += input_char;
            }
            case 0x0A: {
                LOG_ERROR("Hit EOL durning literal token")
            }
            case -1: {
                LOG_ERROR("Hit EOF during literal token");
            }
            default : {
                token->data += input_char;
            }
            }
            continue;
        } else if ( input_char != '\"' && input_char != -1 ) {
            token->data += input_char;
            continue;
        } else if ( input_char == -1 ) {
            LOG_ERROR("Hit EOF during literal token");
        } else {
            input_char = stream.get();
            still_literal = false;
        }
    }

    return input_char;
#endif
    return 0;
}

int parse_const_literal_token( std::fstream& stream, token_t* token, int input_char )
{
    UNUSED_ARG( stream );
    UNUSED_ARG( token );
    UNUSED_ARG( input_char );
    LOG("parse_const_literal_token");
    return 0;
}

int parse_punctuation_token( std::fstream& stream, token_t* token, int input_char )
{
    UNUSED_ARG( stream );
    UNUSED_ARG( token );
    UNUSED_ARG( input_char );
#if 0
    token->data = input_char;

    switch ( input_char ) {
    case '!': { // ! or !=
        input_char = stream.peek();
        if ( input_char == '=' ) {
            input_char == stream.get();
            token->data += input_char;
        }
    } break;
    case '#': { // # or ##
        input_char = stream.peek();
        if ( input_char == '#' ) {
            input_char == stream.get();
            token->data += input_char;
        }
    } break;
    case '%': { // % or %=
        input_char = stream.peek();
        if ( input_char == '=' ) {
            input_char == stream.get();
            token->data += input_char;
        }
    } break;
    case '&': { // & or && or &=
        input_char = stream.peek();
        if ( input_char == '=' || input_char == '&' ) {
            input_char == stream.get();
            token->data += input_char;
        }
    } break;
    case '*': { // * or *=
        input_char = stream.peek();
        if ( input_char == '=' ) {
            input_char == stream.get();
            token->data += input_char;
        }
    } break;
    case '+': { // + or ++ or +=
        input_char = stream.peek();
        if ( input_char == '=' || input_char == '+' ) {
            input_char == stream.get();
            token->data += input_char;
        }
    } break;
    default: {
        // Do nothing
    } break;
    }

    input_char = stream.get();
    return input_char;
#endif
    return 0;
}

int parse_whitespace_token( std::fstream& stream, token_t* token, int input_char )
{
    UNUSED_ARG( stream );
    UNUSED_ARG( token );
    UNUSED_ARG( input_char );
    return 0;
}

int parse_eol_token( std::fstream& stream, token_t* token, int input_char )
{
    UNUSED_ARG( stream );
    UNUSED_ARG( token );
    UNUSED_ARG( input_char );
    return 0;
}

int parse_eof_token( std::fstream& stream, token_t* token, int input_char )
{
    UNUSED_ARG( stream );
    UNUSED_ARG( token );
    UNUSED_ARG( input_char );
    return 0;
}

std::string token_to_string[] = {
    "INVALID_TOKEN",
    "SYMBOL_TOKEN",
    "INTEGER_TOKEN",
    "FLOAT_TOKEN",
    "LITERAL_TOKEN",
    "CONST_LITERAL_TOKEN",
    "PUNCTUATION_TOKEN",
    "WHITESPACE_TOKEN",
    "EOL_TOKEN",
    "EOF_TOKEN"
};

std::string token_type_to_string( token_type_t type )
{
    return token_to_string[type];
}

void print_token_info( token_t* token )
{
    LOG("Token: " << token->data << " Type: " << token_type_to_string(token->type));
}

} // end namespace Engine

