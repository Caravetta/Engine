#include "handle.h"

namespace core {
#if 0
Handle::Handle()
{
    this->handle.data.index = 0;
    this->handle.data.phase = 0;
    this->handle.data.active = 0;
}

Handle::Handle( uint32_t index )
{
    this->handle.data.index = index;
    this->handle.data.phase = 0;
    this->handle.data.active = 0;
}

Handle::Handle( uint64_t value )
{
    this->handle.value = value;
}

void Handle::set_index( uint32_t new_index )
{
    this->handle.data.index = new_index;
}

void Handle::increment_phase()
{
    this->handle.data.phase++;
}

bool Handle::is_active()
{
    bool is_active = this->handle.data.active == 1 ? false : true;
    return is_active;
}

void Handle::set_active()
{
    this->handle.data.active = 1;
}

void Handle::set_inactive()
{
    this->handle.data.active = 0;
}

uint32_t Handle::get_index()
{
    return handle.data.index;
}

uint64_t Handle::get_value(){
    return 0;
}

Handle::operator uint64_t() const
{
    return (handle.data.active << 31 | handle.data.phase << 32 | handle.data.index);
}

void Handle::operator = ( const uint64_t &value )
{
    this->handle.value = value;
}
#endif
} // end namespace core
