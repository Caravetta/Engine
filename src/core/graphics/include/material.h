#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "core_common.h"
#include "shader.h"

namespace Engine {

class Material {
private:
     Shader* __shader;

public:
     Material( Shader& shader );
     ~Material( void );
     Shader& shader( void );
};

} // end namespace Engine

#endif //__MATERIAL_H__
