#include "sort.h"

namespace Engine {

static void _swap_uint32( uint32_t* a, uint32_t* b )
{
     uint32_t tmp = *a;
     *a = *b;
     *b = tmp;
}

static size_t _partition_uint32( uint32_t* data, size_t start, size_t end )
{
     uint32_t pivot = data[end];
     size_t index = (start - 1);

     for ( size_t ii = start; ii <= (end - 1); ii++ ) {
          if ( data[ii] < pivot ) {
               index++;
               _swap_uint32(&data[index], &data[ii]);
          }
     }
     _swap_uint32(&data[index + 1], &data[end]);

     return (index + 1);
}

void quick_sort_uint32( uint32_t* data, size_t start, size_t end )
{
     if ( start < end ) {
          size_t part_idx = _partition_uint32(data, start, end);

          quick_sort_uint32(data, start, (part_idx - 1));
          quick_sort_uint32(data, (part_idx + 1), end);
     }
}

}

