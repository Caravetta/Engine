#ifndef __BASIC_RENDERER_H_
#define __BASIC_RENDERER_H_

#include "core_common.h"
#include "system.h"
#include "graphics.h"

namespace Engine {

class Basic_Renderer : public System {
public:
     void init( void );
     void update( float time_step );
     void shutdown( void );

private:
     Engine::Render_Texture* position_texture;
     Engine::Render_Texture* normal_texture;
     Engine::Render_Texture* albedo_texture;
     Engine::Render_Texture* depth_texture;
     Engine::Render_Texture* lighting_texture;
     Engine::Shader* lighting_shader;
     Engine::Shader* lighting_shader1;
     Engine::Material outline_material;
     int width; //REMOVE
     int height; //REMOVE
};

} // end namespace Engine

#endif //__BASIC_RENDERER_H_
