#include <cstring>

namespace Engine {

uint32_t crc32( const char* string )
{
      uint32_t crc = 0xffffffff;
      crc = crc32_update(crc, string, strlen(string) * sizeof(char));
      crc = ~crc;

      return crc;
}

} // end namespace Engine

