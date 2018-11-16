#ifndef __CORE_H__
#define __CORE_H__

#ifdef WINDOWS_PLATFORM
    #ifdef CORE_EXPORT
        #define CORE_API __declspec(dllexport)
    #else
        #define CORE_API __declspec(dllimport)
    #endif
#endif

#include "asset_system/asset.h"
#include "asset_system/asset_manager.h"
#include "event_system/event_system.h"
#include "input_system/input_manager.h"
#include "window/window.h"
#include "mesh/mesh.h"
#include "camera_system/camera.h"
#include "camera_system/debug_camera.h"
#include "texture/texture.h"
#include "image/image.h"
#include "platform/thread.h"
#include "platform/platform_utils.h"
#include "terrain_system/terrain.h"
#include "platform/platform.h"
#include "component_system/component_manager.h"
#include "component_system/component.h"
#include "entity_system/entity.h"
#include "entity_system/entity_manager.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "math/math_utils.h"
#include "math/perlin.h"
#include "math/fractal_noise.h"
#include "quadtree/quadtree.h"
#include "loader.h"
#include "time/timer.h"
#include "time/function_perf.h"
#include "core_return.h"
#include "system/system.h"
#include "system/system_manager.h"
#include "handle_system/handle.h"
#include "font/font_manager.h"
#include "font/font.h"
#include "archetype_system/archetype.h"
#include "archetype_system/archetype_manager.h"
#include "job_system/job.h"
#include "job_system/job_manager.h"
#include "worker_system/worker_manager.h"
#include "gui/gui_manager.h"

#endif //__CORE_H__
