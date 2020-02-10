#include "token.h"

static std::string token_type_name[] =
{
     "TOKEN_TYPE_UNKNOWN",
     "TOKEN_TYPE_IDENTIFIER",
     "TOKEN_TYPE_OPEN_PAREN",
     "TOKEN_TYPE_CLOSE_PAREN",
     "TOKEN_TYPE_LESS_THAN",
     "TOKEN_TYPE_GREATER_THAN",
     "TOKEN_TYPE_STRING",
     "TOKEN_TYPE_COLON",
     "TOKEN_TYPE_SEMI_COLON",
     "TOKEN_TYPE_ASTERISK",
     "TOKEN_TYPE_OPEN_BRACKET",
     "TOKEN_TYPE_CLOSE_BRACKET",
     "TOKEN_TYPE_OPEN_BRACE",
     "TOKEN_TYPE_CLOSE_BRACE",
     "TOKEN_TYPE_HASH",
     "TOKEN_TYPE_END_OF_STREAM",
     "TOKEN_TYPE_DOUBLE_COLON",
     "TOKEN_TYPE_AMPERSAND",
     "TOKEN_TYPE_COMMA",
     "TOKEN_TYPE_EQUAL",
     "TOKEN_TYPE_NUMBER",
};

Token::Token( void )
{
     __type = Token_Type::TOKEN_TYPE_UNKNOWN;
     __text_len = 0;
     __text = nullptr;
}

Token::Token( char* text, size_t len, Token_Type type )
{
     __type = type;
     __text_len = len;
     __text = text;
}

Token::~Token( void )
{

}

bool Token::equals( const std::string& input )
{
     if ( input.length() != __text_len ) {
          return false;
     }

     const char* local_input = input.c_str();

     for ( size_t ii = 0; ii < __text_len; ii++ ) {
          if ( local_input[ii] != __text[ii] ) {
               return false;
          }
     }

     return true;
}

bool Token::is_type( const Token_Type& type )
{
     return (type == __type);
}

Token_Type Token::type( void )
{
     return __type;
}

std::string Token::data( void )
{
     return std::string(__text, __text_len);
}

std::string Token::to_string( void )
{
     std::string tmp(__text, __text_len);

     std::string total = "Token type: " + token_type_name[__type] + " data: ";
     return total + tmp;
}

