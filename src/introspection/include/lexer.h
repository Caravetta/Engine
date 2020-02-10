#ifndef __LEXER_H__
#define __LEXER_H__

#include <vector>
#include "token.h"

class Lexer {
public:
     Lexer( const std::string& input );
     ~Lexer( void );

     Token current_token( void );
     Token next_token( bool advance );
     Token peek_at_next_token( void );
     bool require_token( Token_Type type, bool advance );
     bool continue_to( Token_Type type );
     bool continue_to_any_identifier( const std::vector< std::string >& identifiers );

private:
     void delete_all_white_space( void );
     bool is_alphabetical( char c );
     bool is_numeric( char c );
     bool is_end_of_line( char c );
     bool is_white_space( char c );
     bool equals_any_identifier( const std::vector< std::string >& identifiers, Token& token );

     Token __current_token;
     std::string __input;
     char* __cur_char;
};

#endif //__LEXER_H__
