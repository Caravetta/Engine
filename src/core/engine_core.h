#ifndef __ENGINE_CORE_H__
#define __ENGINE_CORE_H__

#include "core_common.h"
#include "ecs.h"
#include "engine_math.h"
#include "reflection.h"
#include "utils.h"
#include "input.h"
#include "graphics.h"

namespace Engine {

extern "C" ENGINE_API Rc_t engine_init( void );

} // end namespace Engine

#endif //__ENGINE_CORE_H__
