#include "bit_field.h"

#define BIT_OFFSET 3
#define DEFAULT_BIT_SIZE 8

namespace Engine {

Bit_Field::Bit_Field( void )
{
    uint32_t num_blocks = ( DEFAULT_BIT_SIZE >> BIT_OFFSET ) + 1;
    _bits.resize(num_blocks);
    _num_bits = num_blocks * DEFAULT_BIT_SIZE;
}

Bit_Field::Bit_Field( const uint32_t num_bits )
{
    uint32_t bits = ( num_bits > 0 ) ? num_bits : DEFAULT_BIT_SIZE;
    uint32_t num_blocks = ( bits >> BIT_OFFSET ) + 1;
    _bits.resize(num_blocks);
    _num_bits = num_blocks * DEFAULT_BIT_SIZE;
}

Rc_t Bit_Field::expand( const uint32_t num_bits )
{
    Rc_t rc = SUCCESS;

    if ( num_bits > _num_bits ) {
        uint32_t num_blocks = ( num_bits >> BIT_OFFSET ) + 1;
        _bits.resize(num_blocks);
        _num_bits = num_blocks * DEFAULT_BIT_SIZE;
    } else {
        rc = INVALID_SIZE_ERROR;
    }

    return rc;
}

Rc_t Bit_Field::set_bit( const uint32_t position, const bool value )
{
    Rc_t rc = SUCCESS;

    if ( position < _num_bits ) {
        uint32_t block_idx = ( position >> BIT_OFFSET );
        uint32_t bit_pos = position - ( DEFAULT_BIT_SIZE * block_idx );

        CHECK( bit_pos < DEFAULT_BIT_SIZE );

        uint8_t bit_mask = 0 | ( 1 << bit_pos );

        _bits[block_idx] = ( value == true ) ? ( _bits[block_idx] | bit_mask ) : ( _bits[block_idx] & ~bit_mask );
    } else {
        rc = INDEX_BOUNDS_ERROR;
    }

    return rc;
}

bool Bit_Field::bit_set( const uint32_t position )
{
    bool is_set = false;

    if ( position < _num_bits ) {
        uint32_t block_idx = ( position >> BIT_OFFSET );
        uint32_t bit_pos = position - ( DEFAULT_BIT_SIZE * block_idx );

        CHECK( bit_pos < DEFAULT_BIT_SIZE );

        uint8_t bit_mask = 0 | ( 1 << bit_pos );

        is_set = ( _bits[block_idx] & bit_mask ) == bit_mask ? true : false;
    }

    return is_set;
}

uint32_t Bit_Field::current_size( void )
{
    return _num_bits;
}

} // end namespace Engine
