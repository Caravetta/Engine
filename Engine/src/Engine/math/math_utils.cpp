#include "math_utils.h"

namespace Engine {

#define PI 3.14159265

float to_radians( float angle )
{
    return (float)((angle * PI) / 180);
}

} // end namespace Engine
