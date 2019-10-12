#include "material.h"

namespace Engine {

Material::Material( Shader& shader )
{
     __shader = &shader;
}

Material::~Material( void )
{
     // Do nothing
}

Shader& Material::shader( void )
{
     return *__shader;
}

} // end namespace Engine

