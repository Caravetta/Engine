#include "lexer.h"

Lexer::Lexer( const std::string& input )
{
     __input = input;
     __cur_char = &__input[0];
}

Lexer::~Lexer( void )
{

}

Token Lexer::current_token( void )
{
     return __current_token;
}

Token Lexer::next_token( bool advance )
{
     delete_all_white_space();
     Token_Type token_type = TOKEN_TYPE_UNKNOWN;
     size_t token_len = 1;
     char* token_text = __cur_char;

     if ( advance == true ) {
          __cur_char += 1;
     }

     switch ( token_text[0] ) {
     case '/': { /* do nothing */ } break;
     case '(': { token_type = TOKEN_TYPE_OPEN_PAREN; } break;
     case ')': { token_type = TOKEN_TYPE_CLOSE_PAREN; } break;
     case '<': { token_type = TOKEN_TYPE_LESS_THAN; } break;
     case '>': { token_type = TOKEN_TYPE_GREATER_THAN; } break;
     case ';': { token_type = TOKEN_TYPE_SEMI_COLON; } break;
     case '*': { token_type = TOKEN_TYPE_ASTERISK; } break;
     case '&': { token_type = TOKEN_TYPE_AMPERSAND; } break;
     case '{': { token_type = TOKEN_TYPE_OPEN_BRACE; } break;
     case '}': { token_type = TOKEN_TYPE_CLOSE_BRACE; } break;
     case '[': { token_type = TOKEN_TYPE_OPEN_BRACKET; } break;
     case ']': { token_type = TOKEN_TYPE_CLOSE_BRACKET; } break;
     case '\0': { token_type = TOKEN_TYPE_END_OF_STREAM; } break;
     case '#': { token_type = TOKEN_TYPE_HASH; } break;
     case ',': { token_type = TOKEN_TYPE_COMMA; } break;
     case '=': { token_type = TOKEN_TYPE_EQUAL; } break;
     case ':': {
               token_type = TOKEN_TYPE_COLON;

               if ( advance == false ) {
                    if ( __cur_char[1] && __cur_char[1] == ':' ) {
                         token_type = TOKEN_TYPE_DOUBLE_COLON;
                         token_len = 2;
                    }
               } else {
                    if ( __cur_char[0] && __cur_char[0] == ':' ) {
                         token_type = TOKEN_TYPE_DOUBLE_COLON;
                         token_len = 2;
                    }

                    __cur_char += 1;
               }
     } break;
     case '"': {
               token_text = __cur_char;
               token_len = 0;

               while ( __cur_char[0] && __cur_char[0] != '"' ) {
                    if ( __cur_char[0] == '\\' && __cur_char[1] ) {
                         __cur_char += 1;
                    }
                    __cur_char += 1;
               }

               token_type = TOKEN_TYPE_STRING;
               token_len = __cur_char - token_text;

               if ( __cur_char[0] == '"' ) {
                    __cur_char += 1;
               }
     } break;

     default: {
               if ( (token_text[0] != '-') && is_alphabetical(token_text[0]) ) {
                    while ( is_alphabetical(__cur_char[0]) ||
                            is_numeric(__cur_char[0])      ||
                            (__cur_char[0] == '_') ) {
                         __cur_char += 1;
                    }

                    token_type = TOKEN_TYPE_IDENTIFIER;
                    token_len = __cur_char - token_text;

               } else if ( (token_text[0] == '-') || is_numeric(token_text[0]) ) {
                    uint32_t num_decimals = 0;

                    while ( is_numeric(__cur_char[0])                   ||
                            (__cur_char[0] == '.' && num_decimals == 0) ||
                            __cur_char[0] == 'f' ) {
                         num_decimals = (__cur_char[0] == '.' ? num_decimals++ : num_decimals);
                         __cur_char += 1;
                    }

                    token_len = __cur_char - token_text;
                    token_type = TOKEN_TYPE_NUMBER;
               }
     } break;
     }

     Token token(token_text, token_len, token_type);

     if ( advance == true ) {
          __current_token = token;
     } else {
          __cur_char = token_text;
     }

     return token;
}

Token Lexer::peek_at_next_token( void )
{
     Token token;
     return token;
}

bool Lexer::require_token( Token_Type type, bool advance )
{
     Token token = advance ? next_token(true) : __current_token;

     return (token.type() == type);
}

bool Lexer::continue_to( Token_Type type )
{
     Token token = next_token(true);

     while ( !token.is_type(type) && !token.is_type(TOKEN_TYPE_END_OF_STREAM) ) {
          token = next_token(true);
     }

     return !token.is_type(TOKEN_TYPE_END_OF_STREAM);
}

bool Lexer::continue_to_any_identifier( const std::vector< std::string >& identifiers )
{
     Token token = next_token(true);

     while ( !equals_any_identifier(identifiers, token) && !token.is_type(TOKEN_TYPE_END_OF_STREAM) ) {
          token = next_token(true);
     }

     return !token.is_type(TOKEN_TYPE_END_OF_STREAM);
}

void Lexer::delete_all_white_space( void )
{
     while ( 1 ) {
          if ( is_white_space(__cur_char[0]) ) {
               __cur_char += 1;
          } else if ( __cur_char[0] == '/' &&
                      __cur_char[1]        &&
                      __cur_char[1] == '/' ) {
               /* start of a comment line */
               __cur_char += 2;
               while (  __cur_char[0] && !is_end_of_line(__cur_char[0]) ) {
                    __cur_char += 1;
               }
          } else if ( __cur_char[0] == '/' &&
                      __cur_char[1]        &&
                      __cur_char[1] == '*' ) {
               /* start of comment block */
               while ( __cur_char[0] &&
                       __cur_char[1] &&
                       !( __cur_char[0] == '*' && __cur_char[0] == '/' ) ) {
                    __cur_char += 1;
               }
          } else {
               break;
          }
     }
}

bool Lexer::is_alphabetical( char c )
{
     return ( (c >= 'a' && c <='z') || (c >= 'A' && c <='Z') || c == '_' || c == '~' );
}

bool Lexer::is_numeric( char c )
{
     return ( c >= '0' && c <= '9' );
}

bool Lexer::is_end_of_line( char c )
{
     return ( c == '\n' || c == '\r' );
}

bool Lexer::is_white_space( char c )
{
     return ( c == ' ' || c == '\t' || is_end_of_line(c) );
}

bool Lexer::equals_any_identifier( const std::vector< std::string >& identifiers, Token& token )
{
     for ( size_t ii = 0; ii < identifiers.size(); ii++ ) {
          if ( token.equals(identifiers[ii]) ) {
               return true;
          }
     }

     return false;
}

