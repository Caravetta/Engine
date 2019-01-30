#ifndef __TOKEN_PARSER_H__
#define __TOKEN_PARSER_H__

#include <vector>
#include <fstream>
#include "token.h"

namespace Engine {
namespace Token_Parser {

typedef struct {
    std::vector<token_t> token_list;
} token_parser_t;

std::vector<token_t> tokenize_file( std::string file_path );
std::vector<token_t> tokenize_stream( std::fstream& stream );

} // end namespace Token_Parser
} // end namespace Engine

#endif //__TOKEN_PARSER_H__
