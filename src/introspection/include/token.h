#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>

enum Token_Type {
     TOKEN_TYPE_UNKNOWN,
     TOKEN_TYPE_IDENTIFIER,
     TOKEN_TYPE_OPEN_PAREN,
     TOKEN_TYPE_CLOSE_PAREN,
     TOKEN_TYPE_LESS_THAN,
     TOKEN_TYPE_GREATER_THAN,
     TOKEN_TYPE_STRING,
     TOKEN_TYPE_COLON,
     TOKEN_TYPE_SEMI_COLON,
     TOKEN_TYPE_ASTERISK,
     TOKEN_TYPE_OPEN_BRACKET,
     TOKEN_TYPE_CLOSE_BRACKET,
     TOKEN_TYPE_OPEN_BRACE,
     TOKEN_TYPE_CLOSE_BRACE,
     TOKEN_TYPE_HASH,
     TOKEN_TYPE_END_OF_STREAM,
     TOKEN_TYPE_DOUBLE_COLON,
     TOKEN_TYPE_AMPERSAND,
     TOKEN_TYPE_COMMA,
     TOKEN_TYPE_EQUAL,
     TOKEN_TYPE_NUMBER,
};

class Token {
public:
     Token( void );
     Token( char* text, size_t len, Token_Type type );
     ~Token( void );

     bool equals( const std::string& input );
     bool is_type( const Token_Type& type );
     Token_Type type( void );
     std::string data( void );

     std::string to_string( void );

private:
     Token_Type __type;
     size_t __text_len;
     char* __text;
};

#endif //__TOKEN_H__
