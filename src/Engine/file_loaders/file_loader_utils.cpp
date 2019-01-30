#include "Engine_Types.h"
#include "core_common.h"
#include "file_loader_utils.h"

namespace Engine {

std::string get_file_type( std::string file_path )
{
    u64 start = 0;
    start = file_path.find_last_of(".");
    return file_path.substr(start + 1);
}

} // end namespace Engine
