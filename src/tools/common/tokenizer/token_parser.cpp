#include "token_parser.h"
#include "core_common.h"
#include <iostream>

#define RESET_TOKEN() {         \
    token.data.clear();         \
    token.type = INVALID_TOKEN; \
}

void _tokenize( std::fstream& stream, std::vector<token_t>* token_list, bool white_space )
{
    token_t token;
    int input_char = stream.get();

    while ( !stream.eof() ) {
        RESET_TOKEN()
        if ( input_char == '/' ) {
            //std::cout << "JOSH HERE1" << std::endl;
            int peek_character = stream.peek();

            if ( peek_character == '/' ) {
                // Go through and remove line comment
                while ( peek_character != 0x0A && !stream.eof() ) {
                    peek_character = stream.get();
                }
                token.type = EOL_TOKEN;
                input_char = stream.get();
                continue;
            } else if ( peek_character == '*' ) {
                // Go through and remove block comment
                while ( true ) {
                    RESET_TOKEN()
                    peek_character = stream.get();

                    if ( peek_character == -1 ) {
                        //LOG_ERROR("Block comment not terminated before EOF");
                    } else if ( peek_character == 0x0A ) {
                        token.type = EOL_TOKEN;
                        token_list->push_back(token);
                    } else if ( peek_character == '*' ) {
                        peek_character = stream.peek();

                        if ( peek_character == -1 ) {
                            //LOG_ERROR("Block comment not terminated before EOF");
                        } else if ( peek_character == '/' ) {
                            input_char = stream.get();
                            token.type = WHITESPACE_TOKEN;
                            token.data = ' ';
                            token_list->push_back(token);
                            input_char = stream.get();
                            break;
                        }

                    }
                }
            } else {
                //std::cout << "JOSH HERE" << std::endl;
                // it must be an include
                token.type = SYMBOL_TOKEN;
            input_char = parse_symbol_token(stream, &token, input_char);
            token_list->push_back(token);
            }
        } else if ( isalpha(input_char) || input_char == '_' ) {
            //std::cout << "JOSH HERE2" << std::endl;
            token.type = SYMBOL_TOKEN;
            input_char = parse_symbol_token(stream, &token, input_char);
            token_list->push_back(token);
        } else if ( input_char == 0x0A ) {
            //std::cout << "JOSH HERE3" << std::endl;
            token.type = EOL_TOKEN;
            token.data = "none";
            token_list->push_back(token);
            input_char = stream.get();
        } else if ( isspace(input_char) ) {
            //std::cout << "JOSH HERE4" << std::endl;
            if ( white_space ) { // check if user wants white space tokens
                token.type = WHITESPACE_TOKEN;
                token.data = "none";
                token_list->push_back(token);
            }
            bool still_white_space = true;
            while ( still_white_space ) {
                input_char = stream.get();
                if ( input_char == ' ' || input_char == 0x09 ||
                     input_char == 0x0B || input_char == 0x0D ) {
                    continue;
                }

                still_white_space = false;
            }

        } else if ( input_char == '\"' ) {
            //std::cout << "JOSH HERE5" << std::endl;
            token.type = LITERAL_TOKEN;
            input_char = parse_literal_token(stream, &token, input_char);
            token_list->push_back(token);
        } else if ( input_char == '\'' ) {
            //std::cout << "JOSH HERE6" << std::endl;
            token.type = CONST_LITERAL_TOKEN;
            input_char = parse_const_literal_token(stream, &token, input_char);
            token_list->push_back(token);
        } else if ( isdigit(input_char) ) {
            //std::cout << "JOSH HERE7" << std::endl;
            token.type = INTEGER_TOKEN;
            input_char = parse_integer_token(stream, &token, input_char);
            token_list->push_back(token);
        } else if ( ispunct(input_char) ) {
            //std::cout << "JOSH HERE8" << std::endl;
            token.type = PUNCTUATION_TOKEN;
            input_char = parse_punctuation_token(stream, &token, input_char);
            token_list->push_back(token);
        }
    }

    token.data.clear();
    token.type = EOF_TOKEN;
    token_list->push_back(token);
}


std::vector<token_t> tokenize_file( std::string file_path, bool white_space )
{
    std::vector<token_t> token_list;

    std::fstream source;
    source.open(file_path.c_str(), std::ios_base::in);
    if ( source.fail() ) {
        //LOG_ERROR("Failed to open " << file_path);
        return token_list;
    }

    _tokenize( source, &token_list, white_space );

    return token_list;
}

std::vector<token_t> tokenize_stream( std::fstream& stream )
{
    UNUSED_ARG( stream );
    std::vector<token_t> token_list;
    return token_list;
}
