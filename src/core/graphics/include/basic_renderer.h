#ifndef __BASIC_RENDERER_H_
#define __BASIC_RENDERER_H_

#include "core_common.h"
#include "system.h"

namespace Engine {

class Basic_Renderer : public System {
public:
     void init( void );
     void update( float time_step );
     void shutdown( void );
};

} // end namespace Engine

#endif //__BASIC_RENDERER_H_
