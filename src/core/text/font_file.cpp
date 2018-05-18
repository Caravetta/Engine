#include <iostream>
#include <fstream>
#include "font_file.h"

namespace core {

#define GET_UINT16_FROM_STING(store, string_, pivot) { std::size_t found = string_.find(pivot); \
                                                      if ( found != std::string::npos ) {           \
                                                        store = (uint16_t)stoi(string_.substr((found + 1))); \
                                                      } \
                                                    } \


Font_File::Font_File( std::string file_path ) {

    std::ifstream font_file(file_path, std::ios::in);
    std::string current_line;
    uint16_t current_idx = 0;

    if ( !font_file.is_open() ) {
        LOG_ERROR("Failed to open " << file_path);
        return;
    }

    while ( getline(font_file, current_line) ) {
        std::istringstream buff(current_line);
        std::istream_iterator<std::string> beg(buff), end;
        std::vector<std::string> tokens(beg, end);

        if ( tokens.at(0) == "char" ) {

            GET_UINT16_FROM_STING(char_data[current_idx].id, tokens.at(1), "=");
            GET_UINT16_FROM_STING(char_data[current_idx].x, tokens.at(2), "=");
            GET_UINT16_FROM_STING(char_data[current_idx].y, tokens.at(3), "=");
            GET_UINT16_FROM_STING(char_data[current_idx].width, tokens.at(4), "=");
            GET_UINT16_FROM_STING(char_data[current_idx].height, tokens.at(5), "=");
            GET_UINT16_FROM_STING(char_data[current_idx].x_offset, tokens.at(6), "=");
            GET_UINT16_FROM_STING(char_data[current_idx].y_offset, tokens.at(7), "=");
            GET_UINT16_FROM_STING(char_data[current_idx].x_advance, tokens.at(8), "=");
            GET_UINT16_FROM_STING(char_data[current_idx].page, tokens.at(9), "=");
            GET_UINT16_FROM_STING(char_data[current_idx].chnl, tokens.at(10), "=");

            char_map.insert({ char_data[current_idx].id, current_idx });
            current_idx++;

        } else if( tokens.at(0) == "chars" ) {
            std::size_t found = tokens.at(1).find("=");
            if ( found != std::string::npos ) {
                uint16_t resize_size = (uint16_t)stoi(tokens.at(1).substr((found + 1)));
                char_data.resize(resize_size + 1);
            }
        }
    }

    font_file.close();

    return;
}

core::Font_File::char_data_t Font_File::get_char_data( uint16_t char_id )
{
    core::Font_File::char_data_t char_data_;

    return char_data_;
}

} // end namespace core
