#include "token_parser.h"
#include "core_common.h"

int main( int argc, char* argv[] )
{
     std::vector<token_t> tokens = tokenize_file(argv[1], false);

     for ( size_t ii = 0; ii < tokens.size(); ++ii ) {
          print_token_info(&tokens[ii]);
     }
     return 0;
}

