#ifndef __BIT_FIELD_H__
#define __BIT_FIELD_H__

#include <vector>
#include "core_common.h"

namespace Engine {

class Bit_Field {
private:
    std::vector<uint8_t> _bits;
    uint32_t _num_bits;

public:
    Bit_Field( void );
    Bit_Field( const uint32_t num_bits );
    Rc_t expand( const uint32_t num_bits );
    Rc_t set_bit( const uint32_t position, const bool value );
    bool bit_set( const uint32_t position );
    uint32_t current_size( void );
};

} // end name space Engine

#endif //__BIT_FIELD_H__
