#include "Engine_Types.h"
#include "core_common.h"

namespace Engine {

Rc_t Material::add_element( std::string name, material_element_type_t type )
{
    std::unordered_map<std::string, uint64_t>::const_iterator ele = element_map.find(name);
    if ( ele == element_map.end() ) {
        material_element_info_t element_info;
        element_info.element_name = name;
        element_info.type = type;
        uint64_t new_size = data_size;

        switch( type ) {
        case VEC3_ELEMENT: {
            new_size += sizeof(Vector3f);
        } break;
        case MATRIX4_ELEMENT: {
            new_size += sizeof(Matrix4f);
        } break;
        case TEXT_HANDLE_ELEMENT: {
            new_size += sizeof(Texture_Handle);
        } break;
        default: {
            LOG_ERROR("Uknown material data type");
        } break;
        }

        if ( data_size == 0 ) {
            data = (uint8_t*)malloc(new_size);
            element_info.data_offset = 0;
        } else {
            data = (uint8_t*)realloc(data, new_size);
            element_info.data_offset = (uint32_t)data_size;
        }

        data_size = new_size;
        element_info_vec.push_back(element_info);
        element_map.insert({name, element_info_vec.size() - 1});

        return SUCCESS;
    }

    return ENGINE_ERROR;
}

} // end namespace Engine
