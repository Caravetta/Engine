#if !defined(FONT_FILE_H)

#include <vector>
#include <string>
#include <unordered_map>
#include "../core_common.h"

namespace core {

    class CORE_API Font_File {
    public:
        typedef struct {
            uint16_t id;
            uint16_t x;
            uint16_t y;
            uint16_t width;
            uint16_t height;
            uint16_t x_offset;
            uint16_t y_offset;
            uint16_t x_advance;
            uint16_t page;
            uint16_t chnl;
        } char_data_t;

    private:
        std::vector<char_data_t> char_data;
        std::unordered_map<uint16_t, uint16_t> char_map;

    public:
        Font_File( std::string file_path );
        char_data_t get_char_data( uint16_t char_id );
    };

} // end namespace core

#define FONT_FILE_H
#endif
