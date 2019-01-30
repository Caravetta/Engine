#include "header_parser.h"
#include "token_parser.h"

namespace Engine {
namespace Introspection {

void _parse_component( std::vector<token_t>* tokens, uint32_t index ){
    //token_type_t current_state = SYMBOL_TOKEN;
    token_t expected_token;
    expected_token.type = SYMBOL_TOKEN;
    expected_token.data = "struct";

    LOG("START " << tokens->at(index).data);

    for ( uint32_t ii = (index + 1); ii < tokens->size(); ++ii ) {
    #if 0
        switch(tokens->at(ii).type) {
        case EOL_TOKEN:
        case WHITESPACE_TOKEN: {
            continue;
        } break;
        case SYMBOL_TOKEN: {
            if ( tokens->at(ii).data == expected_token.data ) {
                LOG("Got " << tokens->at(ii).data);
                return;
            } else {
                LOG_ERROR("Got " << tokens->at(ii).data << " but was expecting " << expected_token.data);
            }
        } break;
        default: {
            // Do nothing
        } break;
        }
#endif
        if ( tokens->at(ii).type == expected_token.type ) {
            switch( tokens->at(ii).type ) {
            case SYMBOL_TOKEN: {
                if ( expected_token.data == "struct" ) {
                    expected_token.type = PUNCTUATION_TOKEN;
                    expected_token.data = "{";
                } else if ( expected_token.data == "key" ) {
                    if ( tokens->at(ii).data == "struct" ) {
                        expected_token.type = PUNCTUATION_TOKEN;
                        expected_token.data = "{";
                    } else {
                        expected_token.type = SYMBOL_TOKEN;
                        expected_token.data = "value";
                    }
                } else if ( expected_token.data == "value" ) {

                } else {

                }
            } break;
            case PUNCTUATION_TOKEN: {
                if ( expected_token.data == "{" ) {
                    expected_token.type = SYMBOL_TOKEN;
                    expected_token.data = "key";
                } else if ( expected_token.data == "}" ) {

                }
            } break;
            default: {

            } break;
            }
        } else if ( tokens->at(ii).type == WHITESPACE_TOKEN || tokens->at(ii).type == EOL_TOKEN ) {
            continue;
        } else {
            LOG_ERROR("Got " << tokens->at(ii).data << " but was expecting " << expected_token.data);
        }
    }

}


Rc_t parse_headers( std::vector<std::string>* file_paths )
{
    for ( uint32_t ii = 0; ii < file_paths->size(); ++ii ) {
        std::vector<token_t> tokens = Token_Parser::tokenize_file(file_paths->at(ii));

        for ( uint32_t jj = 0; jj < tokens.size(); ++jj ) {
            switch( tokens[jj].type ) {
            case SYMBOL_TOKEN: {
                if ( tokens[jj].data == "COMPONENT" && (jj - 2) > 0 && tokens[jj - 2].data == "define" ) {
                    _parse_component(&tokens, jj++);
                }
            } break;
            default: {
                // Do nothing
            } break;
            }
        }
    }

    return SUCCESS;
}

} // end namespace Introspection
} // end namespace Engine
