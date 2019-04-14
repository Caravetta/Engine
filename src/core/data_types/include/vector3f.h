#ifndef __VECTOR3F_H__
#define __VECTOR3F_H__

namespace Engine {

struct Vector3f {
     union {
          struct {
               float x;
               float y;
               float z;
          };
          struct {
               float r;
               float g;
               float b;
          };
     };
};

} // end namespace Engine

#endif //__VECTOR3F_H__
