#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "../core_common.h"
#include "vector.h"

class CORE_API Quaternion {
public:
    ALWAYS_INLINE Quaternion() {}
    ALWAYS_INLINE Quaternion( const Vector& quat );
    ALWAYS_INLINE Quaternion( float x, float y, float z, float w );
    ALWAYS_INLINE Quaternion( const Vector3f& axis, float angle );

};

#endif
