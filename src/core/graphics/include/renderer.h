#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace Engine {

class Renderer {
private:
     static Vector3f __clear_color;

public:
     static void set_clear_color( Vector3f color );
     static void clear( void );

};

} // end namespace Engine

#endif //__RENDERER_H__
