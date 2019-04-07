#include <iostream>
#include <inttypes.h>
#include "header_parser.h"
#include "token_parser.h"
#include "core_common.h"

int _parse_struct_member( std::vector<token_t>* tokens, u32* start_idx, std::vector<struct_member>* members )
{
    token_t* token = &tokens->at(*start_idx);
    struct_member member;
    bool member_done = false;
    u32 num_tokens = (u32)tokens->size();

    if ( token->type == SYMBOL_TOKEN ) {
        member.type = token->data;

        *start_idx += 1;
        token = &tokens->at(*start_idx);
        if ( token->type == PUNCTUATION_TOKEN ) {
            //this is a pointer
            member.is_pointer = true;
            *start_idx += 1;
            token = &tokens->at(*start_idx);
        } else {
            member.is_pointer = false;
        }

        if ( token->type == SYMBOL_TOKEN ) {
            member.name = token->data;
        } else {
            return -1;
        }

        while ( member_done == false ) {
            if ( token->type == EOL_TOKEN ) {
                *start_idx += 1;
                //LOG("name " << member.name << " type " << member.type);
                members->push_back(member);
                return 0;
            }

            if ( *start_idx < num_tokens ) {
                *start_idx += 1;
                token = &tokens->at(*start_idx);
            } else {
                //LOG_ERROR("Failed to find EOL before end of token stream");
                return -1;
            }
        }

    } else {
        return -1;
    }

    return 0;
}

int _parse_struct( std::vector<token_t>* tokens, u32* start_idx, std::vector<struct_def>* structs)
{
    int rc = 0;
    struct_def struct_info;
    bool name_at_end = false;
    token_t* token = &tokens->at(*start_idx);

    if ( token->type == SYMBOL_TOKEN ) {
        struct_info.struct_name = token->data;

        // update to the next token
        *start_idx += 1;
        token = &tokens->at(*start_idx);

        if ( token->type != PUNCTUATION_TOKEN && token->data != "{" ) {
            //LOG_ERROR("Struct not properly defined");
            return -1;
        }

        // update to the next token
        *start_idx += 1;
        token = &tokens->at(*start_idx);

    } else if ( token->type == PUNCTUATION_TOKEN && token->data == "{") {
        name_at_end = true;

        // update to the next token
        *start_idx += 1;
        token = &tokens->at(*start_idx);
    } else {
        //LOG_ERROR("Struct not properly defined");
        return -1;
    }

    // check if there is a EOL to remove
    if ( token->type == EOL_TOKEN ) {
        // update to the next token
        *start_idx += 1;
        token = &tokens->at(*start_idx);
    }

    // need to step through all data memebers
    while ( token->type == SYMBOL_TOKEN ) {
        rc = _parse_struct_member(tokens, start_idx, &struct_info.members);
        if ( rc != SUCCESS ) {
            //LOG_ERROR("Failed to parse struct member");
            return rc;
        }

        token = &tokens->at(*start_idx);
    }

    if ( token->type == PUNCTUATION_TOKEN && token->data == "}" ) {
        if ( name_at_end == false ) {
            structs->push_back(struct_info);
            return 0;
        }

        *start_idx += 1;
        token = &tokens->at(*start_idx);

        if ( token->type != SYMBOL_TOKEN ) {
            return -1;
        }

        struct_info.struct_name = token->data;
        structs->push_back(struct_info);

        return 0;

    } else {
        return -1;
    }

    return rc;
}

int _generate_component_data( std::vector<token_t>* tokens, u32* start_idx, std::vector<struct_def>* structs )
{

    int rc = 0;
    token_t* token = &tokens->at(*start_idx);

    if ( token->type == SYMBOL_TOKEN && token->data == "struct" ) {
        *start_idx += 1;
        rc = _parse_struct( tokens, start_idx, structs);
        token = &tokens->at(*start_idx);
    } else {
        rc = -1;
    }

    return rc;
}

int _component_parse_pass( std::vector<token_t>* tokens, std::vector<struct_def>* comps, uint32_t* max_gen_id )
{
    u32 current_idx = 0;
    u32 num_tokens = (u32)tokens->size();
    int rc = 0;

    while ( current_idx < num_tokens ) {
        token_t* token = &tokens->at(current_idx);
        if ( token->type == SYMBOL_TOKEN && token->data == "COMPONENT" ) {
            current_idx += 1;

            while ( (token->type != EOL_TOKEN) && (current_idx < num_tokens) ) {
                current_idx += 1;
                token = &tokens->at(current_idx);
            }

            current_idx += 1;

            rc = _generate_component_data(tokens, &current_idx, comps);
        } else if ( token->type == SYMBOL_TOKEN && token->data == "LAST_INTERNAL_GEN_COMP_ID" ) {
            current_idx += 1;
            token = &tokens->at(current_idx);
            if ( token->type == INTEGER_TOKEN ) {
                uint32_t last_gen_id = strtoul(token->data.c_str(), NULL, 0);
                *max_gen_id = last_gen_id;
            }

            current_idx += 1;
        }
        current_idx += 1;
    }

    return 0;
}

int parse_headers( std::vector<std::string>* file_paths, std::vector<struct_def>* comps, uint32_t* max_gen_id )
{
    for ( u32 ii = 0; ii < file_paths->size(); ++ii ) {
        std::vector<token_t> tokens = tokenize_file(file_paths->at(ii), false);

        _component_parse_pass( &tokens, comps, max_gen_id );
    }
    return 0;
}

